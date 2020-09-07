#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick>
#include <engine.h>
#include <qmlconnector.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType <QmlConnector> ("blurEngine", 1, 0, "QmlConnector");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/face.qml")));
    return app.exec();
}
