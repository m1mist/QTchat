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

}

HttpManager::~HttpManager() {

}

void HttpManager::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod) {
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentTypeHeader, QByteArray::number(data.length()));
    auto self = shared_from_this();
    QNetworkReply* reply = manager_.post(request, data);

    QObject::connect(reply, &QNetworkReply::finished, [self, reply, req_id, mod](){
        //错误处理
    });
}
