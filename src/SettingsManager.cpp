#include "SettingsManager.h"
#include <QStandardPaths>
#include <QDir>

const QString SettingsManager::SETTING_DARK_THEME_ENABLED = "DarkThemeEnabled";
const QString SettingsManager::SETTING_DEFAULT_STYLE = "DefaultStyle";
const QString SettingsManager::SETTING_FIRST_START = "FirstAppStart";

SettingsManager::SettingsManager(QObject* parent)
    : QObject(parent)
{
    QString userPath = QDir::fromNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    userPath += QDir::separator();
    userPath += "qdarktheme.conf";
    m_settings = QSharedPointer<QSettings>(new QSettings(userPath, QSettings::IniFormat));

    if (!fileExists(userPath)) {
        updateValue(SETTING_DARK_THEME_ENABLED, false);
        updateValue(SETTING_DEFAULT_STYLE, QString(""));
        updateValue(SETTING_FIRST_START, true);
    } else {
        getBoolValue(SETTING_DARK_THEME_ENABLED);
        getStringValue(SETTING_DEFAULT_STYLE);
        getBoolValue(SETTING_FIRST_START);
    }
}

QString SettingsManager::getStringValue(const QString& key) const
{
    return m_settings->value(key).toString();
}

bool SettingsManager::getBoolValue(const QString &key) const
{
    return m_settings->value(key).toBool();
}

void SettingsManager::updateValue(const QString& key, const QVariant& value) const
{
    m_settings->setValue(key, value);
}

bool SettingsManager::fileExists(const QString& path)
{
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    return check_file.exists() && check_file.isFile();
}