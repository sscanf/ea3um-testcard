#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QQmlContext>
#include "settings.h"

Q_DECLARE_METATYPE(Settings*)

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Settings *settings = new Settings ();
    engine.rootContext()->setContextProperty("Settings",settings);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
