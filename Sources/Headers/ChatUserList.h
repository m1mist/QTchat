/**
  ******************************************************************************
  * @file           : ChatUserList.h
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-4
  ******************************************************************************
 **/

#ifndef CHATUSERLIST_H
#define CHATUSERLIST_H
#include <QListWidget>
#include <QWheelEvent>
#include <QEvent>
#include <QScrollBar>
#include <QDebug>


class ChatUserList:public QListWidget {
    Q_OBJECT;
public:
    ChatUserList(QWidget* parent = nullptr);

protected:
    //滚动条
    bool eventFilter(QObject *watched, QEvent *event) override;

signals:
    void sig_load_chat_user();
};



#endif //CHATUSERLIST_H
