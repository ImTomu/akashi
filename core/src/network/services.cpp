#include "include/aoservice.h"

void AOService::SrvGetVideo(QString url, std::function<void(QString streamUrl)> response)
{
    QUrlQuery params;
    params.addQueryItem("url", url);
    Request("Music/GetVideo", params, RequestType::Get, {}, [=] (QNetworkReply *f_reply) {
        QString strReply = (QString)f_reply->readAll();
        qDebug() << strReply;
        QJsonDocument json = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jObj = json.object();
        if (f_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
            qDebug().noquote() << "Data returned";
            qDebug().noquote() << jObj["isSucceed"].toBool();
            qDebug().noquote() << jObj["message"].toString();
            if (!jObj.isEmpty()) {
                if (jObj["isSucceed"].toBool()) {
                    qDebug().noquote() << "success.";
                    response(jObj["streamUrl"].toString());
                }
            }
        }
        else if (f_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() >= 400) {
            response(url);
        } else {
            qDebug() << json;
        }
        f_reply->deleteLater();
    });
}
