/**
  ******************************************************************************
  * @file           : global.cpp
  * @author         : 16649
  * @brief          : global.h的定义
  * @attention      : None
  * @date           : 24-7-16
  ******************************************************************************
 **/
#include "global.h"
std::function<void(QWidget*)>repolish =[](QWidget* w){
    w->style()->unpolish(w);
    w->style()->polish(w);
};

QString gate_url_prefix = "";
