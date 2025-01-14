#include "ipapirequest.h"


IpApiRequest::IpApiRequest(QObject *parent) : QObject(parent),
    manager(new QNetworkAccessManager(this))
{
}

void IpApiRequest::queryIpInfo(const QString &ipAddress, const QString &lang)
{
    QString urlStr = "http://ip-api.com/json/" + ipAddress;
    if(!lang.isEmpty())
    {
        urlStr = urlStr+"?lang="+lang;
    }
    QUrl url(urlStr);

    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &IpApiRequest::onReplyFinished);
}

void IpApiRequest::onReplyFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            QString country = jsonObj.value("country").toString();
            QString regionName = jsonObj.value("regionName").toString();
            QString city = jsonObj.value("city").toString();
            QString isp = jsonObj.value("isp").toString();
            QString query = jsonObj.value("query").toString();

            QString status = jsonObj.value("status").toString();


            if(status == "fail")
            {
              emit errorOccurred("ERROR");
            }
            else {
              emit ipInfoReceived(country, regionName, city, isp,query);
            }
//            qDebug() << "国家:" << country;
//            qDebug() << "地区:" << regionName;
//            qDebug() << "城市:" << city;
//            qDebug() << "ISP:" << isp;

        } else {
            qDebug() << "ERROR";
            emit errorOccurred("ERROR");
        }
    } else {
        qDebug() << "ERROR:" << reply->errorString();
        emit errorOccurred(reply->errorString());
    }
    reply->deleteLater();
}
