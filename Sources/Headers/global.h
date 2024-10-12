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
#include <QByteArray>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QRegularExpression>
#include <QSettings>
#include <QStyle>
#include <QWidget>

#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <utility>
/**
 * @brief repolish 用于刷新qss
 */
extern std::function<void(QWidget*)> repolish;

extern std::function<QString(QString)> xor_string;

enum ReqId{
    ID_GET_VERIFY = 1001,//获取验证码
    ID_REGISTER_USER = 1002, //注册用户
    ID_RESET_PWD = 1003, //重置密码
    ID_LOGIN_USER = 1004, //用户登录
    ID_CHAT_LOGIN = 1005, //登陆聊天服务器
    ID_CHAT_LOGIN_RSP= 1006, //登陆聊天服务器回包
    ID_SEARCH_USER_REQ = 1007, //用户搜索请求
    ID_SEARCH_USER_RSP = 1008, //搜索用户回包
    ID_ADD_FRIEND_REQ = 1009,  //添加好友申请
    ID_ADD_FRIEND_RSP = 1010, //申请添加好友回复
    ID_NOTIFY_ADD_FRIEND_REQ = 1011,  //通知用户添加好友申请
    ID_AUTH_FRIEND_REQ = 1013,  //认证好友请求
    ID_AUTH_FRIEND_RSP = 1014,  //认证好友回复
    ID_NOTIFY_AUTH_FRIEND_REQ = 1015, //通知用户认证好友申请
    ID_TEXT_CHAT_MSG_REQ  = 1017,  //文本聊天信息请求
    ID_TEXT_CHAT_MSG_RSP  = 1018,  //文本聊天信息回复
    ID_NOTIFY_TEXT_CHAT_MSG_REQ = 1019, //通知用户文本聊天信息
};

enum Modules{
    REGISTER = 0,
    RESET    = 1,
    LOGIN    = 2,
};

enum ErrorCodes{
    SUCCESS = 0,
    ERROR_JSON = 1,//json解析失败
    ERROR_NETWORK = 2,//网络错误
};
enum TipErr{
    TIP_SUCCESS = 0,    //成功
    TIP_EMAIL_ERR = 1,  //邮箱错误
    TIP_PWD_ERR = 2,    //密码错误
    TIP_CONFIRM_ERR = 3,//确认密码错误
    TIP_PWD_CONFIRM = 4,//
    TIP_VARIFY_ERR = 5, //验证码错误
    TIP_USER_ERR = 6    //用户名错误
};

enum ChatUiMode {
    SEARCH,     //搜索
    CHAT,       //聊天
    CONTACTS,   //联系人
};

enum ListItemType {
    CHAT_ITEM,
    CONTACTS_ITEM,
    SEARCH_RESULT_ITEM,
    ADD_USER_TIP_ITEM,
    INVALID_ITEM,
    GROUP_TIP_ITEM
};

enum class ChatRole
{

    Self,
    Other
};
extern QString gate_url_prefix;

//一个Label有六种状态，普通状态，普通的悬浮状态，普通的点击状态，选中状态，选中的悬浮状态，选中的点击状态。
//当Label处于普通状态，被点击后，切换为选中状态，再次点击又切换为普通状态。
//ClickLbState定义在global.h中，包含两种状态一个是普通状态，一个是选中状态。而Label中的六种状态就是基于这两种状态嵌套实现的。
enum ClickLbState{
    Normal = 0,
    Selected = 1
};

struct ServerInfo{
    QString host;
    QString port;
    QString token;
    int uid;
};
#endif //LLFCCHAT_GLOBAL_H
