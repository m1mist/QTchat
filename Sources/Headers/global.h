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

extern std::function<QString(QString)> xor_string;

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

//一个Label有六种状态，普通状态，普通的悬浮状态，普通的点击状态，选中状态，选中的悬浮状态，选中的点击状态。
//当Label处于普通状态，被点击后，切换为选中状态，再次点击又切换为普通状态。
//ClickLbState定义在global.h中，包含两种状态一个是普通状态，一个是选中状态。而Label中的六种状态就是基于这两种状态嵌套实现的。
enum ClickLbState{
    Normal = 0,
    Selected = 1
};
#endif //LLFCCHAT_GLOBAL_H
