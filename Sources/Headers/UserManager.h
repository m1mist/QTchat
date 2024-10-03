/**
  ******************************************************************************
  * @file           : UserManager.h
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-9-25
  ******************************************************************************
 **/

#ifndef LLFCCHAT_USERMANAGER_H
#define LLFCCHAT_USERMANAGER_H
#include "global.h"
#include "singleton.hpp"

class UserManager: public QObject,public Singleton<UserManager>, public std::enable_shared_from_this<UserManager>{
    Q_OBJECT
public:
    friend class Singleton<UserManager>;
    ~UserManager() = default;
    void SetName(QString name);
    void SetUid(int uid);
    void SetToken(QString token);
private:
    UserManager() = default;
    QString name_;
    QString token_;
    int uid_;
};


#endif //LLFCCHAT_USERMANAGER_H
