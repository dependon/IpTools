#include "inimanager.h"
#include <QDir>
#include <QDebug>
#include <QTextStream>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

const QString CONFIG_PATH =   QDir::homePath() +
        "/.config/iptools/config.ini";


IniManager::IniManager(QObject *parent)
    :QObject(parent)
{
    qDebug()<< CONFIG_PATH;
    m_settings =new QSettings(CONFIG_PATH, QSettings::IniFormat);
}

IniManager *IniManager::instance()
{
    static IniManager *pInstance = nullptr;
    if (nullptr == pInstance)
    {
        pInstance = new IniManager();
    }
    return pInstance;
}

void IniManager::setValue(const QString &key, const QVariant &value)
{
    m_settings->setValue(key,value);
}

QVariant IniManager::value(const QString &key, const QVariant &defaultValue) const
{
    return m_settings->value(key,defaultValue);
}

void IniManager::remove(const QString &key)
{
    return m_settings->remove(key);
}

bool IniManager::contains(const QString &key) const
{
    return m_settings->contains(key);
}

void IniManager::clear()
{
    m_settings->clear();
}
