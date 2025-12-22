#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCoreApplication>
#include <QIcon>
#include "AgendaManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/logo/ico.png"));
    // 设置应用程序信息
    app.setApplicationName("Agenda");
    app.setOrganizationName("AgendaSoft");
    app.setOrganizationDomain("agendasoft.com");
    // app.setWindowIcon(QIcon(":/images/calendar.png"));

    // 创建AgendaManager实例
    AgendaManager agendaManager;

    QQmlApplicationEngine engine;

    // 获取程序运行目录（绝对路径）
    QString appDir = QCoreApplication::applicationDirPath();
    // 把路径暴露给QML，命名为 "appDirPath"
    engine.rootContext()->setContextProperty("appDirPath", appDir);

    // 注册C++类到QML上下文
    engine.rootContext()->setContextProperty("agendaManager", &agendaManager);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);
    engine.loadFromModule("Agenda", "Main");

    return app.exec();
}
