#include "include/aoservice.h"

#include "include/config_manager.h"

AOService::AOService()
{
    m_manager = new QNetworkAccessManager();
    rootServiceAddress = ConfigManager::serviceAddress();
}

AOService::~AOService()
{
    m_manager->deleteLater();
}

void AOService::Request(QString apiPath, QUrlQuery params, RequestType requestType, std::map<QString, QString> data, std::function<void(QNetworkReply *reply)> response)
{
    QUrl url (rootServiceAddress + "/" + apiPath);
    if (!params.queryItems().empty()) {
        url.setQuery(params);
    }
    if (url.isValid()) {

        connect(m_manager, &QNetworkAccessManager::finished,
                this, response);
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        if (requestType == RequestType::Post) {
            QJsonObject l_json;
            for (std::map<QString,QString>::iterator it=data.begin(); it!=data.end(); ++it) {
                l_json[it->first] = it->second;
            }
            m_manager->post(request, QJsonDocument(l_json).toJson());
        }
        else
        {
            m_manager->get(request);

        }
        return;
    }
    return;
}
