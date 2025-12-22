#include "AgendaManager.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <QTimer>
#include <QtGlobal>
#include <QRegularExpression>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <algorithm>
#include <cctype>
#include <stdexcept>

AgendaManager::AgendaManager(QObject *parent)
    : QObject(parent)
    , m_agenda(new Agenda())
    , m_currentFilter("全部")
    , m_currentSortType(0)
    , m_isLoading(false)
{
    // 自动加载上次保存的数据
    QTimer::singleShot(100, this, &AgendaManager::autoLoad);
}

AgendaManager::~AgendaManager()
{
    autoSave();
    delete m_agenda;
}

// ========== 智能输入处理 ==========

QString AgendaManager::trimWhitespace(const QString &str) const
{
    QString result;
    for (const QChar &c : str) {
        if (!c.isSpace()) {
            result.append(c);
        }
    }
    return result;
}

QString AgendaManager::padZero(int num) const
{
    return (num < 10) ? "0" + QString::number(num) : QString::number(num);
}

bool AgendaManager::isAllDigit(const QString &str) const
{
    for (const QChar &c : str) {
        if (!c.isDigit()) {
            return false;
        }
    }
    return !str.isEmpty();
}

QString AgendaManager::processDateInput(const QString &input) const
{
    QString cleanInput = trimWhitespace(input);
    QString lowerInput = cleanInput.toLower();

    // 情况1: "t" 或 "today" → 今日日期
    if (lowerInput == "t" || lowerInput == "today") {
        return getTodayDate();
    }

    // 情况2: 纯数字 → 今日日期
    if (isAllDigit(cleanInput)) {
        return getTodayDate();
    }

    // 情况3: 多种格式的日期字符串
    // 正则表达式匹配 yyyy(任意分隔符)mm(任意分隔符)dd
    static QRegularExpression dateRegex(R"(^(\d{4})\D+(\d{1,2})\D+(\d{1,2})$)",
                                        QRegularExpression::CaseInsensitiveOption);

    QRegularExpressionMatch match = dateRegex.match(cleanInput);
    if (match.hasMatch()) {
        int year = match.captured(1).toInt();
        int month = match.captured(2).toInt();
        int day = match.captured(3).toInt();

        if (year >= 1900 && year <= 2100 &&
            month >= 1 && month <= 12 &&
            day >= 1 && day <= 31) {

            // 简单验证月份天数
            if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
                return getTodayDate();
            }
            if (month == 2 && day > 29) {
                return getTodayDate();
            }

            return QString("%1/%2/%3")
                .arg(year)
                .arg(padZero(month))
                .arg(padZero(day));
        }
    }

    // 情况4: 无法识别 → 默认今日日期
    return getTodayDate();
}

QString AgendaManager::fixTimeFormat(const QString &input) const
{
    QString cleanInput = trimWhitespace(input);

    // 情况1: 纯数字 → "00:00"
    if (isAllDigit(cleanInput)) {
        return "00:00";
    }

    // 情况2: 正则匹配 hh(非数字)mm 格式
    static QRegularExpression timeRegex(R"(^(\d{1,2})\D+(\d{1,2})$)",
                                        QRegularExpression::CaseInsensitiveOption);

    QRegularExpressionMatch match = timeRegex.match(cleanInput);
    if (match.hasMatch()) {
        int hour = match.captured(1).toInt();
        int minute = match.captured(2).toInt();

        if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59) {
            return QString("%1:%2")
            .arg(padZero(hour))
                .arg(padZero(minute));
        }
    }

    // 情况3: 无法识别 → "00:00"
    return "00:00";
}

QString AgendaManager::getTodayDate() const
{
    QDate today = QDate::currentDate();
    return QString("%1/%2/%3")
        .arg(today.year())
        .arg(padZero(today.month()))
        .arg(padZero(today.day()));
}

QString AgendaManager::getCurrentTime() const
{
    QTime now = QTime::currentTime();
    return QString("%1:%2")
        .arg(padZero(now.hour()))
        .arg(padZero(now.minute()));
}

