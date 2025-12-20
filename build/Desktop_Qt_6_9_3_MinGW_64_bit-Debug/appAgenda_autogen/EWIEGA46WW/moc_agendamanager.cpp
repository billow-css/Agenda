/****************************************************************************
** Meta object code from reading C++ file 'agendamanager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../agendamanager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'agendamanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN13AgendaManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto AgendaManager::qt_create_metaobjectdata<qt_meta_tag_ZN13AgendaManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "AgendaManager",
        "dataChanged",
        "",
        "filterChanged",
        "loadingChanged",
        "errorOccurred",
        "message",
        "operationCompleted",
        "itemAdded",
        "id",
        "itemRemoved",
        "itemUpdated",
        "itemsImported",
        "count",
        "getAllItems",
        "QVariantList",
        "getItem",
        "QVariantMap",
        "addItem",
        "name",
        "desc",
        "ddl",
        "time",
        "priority",
        "status",
        "updateItem",
        "updates",
        "removeItem",
        "removeItems",
        "ids",
        "clearAll",
        "processDateInput",
        "input",
        "fixTimeFormat",
        "getTodayDate",
        "getCurrentTime",
        "sortBy",
        "sortCode",
        "applyFilter",
        "filterCode",
        "filterValue",
        "clearFilter",
        "searchItems",
        "keyword",
        "markAsCompleted",
        "toggleCompletion",
        "markAsCompletedBatch",
        "importFromCSV",
        "filePath",
        "exportToCSV",
        "importFromTXT",
        "exportToTXT",
        "autoSave",
        "autoLoad",
        "getStatusOptions",
        "getPriorityOptions",
        "getStatusText",
        "getPriorityText",
        "getStatusColor",
        "getPriorityColor",
        "getStatistics",
        "quickAddItem",
        "quickCompleteItem",
        "itemCount",
        "currentFilter",
        "isLoading"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'dataChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'filterChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'loadingChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'errorOccurred'
        QtMocHelpers::SignalData<void(const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Signal 'operationCompleted'
        QtMocHelpers::SignalData<void(const QString &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Signal 'itemAdded'
        QtMocHelpers::SignalData<void(int)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 9 },
        }}),
        // Signal 'itemRemoved'
        QtMocHelpers::SignalData<void(int)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 9 },
        }}),
        // Signal 'itemUpdated'
        QtMocHelpers::SignalData<void(int)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 9 },
        }}),
        // Signal 'itemsImported'
        QtMocHelpers::SignalData<void(int)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 13 },
        }}),
        // Method 'getAllItems'
        QtMocHelpers::MethodData<QVariantList() const>(14, 2, QMC::AccessPublic, 0x80000000 | 15),
        // Method 'getItem'
        QtMocHelpers::MethodData<QVariantMap(int) const>(16, 2, QMC::AccessPublic, 0x80000000 | 17, {{
            { QMetaType::Int, 9 },
        }}),
        // Method 'addItem'
        QtMocHelpers::MethodData<int(const QString &, const QString &, const QString &, const QString &, int, int)>(18, 2, QMC::AccessPublic, QMetaType::Int, {{
            { QMetaType::QString, 19 }, { QMetaType::QString, 20 }, { QMetaType::QString, 21 }, { QMetaType::QString, 22 },
            { QMetaType::Int, 23 }, { QMetaType::Int, 24 },
        }}),
        // Method 'addItem'
        QtMocHelpers::MethodData<int(const QString &, const QString &, const QString &, const QString &, int)>(18, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Int, {{
            { QMetaType::QString, 19 }, { QMetaType::QString, 20 }, { QMetaType::QString, 21 }, { QMetaType::QString, 22 },
            { QMetaType::Int, 23 },
        }}),
        // Method 'updateItem'
        QtMocHelpers::MethodData<bool(int, const QVariantMap &)>(25, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 9 }, { 0x80000000 | 17, 26 },
        }}),
        // Method 'removeItem'
        QtMocHelpers::MethodData<bool(int)>(27, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 9 },
        }}),
        // Method 'removeItems'
        QtMocHelpers::MethodData<bool(const QVariantList &)>(28, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { 0x80000000 | 15, 29 },
        }}),
        // Method 'clearAll'
        QtMocHelpers::MethodData<bool()>(30, 2, QMC::AccessPublic, QMetaType::Bool),
        // Method 'processDateInput'
        QtMocHelpers::MethodData<QString(const QString &) const>(31, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::QString, 32 },
        }}),
        // Method 'fixTimeFormat'
        QtMocHelpers::MethodData<QString(const QString &) const>(33, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::QString, 32 },
        }}),
        // Method 'getTodayDate'
        QtMocHelpers::MethodData<QString() const>(34, 2, QMC::AccessPublic, QMetaType::QString),
        // Method 'getCurrentTime'
        QtMocHelpers::MethodData<QString() const>(35, 2, QMC::AccessPublic, QMetaType::QString),
        // Method 'sortBy'
        QtMocHelpers::MethodData<void(int)>(36, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 37 },
        }}),
        // Method 'applyFilter'
        QtMocHelpers::MethodData<void(int, const QString &)>(38, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 39 }, { QMetaType::QString, 40 },
        }}),
        // Method 'applyFilter'
        QtMocHelpers::MethodData<void(int)>(38, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::Int, 39 },
        }}),
        // Method 'clearFilter'
        QtMocHelpers::MethodData<void()>(41, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'searchItems'
        QtMocHelpers::MethodData<QVariantList(const QString &) const>(42, 2, QMC::AccessPublic, 0x80000000 | 15, {{
            { QMetaType::QString, 43 },
        }}),
        // Method 'markAsCompleted'
        QtMocHelpers::MethodData<void(int)>(44, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 9 },
        }}),
        // Method 'toggleCompletion'
        QtMocHelpers::MethodData<void(int)>(45, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 9 },
        }}),
        // Method 'markAsCompletedBatch'
        QtMocHelpers::MethodData<void(const QVariantList &)>(46, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 15, 29 },
        }}),
        // Method 'importFromCSV'
        QtMocHelpers::MethodData<bool(const QString &)>(47, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 48 },
        }}),
        // Method 'exportToCSV'
        QtMocHelpers::MethodData<bool(const QString &)>(49, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 48 },
        }}),
        // Method 'importFromTXT'
        QtMocHelpers::MethodData<bool(const QString &)>(50, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 48 },
        }}),
        // Method 'exportToTXT'
        QtMocHelpers::MethodData<bool(int, const QString &)>(51, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 9 }, { QMetaType::QString, 48 },
        }}),
        // Method 'autoSave'
        QtMocHelpers::MethodData<bool()>(52, 2, QMC::AccessPublic, QMetaType::Bool),
        // Method 'autoLoad'
        QtMocHelpers::MethodData<bool()>(53, 2, QMC::AccessPublic, QMetaType::Bool),
        // Method 'getStatusOptions'
        QtMocHelpers::MethodData<QVariantList() const>(54, 2, QMC::AccessPublic, 0x80000000 | 15),
        // Method 'getPriorityOptions'
        QtMocHelpers::MethodData<QVariantList() const>(55, 2, QMC::AccessPublic, 0x80000000 | 15),
        // Method 'getStatusText'
        QtMocHelpers::MethodData<QString(int) const>(56, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::Int, 24 },
        }}),
        // Method 'getPriorityText'
        QtMocHelpers::MethodData<QString(int) const>(57, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::Int, 23 },
        }}),
        // Method 'getStatusColor'
        QtMocHelpers::MethodData<QString(int) const>(58, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::Int, 24 },
        }}),
        // Method 'getPriorityColor'
        QtMocHelpers::MethodData<QString(int) const>(59, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::Int, 23 },
        }}),
        // Method 'getStatistics'
        QtMocHelpers::MethodData<QVariantMap() const>(60, 2, QMC::AccessPublic, 0x80000000 | 17),
        // Method 'quickAddItem'
        QtMocHelpers::MethodData<int(const QString &, int)>(61, 2, QMC::AccessPublic, QMetaType::Int, {{
            { QMetaType::QString, 19 }, { QMetaType::Int, 23 },
        }}),
        // Method 'quickAddItem'
        QtMocHelpers::MethodData<int(const QString &)>(61, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Int, {{
            { QMetaType::QString, 19 },
        }}),
        // Method 'quickCompleteItem'
        QtMocHelpers::MethodData<void(int)>(62, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 9 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'itemCount'
        QtMocHelpers::PropertyData<int>(63, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'currentFilter'
        QtMocHelpers::PropertyData<QString>(64, QMetaType::QString, QMC::DefaultPropertyFlags, 1),
        // property 'isLoading'
        QtMocHelpers::PropertyData<bool>(65, QMetaType::Bool, QMC::DefaultPropertyFlags, 2),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<AgendaManager, qt_meta_tag_ZN13AgendaManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject AgendaManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13AgendaManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13AgendaManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13AgendaManagerE_t>.metaTypes,
    nullptr
} };

void AgendaManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AgendaManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->dataChanged(); break;
        case 1: _t->filterChanged(); break;
        case 2: _t->loadingChanged(); break;
        case 3: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->operationCompleted((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->itemAdded((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->itemRemoved((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->itemUpdated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->itemsImported((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: { QVariantList _r = _t->getAllItems();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 10: { QVariantMap _r = _t->getItem((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 11: { int _r = _t->addItem((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 12: { int _r = _t->addItem((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 13: { bool _r = _t->updateItem((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariantMap>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 14: { bool _r = _t->removeItem((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 15: { bool _r = _t->removeItems((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 16: { bool _r = _t->clearAll();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 17: { QString _r = _t->processDateInput((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 18: { QString _r = _t->fixTimeFormat((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 19: { QString _r = _t->getTodayDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 20: { QString _r = _t->getCurrentTime();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 21: _t->sortBy((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 22: _t->applyFilter((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 23: _t->applyFilter((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 24: _t->clearFilter(); break;
        case 25: { QVariantList _r = _t->searchItems((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 26: _t->markAsCompleted((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 27: _t->toggleCompletion((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 28: _t->markAsCompletedBatch((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1]))); break;
        case 29: { bool _r = _t->importFromCSV((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 30: { bool _r = _t->exportToCSV((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 31: { bool _r = _t->importFromTXT((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 32: { bool _r = _t->exportToTXT((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 33: { bool _r = _t->autoSave();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 34: { bool _r = _t->autoLoad();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 35: { QVariantList _r = _t->getStatusOptions();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 36: { QVariantList _r = _t->getPriorityOptions();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 37: { QString _r = _t->getStatusText((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 38: { QString _r = _t->getPriorityText((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 39: { QString _r = _t->getStatusColor((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 40: { QString _r = _t->getPriorityColor((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 41: { QVariantMap _r = _t->getStatistics();
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 42: { int _r = _t->quickAddItem((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 43: { int _r = _t->quickAddItem((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 44: _t->quickCompleteItem((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (AgendaManager::*)()>(_a, &AgendaManager::dataChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (AgendaManager::*)()>(_a, &AgendaManager::filterChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (AgendaManager::*)()>(_a, &AgendaManager::loadingChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (AgendaManager::*)(const QString & )>(_a, &AgendaManager::errorOccurred, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (AgendaManager::*)(const QString & )>(_a, &AgendaManager::operationCompleted, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (AgendaManager::*)(int )>(_a, &AgendaManager::itemAdded, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (AgendaManager::*)(int )>(_a, &AgendaManager::itemRemoved, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (AgendaManager::*)(int )>(_a, &AgendaManager::itemUpdated, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (AgendaManager::*)(int )>(_a, &AgendaManager::itemsImported, 8))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<int*>(_v) = _t->itemCount(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->currentFilter(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->isLoading(); break;
        default: break;
        }
    }
}

const QMetaObject *AgendaManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AgendaManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13AgendaManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AgendaManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 45)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 45;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 45)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 45;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void AgendaManager::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AgendaManager::filterChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AgendaManager::loadingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void AgendaManager::errorOccurred(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void AgendaManager::operationCompleted(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void AgendaManager::itemAdded(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void AgendaManager::itemRemoved(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void AgendaManager::itemUpdated(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}

// SIGNAL 8
void AgendaManager::itemsImported(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1);
}
QT_WARNING_POP
