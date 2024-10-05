/**
  ******************************************************************************
  * @file           : widgetchatuser.cpp
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-4
  ******************************************************************************
 **/

// You may need to build the project (run Qt uic code generator) to get "ui_WidgetChatUser.h" resolved

#include "Headers/widgetchatuser.h"
#include "Forms/ui_WidgetChatUser.h"


WidgetChatUser::WidgetChatUser(QWidget *parent) :
    ListItem(parent), ui(new Ui::WidgetChatUser) {
    ui->setupUi(this);
    SetItemType(CHAT_ITEM);
}

WidgetChatUser::~WidgetChatUser() {
    delete ui;
}

void WidgetChatUser::SetInfo(QString name, QString head, QString msg) {
    _name = name;
    _head = head;
    _msg = msg;
    // 加载图片
    QPixmap pixmap(_head);

    // 设置图片自动缩放
    ui->profile_icon->setPixmap(pixmap.scaled(ui->profile_icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->profile_icon->setScaledContents(true);

    ui->label_user->setText(_name);
    ui->label_chat->setText(_msg);

}
