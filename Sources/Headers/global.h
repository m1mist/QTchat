/**
  ******************************************************************************
  * @file           : global.h
  * @author         : 16649
  * @brief          : None
  * @attention      : None
  * @date           : 24-7-16
  ******************************************************************************
 **/

#ifndef LLFCCHAT_GLOBAL_H
#define LLFCCHAT_GLOBAL_H
#include <QWidget>
#include <QJsonObject>
#include <QSettings>
#include <QDir>
#include "QStyle"
#include <QRegularExpression>
#include <QByteArray>
#include <QNetworkReply>

#include <memory>
#include <iostream>
#include <mutex>
#include <functional>

/**
 * @brief repolish 用于刷新qss
 */
extern std::function<void(QWidget*)> repolish;

enum ReqId{
    ID_GET_AUTH = 1001,//获取验证码
    ID_REGISTER_USER = 1002, //注册用户
};

enum Modules{
    REGISTER = 0,
};

enum ErrorCodes{
    SUCCESS = 0,
    ERROR_JSON = 1,//json解析失败
    ERROR_NETWORK = 2,//网络错误
};
enum TipErr{
    TIP_SUCCESS = 0,
    TIP_EMAIL_ERR = 1,
    TIP_PWD_ERR = 2,
    TIP_CONFIRM_ERR = 3,
    TIP_PWD_CONFIRM = 4,
    TIP_VARIFY_ERR = 5,
    TIP_USER_ERR = 6
};

extern QString gate_url_prefix;

#endif //LLFCCHAT_GLOBAL_H
