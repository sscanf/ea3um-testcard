#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QQmlContext>
#include <QDebug>
#include <QtQml>
#include "settings.h"
#include "filter.h"

Q_DECLARE_METATYPE(Settings*)

int main(int argc, char *argv[])
{
    qmlRegisterType<MyFilter>("OFilter", 1, 0, "MyFilter");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Settings            *pSettings = new Settings;
//    MyFilter            *pFilter   = new MyFilter;


    engine.rootContext()->setContextProperty("Settings",pSettings);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