// ========== 日程管理 ==========

QVariantList AgendaManager::getAllItems() const
{
    QVariantList items;
    if(m_currentFilter == "全部"){
        int count = m_agenda->getItemCount();

        for (int i = 1; i <= count; i++) {
            AgendaItem item = m_agenda->getItem(i);
            if (item.getId() != -1) {
                items.append(agendaItemToMap(item));
            }
        }
    }
    else{
        const std::vector<int> &filter = m_agenda->filtered_indices;
        for(auto i : filter){
            AgendaItem item = m_agenda->getItem(i+1);
            items.append(agendaItemToMap(item));
        }
    }
    return items;
}

QVariantMap AgendaManager::getItem(int id) const
{
    AgendaItem item = m_agenda->getItem(id);
    if (item.getId() == -1) {
        return QVariantMap();
    }
    return agendaItemToMap(item);
}

int AgendaManager::addItem(const QString &name, const QString &desc,
                           const QString &ddl, const QString &time,
                           int priority, int status)
{
    try {
        // 智能处理日期和时间
        QString processedDate = processDateInput(ddl);
        QString processedTime = fixTimeFormat(time);

        // 验证
        if (name.trimmed().isEmpty()) {
            emit errorOccurred("日程名称不能为空");
            return -1;
        }

        if (!isValidDateString(processedDate)) {
            emit errorOccurred("日期格式不正确");
            return -1;
        }

        if (!isValidTimeString(processedTime)) {
            emit errorOccurred("时间格式不正确");
            return -1;
        }

        if (priority < 1 || priority > 4) {
            emit errorOccurred("优先级应为 1-4");
            return -1;
        }

        // 创建日程项
        AgendaItem item(
            name.toStdString(),
            desc.toStdString(),
            processedDate.toStdString(),
            processedTime.toStdString(),
            priority
            );
        item.setStatus(status);

        int newId = m_agenda->addItem(item);

        if (newId > 0) {
            // 应用当前排序
            if (m_currentSortType != 0) {
                m_agenda->sortItems(m_currentSortType);
            }

            emit dataChanged();
            emit itemAdded(newId);
            emit operationCompleted(QString("日程添加成功 (ID: %1)").arg(newId));
            autoSave();
            return newId;
        }

        emit errorOccurred("添加日程失败");
        return -1;
    } catch (const std::exception &e) {
        emit errorOccurred(QString("添加失败: %1").arg(e.what()));
        return -1;
    } catch (...) {
        emit errorOccurred("添加日程失败");
        return -1;
    }
}

bool AgendaManager::updateItem(int id, const QVariantMap &updates)
{
    try {
        AgendaItem oldItem = m_agenda->getItem(id);
        if (oldItem.getId() == -1) {
            emit errorOccurred(QString("ID %1 的日程不存在").arg(id));
            return false;
        }

        // 获取更新值，应用智能处理
        QString name = updates.contains("name") ?
                           updates["name"].toString() : QString::fromStdString(oldItem.getName());
        QString desc = updates.contains("description") ?
                           updates["description"].toString() : QString::fromStdString(oldItem.getDescription());
        QString ddl = updates.contains("ddl") ?
                          processDateInput(updates["ddl"].toString()) : QString::fromStdString(oldItem.getDDL());
        QString time = updates.contains("time") ?
                           fixTimeFormat(updates["time"].toString()) : QString::fromStdString(oldItem.getTime());
        int status = updates.contains("status") ?
                         updates["status"].toInt() : oldItem.getStatus();
        int priority = updates.contains("priority") ?
                           updates["priority"].toInt() : oldItem.getPriority();

        // 验证
        if (name.trimmed().isEmpty()) {
            emit errorOccurred("日程名称不能为空");
            return false;
        }

        if (!isValidDateString(ddl)) {
            emit errorOccurred("日期格式不正确");
            return false;
        }

        if (!isValidTimeString(time)) {
            emit errorOccurred("时间格式不正确");
            return false;
        }

        // 创建新项
        AgendaItem newItem(
            name.toStdString(),
            desc.toStdString(),
            ddl.toStdString(),
            time.toStdString(),
            priority
            );
        newItem.setStatus(status);

        // 更新
        bool success = m_agenda->updateItem(id, newItem);

        if (success) {
            emit dataChanged();
            emit itemUpdated(id);
            emit operationCompleted("日程更新成功");
            autoSave();
        }

        return success;
    } catch (const std::exception &e) {
        emit errorOccurred(QString("更新失败: %1").arg(e.what()));
        return false;
    } catch (...) {
        emit errorOccurred("更新日程失败");
        return false;
    }
}

