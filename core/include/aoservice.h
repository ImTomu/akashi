#ifndef AOSERVICE_H
#define AOSERVICE_H

#include <QObject>
#include <QtNetwork>
#include "aoclient.h"

enum RequestType {
    Get = 0,
    Post = 1
};

/*
 * External service for AO
 */

class AOService : QObject {
    Q_OBJECT

  public:
    /**
     * @brief Constructor for the AOService class.
     */
    explicit AOService();

    /**
     *  @brief Deconstructor for the AOService class.
     */
    ~AOService();

    /**
     * @brief Service address base Url
     */
    QString rootServiceAddress;

#pragma APIs {
    /**
     * @brief SrvGetVideo
     * @param url
     * @return
     */
    void SrvGetVideo(QString url, std::function<void(QString streamUrl)> response);
#pragma }

  private slots:

    /**
     * @brief Request for the AOService class with response callback.
     */
    void Request(QString apiPath, QUrlQuery params, RequestType requestType, std::map<QString, QString> data, std::function<void(QNetworkReply *reply)> response);

  private:
    /**
     * @brief Pointer to the network manager.
     */
    QNetworkAccessManager *m_manager;
};

#endif // AOSERVICE_H
