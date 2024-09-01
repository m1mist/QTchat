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

std::function<QString(QString)> xor_string = [](QString input){
    QString result = input;
    int length = input.length();
    length = length % 255;
    for (int i = 0; i < length; ++i) {
        result[i] = QChar(static_cast<ushort>(input[i].unicode() ^ static_cast<ushort>(length)));
    }
    return result;
};

QString gate_url_prefix = "";