bool AgendaManager::removeItem(int id)
{
    try {
        bool success = m_agenda->removeItem(id);
        if (success) {
            emit dataChanged();
            emit itemRemoved(id);
            emit operationCompleted("日程删除成功");
            autoSave();
        } else {
            emit errorOccurred(QString("ID %1 的日程不存在").arg(id));
        }
        return success;
    } catch (const std::exception &e) {
        emit errorOccurred(QString("删除失败: %1").arg(e.what()));
        return false;
    } catch (...) {
        emit errorOccurred("删除日程失败");
        return false;
    }
}

bool AgendaManager::removeItems(const QVariantList &ids)
{
    int successCount = 0;
    for (const QVariant &idVar : ids) {
        int id = idVar.toInt();
        if (m_agenda->removeItem(id)) {
            successCount++;
        }
    }

    if (successCount > 0) {
        emit dataChanged();
        emit operationCompleted(QString("成功删除 %1 个日程").arg(successCount));
        autoSave();
        return true;
    }

    return false;
}

// ========== 排序和筛选 ==========

void AgendaManager::sortBy(int sortCode)
{
    try {
        m_agenda->sortItems(sortCode);
        m_currentSortType = sortCode;
        emit dataChanged();
    } catch (const std::exception &e) {
        emit errorOccurred(QString("排序失败: %1").arg(e.what()));
    }
}

void AgendaManager::applyFilter(int filterCode, const QString &filterValue)
{
    try {
        m_agenda->applyFilter(filterCode, filterValue.toStdString());

        // 更新当前筛选状态
        switch (filterCode) {
        case 3: // BY_STATUS
            if (filterValue == "0") m_currentFilter = "等待处理";
            else if (filterValue == "1") m_currentFilter = "已完成";
            else if (filterValue == "2") m_currentFilter = "已取消";
            else if (filterValue == "3") m_currentFilter = "暂停";
            else m_currentFilter = "状态筛选";
            break;
        case 1: // BY_PRIORITY
            m_currentFilter = QString("优先级: %1").arg(filterValue);
            break;
        default:
            m_currentFilter = "自定义筛选";
        }

        emit filterChanged();
        emit dataChanged();
    } catch (const std::exception &e) {
        emit errorOccurred(QString("筛选失败: %1").arg(e.what()));
    }
}

void AgendaManager::clearFilter()
{
    try {
        m_agenda->clearFilter();
        m_currentFilter = "全部";
        emit filterChanged();
        emit dataChanged();
        emit operationCompleted("筛选已清除");
    } catch (const std::exception &e) {
        emit errorOccurred(QString("清除筛选失败: %1").arg(e.what()));
    }
}

QVariantList AgendaManager::searchItems(const QString &keyword) const
{
    QVariantList results;
    if (keyword.trimmed().isEmpty()) {
        return getAllItems();
    }

    QString searchTerm = keyword.toLower();
    auto allItems = getAllItems();

    for (const QVariant &itemVar : qAsConst(allItems)) {
        QVariantMap item = itemVar.toMap();
        QString name = item["name"].toString().toLower();
        QString desc = item["description"].toString().toLower();

        if (name.contains(searchTerm) || desc.contains(searchTerm)) {
            results.append(item);
        }
    }

    return results;
}

// ========== 快速操作 ==========

