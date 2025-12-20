#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include "AgendaManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // 设置应用程序信息
    app.setApplicationName("Agenda");
    app.setOrganizationName("AgendaSoft");
    app.setOrganizationDomain("agendasoft.com");
    // app.setWindowIcon(QIcon(":/images/calendar.png"));

    // 创建AgendaManager实例
    AgendaManager agendaManager;

    QQmlApplicationEngine engine;

    // 注册C++类到QML上下文
    engine.rootContext()->setContextProperty("agendaManager", &agendaManager);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);
    engine.loadFromModule("Agenda", "Main");

    return app.exec();
}
