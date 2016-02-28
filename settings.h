#ifndef SETTINGS_H
#define SETTINGS_H
#include <QString>
#include <QVariant>
#include <QSettings>

class Settings : public QSettings
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0):
        QSettings ("/mnt/config/carta.ini", QSettings::IniFormat, parent) {};
    Q_INVOKABLE inline void setValue(const QString &key, const QVariant &value) { QSettings::setValue(key, value); }
    Q_INVOKABLE inline QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const { return QSettings::value(key, defaultValue); }
};

#endif // SETTINGS_H
