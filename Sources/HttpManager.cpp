/**
  ******************************************************************************
  * @file           : HttpManager.cpp
  * @author         : 16649
  * @brief          : None
  * @attention      : None
  * @date           : 24-7-17
  ******************************************************************************
 **/

#include "HttpManager.h"

HttpManager::HttpManager() {
    connect(this, &HttpManager::sig_http_finish, this, &HttpManager::slot_http_finish);
}

HttpManager::~HttpManager() = default;

void HttpManager::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod) {
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentTypeHeader, QByteArray::number(data.length()));
    auto self = shared_from_this();
    QNetworkReply* reply = manager_.post(request, data);

    QObject::connect(reply, &QNetworkReply::finished, [self, reply, req_id, mod](){
        //错误处理
        if(reply->error() != QNetworkReply::NoError){
            qDebug() << reply->errorString();
            //发送signal通知完成
            emit self->sig_http_finish(req_id, "", ErrorCodes::ERROR_NETWORK, mod);
            reply->deleteLater();
            return ;
        }

        QString res = reply->readAll();
        //发送signal通知完成
        emit self->sig_http_finish(req_id, res, ErrorCodes::SUCCESS, mod);
        reply->deleteLater();
        return;
    });
}

void HttpManager::slot_http_finish(ReqId id, QString str, ErrorCodes err, Modules mod) {
    //发送信号通知指定模块http响应结束
    if(mod == Modules::REGISTER){
        emit sig_reg_mod_finish(id, str, err);
    }
    if(mod == Modules::RESET){
        emit sig_reset_mod_finish(id, str, err);
    }
    if(mod == Modules::LOGIN){
        emit sig_login_mod_finish(id, str, err);
    }
}
