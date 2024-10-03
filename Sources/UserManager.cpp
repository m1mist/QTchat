/**
  ******************************************************************************
  * @file           : UserManager.cpp
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-9-25
  ******************************************************************************
 **/

#include "UserManager.h"

void UserManager::SetName(QString name) {
    name_ = std::move(name);
}

void UserManager::SetUid(const int uid) {
    uid_ = uid;
}

void UserManager::SetToken(QString token) {
    token_ = std::move(token);
}