int AgendaManager::quickAddItem(const QString &name, int priority)
{
    if (name.trimmed().isEmpty()) {
        emit errorOccurred("日程名称不能为空");
        return -1;
    }

    if (priority < 1 || priority > 4) {
        priority = 3; // 默认中等优先级
    }

    return addItem(name, "", getTodayDate(), getCurrentTime(), priority, 0);
}

void AgendaManager::quickCompleteItem(int id)
{
    AgendaItem item = m_agenda->getItem(id);
    if (item.getId() != -1) {
        QVariantMap updates;
        updates["status"] = (item.getStatus() == 1) ? 0 : 1; // 切换状态
        updateItem(id, updates);
    }
}

void AgendaManager::markAsCompleted(int id)
{
    QVariantMap updates;
    updates["status"] = 1;
    updateItem(id, updates);
}

void AgendaManager::toggleCompletion(int id)
{
    quickCompleteItem(id);
}

void AgendaManager::markAsCompletedBatch(const QVariantList &ids)
{
    int updatedCount = 0;
    for (const QVariant &idVar : ids) {
        int id = idVar.toInt();
        AgendaItem item = m_agenda->getItem(id);
        if (item.getId() != -1 && item.getStatus() != 1) {
            QVariantMap updates;
            updates["status"] = 1;
            updateItem(id, updates);
            updatedCount++;
        }
    }

    if (updatedCount > 0) {
        emit operationCompleted(QString("已将 %1 个日程标记为已完成").arg(updatedCount));
    }
}

// ========== 文件操作 ==========

bool AgendaManager::importFromCSV(const QString &filePath)
{
    m_isLoading = true;
    emit loadingChanged();

    try {
        bool success = FileProcess::importList(*m_agenda, filePath.toStdString());

        if (success) {
            int count = m_agenda->getItemCount();
            emit dataChanged();
            emit itemsImported(count);
            emit operationCompleted(QString("成功从 %1 导入 %2 个日程")
                                        .arg(QFileInfo(filePath).fileName())
                                        .arg(count));
            autoSave();
        } else {
            emit errorOccurred("CSV导入失败：文件格式不正确或文件不存在");
        }

        m_isLoading = false;
        emit loadingChanged();
        return success;
    } catch (const std::exception &e) {
        m_isLoading = false;
        emit loadingChanged();
        emit errorOccurred(QString("导入失败: %1").arg(e.what()));
        return false;
    } catch (...) {
        m_isLoading = false;
        emit loadingChanged();
        emit errorOccurred("导入失败：未知错误");
        return false;
    }
}

bool AgendaManager::exportToCSV(const QString &filePath)
{
    try {
        bool success = FileProcess::exportList(*m_agenda, filePath.toStdString());

        if (success) {
            emit operationCompleted(QString("成功导出到 %1").arg(filePath));
        } else {
            emit errorOccurred("导出失败");
        }

        return success;
    } catch (...) {
        emit errorOccurred("导出失败：文件写入错误");
        return false;
    }
}

bool AgendaManager::importFromTXT(const QString &filePath)
{
    try {
        bool success = FileProcess::importCard(*m_agenda, filePath.toStdString());

        if (success) {
            emit dataChanged();
            emit operationCompleted(QString("成功从 %1 导入日程卡片")
                                        .arg(QFileInfo(filePath).fileName()));
            autoSave();
        } else {
            emit errorOccurred("TXT导入失败：卡片格式不正确");
        }

        return success;
    } catch (...) {
        emit errorOccurred("导入失败：文件格式错误");
        return false;
    }
}

bool AgendaManager::exportToTXT(int id, const QString &filePath)
{
    try {
        AgendaItem item = m_agenda->getItem(id);
        if (item.getId() == -1) {
            emit errorOccurred(QString("ID %1 的日程不存在").arg(id));
            return false;
        }

        bool success = FileProcess::exportCard(item, filePath.toStdString());

        if (success) {
            emit operationCompleted(QString("日程卡片导出到 %1 成功").arg(filePath));
        } else {
            emit errorOccurred("卡片导出失败");
        }

        return success;
    } catch (...) {
        emit errorOccurred("导出失败：文件写入错误");
        return false;
    }
}

