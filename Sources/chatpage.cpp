/**
  ******************************************************************************
  * @file           : chatpage.cpp
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-5
  ******************************************************************************
 **/

// You may need to build the project (run Qt uic code generator) to get "ui_ChatPage.h" resolved

#include "Headers/chatpage.h"

#include <QStyleOption>
#include <QPainter>
#include "Forms/ui_ChatPage.h"


ChatPage::ChatPage(QWidget *parent) :
    QWidget(parent), ui(new Ui::ChatPage) {
    ui->setupUi(this);
    //设置按钮样式
    ui->button_receive->SetState("normal","hover","press");
    ui->button_send->SetState("normal","hover","press");

    //设置图标样式
    ui->label_emoji->SetState("normal","hover","press","normal","hover","press");
    ui->label_send_file->SetState("normal","hover","press","normal","hover","press");
}

ChatPage::~ChatPage() {
    delete ui;
}

void ChatPage::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

}
