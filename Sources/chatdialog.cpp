/**
  ******************************************************************************
  * @file           : chatdialog.cpp
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-1
  ******************************************************************************
 **/

// You may need to build the project (run Qt uic code generator) to get "ui_ChatDialog.h" resolved

#include "Headers/chatdialog.h"
#include "Forms/ui_ChatDialog.h"


ChatDialog::ChatDialog(QWidget *parent) :
    QWidget(parent), ui(new Ui::ChatDialog) {
    ui->setupUi(this);
    ui->button_plus->SetState("normal","hover","press");
}

ChatDialog::~ChatDialog() {
    delete ui;
}