// ========== 自动保存/加载 ==========

bool AgendaManager::autoSave()
{
    try {
        QString filePath = "autosave.csv";
        bool success = FileProcess::exportList(*m_agenda, filePath.toStdString());
        if (success) {
            qDebug() << "自动保存成功:" << filePath;
        }
        return success;
    } catch (...) {
        qDebug() << "自动保存失败";
        return false;
    }
}

bool AgendaManager::autoLoad()
{
    try {
        QString filePath = "autosave.csv";
        bool success = FileProcess::importList(*m_agenda, filePath.toStdString());
        if (success) {
            emit dataChanged();
            qDebug() << "自动加载成功:" << filePath;
        }
        return success;
    } catch (...) {
        qDebug() << "自动加载失败";
        return false;
    }
}

// ========== 工具函数 ==========

QVariantList AgendaManager::getStatusOptions() const
{
    QVariantList options;
    options.append(QVariantMap{{"text", "全部"}, {"value", -1}});
    options.append(QVariantMap{{"text", "等待处理"}, {"value", 0}});
    options.append(QVariantMap{{"text", "已完成"}, {"value", 1}});
    options.append(QVariantMap{{"text", "已取消"}, {"value", 2}});
    options.append(QVariantMap{{"text", "暂停"}, {"value", 3}});
    return options;
}

QVariantList AgendaManager::getPriorityOptions() const
{
    QVariantList options;
    options.append(QVariantMap{{"text", "全部"}, {"value", -1}});
    options.append(QVariantMap{{"text", "紧急 (1)"}, {"value", 1}});
    options.append(QVariantMap{{"text", "高 (2)"}, {"value", 2}});
    options.append(QVariantMap{{"text", "中等 (3)"}, {"value", 3}});
    options.append(QVariantMap{{"text", "一般 (4)"}, {"value", 4}});
    return options;
}

QString AgendaManager::getStatusText(int status) const
{
    switch (status) {
    case 0: return "等待处理";
    case 1: return "已完成";
    case 2: return "已取消";
    case 3: return "暂停";
    default: return "未知";
    }
}

QString AgendaManager::getPriorityText(int priority) const
{
    switch (priority) {
    case 1: return "紧急";
    case 2: return "高";
    case 3: return "中等";
    case 4: return "一般";
    default: return "未知";
    }
}

QString AgendaManager::getStatusColor(int status) const
{
    switch (status) {
    case 0: return "#3498db"; // 蓝色
    case 1: return "#2ecc71"; // 绿色
    case 2: return "#e74c3c"; // 红色
    case 3: return "#f39c12"; // 橙色
    default: return "#95a5a6"; // 灰色
    }
}

QString AgendaManager::getPriorityColor(int priority) const
{
    switch (priority) {
    case 1: return "#e74c3c"; // 红色
    case 2: return "#e67e22"; // 橙色
    case 3: return "#f1c40f"; // 黄色
    case 4: return "#3498db"; // 蓝色
    default: return "#95a5a6"; // 灰色
    }
}

QVariantMap AgendaManager::getStatistics() const
{
    QVariantMap stats;
    int total = m_agenda->getItemCount();
    int completed = 0;
    int overdue = 0;
    int queue = 0;
    int pause = 0;

    QDate today = QDate::currentDate();

    for (int i = 1; i <= total; i++) {
        AgendaItem item = m_agenda->getItem(i);
        if (item.getId() != -1) {
            switch (item.getStatus()) {
            case 0: queue++; break;
            case 1: completed++; break;
            case 2: overdue++; break;
            case 3: pause++; break;
            }

            // 检查是否过期
            QDate itemDate = QDate::fromString(QString::fromStdString(item.getDDL()), "yyyy/MM/dd");
            if (itemDate < today && item.getStatus() != 1) {
                stats["overdueCount"] = stats["overdueCount"].toInt() + 1;
            }
        }
    }

    stats["total"] = total;
    stats["completed"] = completed;
    stats["overdue"] = overdue;
    stats["queue"] = queue;
    stats["pause"] = pause;
    stats["completionRate"] = total > 0 ? (completed * 100.0 / total) : 0;

    return stats;
}

