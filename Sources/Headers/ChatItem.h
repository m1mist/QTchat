/**
  ******************************************************************************
  * @file           : ChatItem.h
  * @author         : hupujun
  * @brief          : 聊天区域内容，包括气泡、名字、头像
  * @attention      : None
  * @date           : 24-10-8
  ******************************************************************************
 **/

#ifndef CHATITEM_H
#define CHATITEM_H
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "global.h"
class Bubble;

class ChatItem:public QWidget{
    Q_OBJECT
public:
    explicit ChatItem(ChatRole role, QWidget *parent = nullptr);
    void setUserName(const QString &name) const;
    void setUserIcon(const QPixmap &icon) const;
    void setWidget(QWidget *w);

private:
    ChatRole role_;
    QLabel *p_name_label_;
    QLabel *p_icon_label_;
    QWidget *p_bubble_widget_;
};



#endif //CHATITEM_H
