#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "task1back.h"
#include "task2back.h"
#include "monthes_qml_env.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<task1back>("LabTasks", 1, 0, "Task1BackEnd");
    qmlRegisterType<task2back>("LabTasks", 1, 0, "Task2BackEnd");
    qmlRegisterUncreatableType<monthes_qml_env>("LabTasks", 1, 0, "monthes", "Do not try to instantinate this type!");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/LabWork1/main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