// ========== 辅助函数 ==========

QVariantMap AgendaManager::agendaItemToMap(const AgendaItem &item) const
{
    QVariantMap map;
    map["id"] = item.getId();
    map["name"] = QString::fromStdString(item.getName());
    map["description"] = QString::fromStdString(item.getDescription());
    map["ddl"] = QString::fromStdString(item.getDDL());
    map["time"] = QString::fromStdString(item.getTime());
    map["status"] = item.getStatus();
    map["priority"] = item.getPriority();

    // 文本和颜色
    map["statusText"] = getStatusText(item.getStatus());
    map["priorityText"] = getPriorityText(item.getPriority());
    map["statusColor"] = getStatusColor(item.getStatus());
    map["priorityColor"] = getPriorityColor(item.getPriority());

    // 是否过期
    QDate today = QDate::currentDate();
    QDate itemDate = QDate::fromString(QString::fromStdString(item.getDDL()), "yyyy/MM/dd");
    QTime itemTime = QTime::fromString(QString::fromStdString(item.getTime()), "HH:mm");
    QDateTime itemDateTime(itemDate, itemTime);
    QDateTime nowDateTime(today, QTime::currentTime());

    map["isOverdue"] = itemDateTime < nowDateTime && item.getStatus() != 1;
    map["isToday"] = itemDate == today;

    return map;
}

AgendaItem AgendaManager::mapToAgendaItem(const QVariantMap &map) const
{
    std::string name = map["name"].toString().toStdString();
    std::string desc = map["description"].toString().toStdString();
    std::string ddl = map["ddl"].toString().toStdString();
    std::string time = map["time"].toString().toStdString();
    int priority = map["priority"].toInt();
    int status = map.contains("status") ? map["status"].toInt() : 0;

    AgendaItem item(name, desc, ddl, time, priority);
    item.setStatus(status);

    if (map.contains("id")) {
        item.setId(map["id"].toInt());
    }

    return item;
}

// ========== 验证函数 ==========

bool AgendaManager::isValidDateString(const QString &date) const
{
    static QRegularExpression dateRegex("^\\d{4}/\\d{2}/\\d{2}$");
    if (!dateRegex.match(date).hasMatch()) {
        return false;
    }

    QStringList parts = date.split('/');
    if (parts.size() != 3) return false;

    bool ok;
    int year = parts[0].toInt(&ok);
    if (!ok || year < 1900 || year > 2100) return false;

    int month = parts[1].toInt(&ok);
    if (!ok || month < 1 || month > 12) return false;

    int day = parts[2].toInt(&ok);
    if (!ok || day < 1 || day > 31) return false;

    // 月份天数验证
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    if (month == 2 && day > 29) {
        return false;
    }

    // 闰年验证（简化版，2月29日只在闰年有效）
    if (month == 2 && day == 29) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (!isLeapYear) {
            return false;
        }
    }

    return true;
}

bool AgendaManager::isValidTimeString(const QString &time) const
{
    static QRegularExpression timeRegex("^\\d{2}:\\d{2}$");
    if (!timeRegex.match(time).hasMatch()) {
        return false;
    }

    QStringList parts = time.split(':');
    if (parts.size() != 2) return false;

    bool ok;
    int hour = parts[0].toInt(&ok);
    if (!ok || hour < 0 || hour > 23) return false;

    int minute = parts[1].toInt(&ok);
    if (!ok || minute < 0 || minute > 59) return false;

    return true;
}

// ========== 属性访问器 ==========

int AgendaManager::itemCount() const
{
    return m_agenda->getItemCount();
}

QString AgendaManager::currentFilter() const
{
    return m_currentFilter;
}

bool AgendaManager::isLoading() const
{
    return m_isLoading;
}


bool AgendaManager::clearAll(){
    m_agenda->clearAll();
    return true;
}
