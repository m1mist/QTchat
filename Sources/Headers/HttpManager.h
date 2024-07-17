/**
  ******************************************************************************
  * @file           : HttpManager.h
  * @author         : 16649
  * @brief          : None
  * @attention      : None
  * @date           : 24-7-17
  ******************************************************************************
 **/

#ifndef LLFCCHAT_HTTPMANAGER_H
#define LLFCCHAT_HTTPMANAGER_H
#include "singleton.hpp"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include "global.h"

class HttpManager: public QObject, public Singleton<HttpManager>,
        public std::enable_shared_from_this<HttpManager>{
    Q_OBJECT
public:
    ~HttpManager();
private:
    friend class Singleton<HttpManager>;
    HttpManager();
    QNetworkAccessManager manager_;
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);
signals:
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
};


#endif //LLFCCHAT_HTTPMANAGER_H
