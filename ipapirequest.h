#ifndef IPAPIREQUEST_H
#define IPAPIREQUEST_H

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

class IpApiRequest : public QObject
{
    Q_OBJECT
public:
    IpApiRequest(QObject *parent = nullptr);
    // 定义一个公共接口函数，用于查询指定IP地址的信息
    void queryIpInfo(const QString& ipAddress ,const QString & lang);
private slots:
    void onReplyFinished();

signals:
    // 定义信号，当IP信息接收成功时发出
    void ipInfoReceived(const QString& country, const QString& regionName, const QString& city, const QString& isp,const QString & query);
    // 定义信号，当出现错误时发出
    void errorOccurred(const QString& errorMessage);

private:
    QNetworkAccessManager *manager;
};

#endif // IPAPIREQUEST_H
