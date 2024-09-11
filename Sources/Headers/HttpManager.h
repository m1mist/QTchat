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
#include <QJsonDocument>
#include "global.h"

class HttpManager: public QObject, public Singleton<HttpManager>,
        public std::enable_shared_from_this<HttpManager>{
    Q_OBJECT
public:
    ~HttpManager();
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);

private:
    friend class Singleton<HttpManager>;
    HttpManager();
    QNetworkAccessManager manager_;

private slots:
    //槽：http响应结束
    void slot_http_finish(ReqId id, QString str, ErrorCodes err, Modules mod);

signals:
    void sig_http_finish(ReqId id, QString str, ErrorCodes err, Modules mod);
    void sig_reg_mod_finish(ReqId id, QString str, ErrorCodes err);
    void sig_reset_mod_finish(ReqId id, QString str, ErrorCodes err);
    void sig_login_mod_finish(ReqId id, QString str, ErrorCodes err);
};


#endif //LLFCCHAT_HTTPMANAGER_H
