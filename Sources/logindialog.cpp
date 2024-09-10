/**
  ******************************************************************************
  * @file           : logindialog.cpp
  * @author         : 16649
  * @brief          : None
  * @attention      : None
  * @date           : 24-7-11
  ******************************************************************************
 **/

// You may need to build the project (run Qt uic code generator) to get "ui_LoginDialog.h" resolved

#include "logindialog.h"
#include "Forms/ui_LoginDialog.h"


LoginDialog::LoginDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::LoginDialog) {
    ui->setupUi(this);
    connect(ui->register_button, &QPushButton::clicked, this, &LoginDialog::switchRegister);
    ui->forget_label->SetState("normal","hover","","selected","selected_hover","");
    connect(ui->forget_label, &ClickedLabel::clicked, this, &LoginDialog::slot_forget_pwd);
}

LoginDialog::~LoginDialog() {
    delete ui;
}

void LoginDialog::slot_forget_pwd() {
    qDebug()<<"slot forget pwd";
    emit switchReset();
}


