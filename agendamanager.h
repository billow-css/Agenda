#ifndef AGENDAMANAGER_H
#define AGENDAMANAGER_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QVariantMap>
#include <QRegularExpression>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <algorithm>
#include <cctype>
#include "../express_manager/test/core/Agenda.h"
#include "../express_manager/test/core/FileProcess.h"

class AgendaManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int itemCount READ itemCount NOTIFY dataChanged)
    Q_PROPERTY(QString currentFilter READ currentFilter NOTIFY filterChanged)
    Q_PROPERTY(bool isLoading READ isLoading NOTIFY loadingChanged)

public:
    explicit AgendaManager(QObject *parent = nullptr);
    ~AgendaManager();

    // 日程管理
    Q_INVOKABLE QVariantList getAllItems() const;
    Q_INVOKABLE QVariantMap getItem(int id) const;
    Q_INVOKABLE int addItem(const QString &name, const QString &desc,
                            const QString &ddl, const QString &time,
                            int priority, int status = 0);
    Q_INVOKABLE bool updateItem(int id, const QVariantMap &updates);
    Q_INVOKABLE bool removeItem(int id);
    Q_INVOKABLE bool removeItems(const QVariantList &ids);
    Q_INVOKABLE bool clearAll();

    // 智能输入处理
    Q_INVOKABLE QString processDateInput(const QString &input) const;
    Q_INVOKABLE QString fixTimeFormat(const QString &input) const;
    Q_INVOKABLE QString getTodayDate() const;
    Q_INVOKABLE QString getCurrentTime() const;

    // 排序和筛选
    Q_INVOKABLE void sortBy(int sortCode);
    Q_INVOKABLE void applyFilter(int filterCode, const QString &filterValue = "");
    Q_INVOKABLE void clearFilter();
    Q_INVOKABLE QVariantList searchItems(const QString &keyword) const;

    // 批量操作
    Q_INVOKABLE void markAsCompleted(int id);
    Q_INVOKABLE void toggleCompletion(int id);
    Q_INVOKABLE void markAsCompletedBatch(const QVariantList &ids);

    // 文件操作
    Q_INVOKABLE bool importFromCSV(const QString &filePath);
    Q_INVOKABLE bool exportToCSV(const QString &filePath);
    Q_INVOKABLE bool importFromTXT(const QString &filePath);
    Q_INVOKABLE bool exportToTXT(int id, const QString &filePath);

    // 自动保存/加载
    Q_INVOKABLE bool autoSave();
    Q_INVOKABLE bool autoLoad();

    // 工具函数
    Q_INVOKABLE QVariantList getStatusOptions() const;
    Q_INVOKABLE QVariantList getPriorityOptions() const;
    Q_INVOKABLE QString getStatusText(int status) const;
    Q_INVOKABLE QString getPriorityText(int priority) const;
    Q_INVOKABLE QString getStatusColor(int status) const;
    Q_INVOKABLE QString getPriorityColor(int priority) const;
    Q_INVOKABLE QVariantMap getStatistics() const;

    // 快速操作
    Q_INVOKABLE int quickAddItem(const QString &name, int priority = 3);
    Q_INVOKABLE void quickCompleteItem(int id);

    // 属性访问器
    int itemCount() const;
    QString currentFilter() const;
    bool isLoading() const;


signals:
    void dataChanged();
    void filterChanged();
    void loadingChanged();
    void errorOccurred(const QString &message);
    void operationCompleted(const QString &message);
    void itemAdded(int id);
    void itemRemoved(int id);
    void itemUpdated(int id);
    void itemsImported(int count);

private:
    Agenda *m_agenda;
    QString m_currentFilter;
    int m_currentSortType;
    bool m_isLoading;

    // 辅助函数
    QString trimWhitespace(const QString &str) const;
    QString padZero(int num) const;
    bool isAllDigit(const QString &str) const;
    QVariantMap agendaItemToMap(const AgendaItem &item) const;
    AgendaItem mapToAgendaItem(const QVariantMap &map) const;
    std::vector<AgendaItem> getCurrentItems() const;

    // 日期时间验证
    bool isValidDateString(const QString &date) const;
    bool isValidTimeString(const QString &time) const;
};

#endif // AGENDAMANAGER_H
