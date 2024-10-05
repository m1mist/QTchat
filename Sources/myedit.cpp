/**
  ******************************************************************************
  * @file           : myedit.cpp
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-3
  ******************************************************************************
 **/

// You may need to build the project (run Qt uic code generator) to get "ui_MyEdit.h" resolved

#include "Headers/myedit.h"
#include "Forms/ui_MyEdit.h"


MyEdit::MyEdit(QWidget *parent) :
    QLineEdit(parent), ui(new Ui::MyEdit), max_len(0) {
    ui->setupUi(this);
}

void MyEdit::focusOutEvent(QFocusEvent *event) {
    QLineEdit::focusOutEvent(event);
    emit sig_focos_out();
}

void MyEdit::LimitTextLength(QString text) {
    if (max_len <= 0) {
        return;
    }
    QByteArray byte_array = text.toUtf8();
    if (byte_array.size()>=max_len) {
        byte_array = byte_array.left(max_len);
        this->setText(QString::fromUtf8(byte_array));
    }
}

MyEdit::~MyEdit() {
    delete ui;
}
