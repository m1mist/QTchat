/**
  ******************************************************************************
  * @file           : MainWindow.cpp
  * @author         : 16649
  * @brief          : None
  * @attention      : None
  * @date           : 24-7-11
  ******************************************************************************
 **/

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include "Headers/mainwindow.h"
#include "Forms/ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    //显示登录界面
    login_dialog_ = new LoginDialog(this);//设置MainwWindow为父窗口
    setCentralWidget(login_dialog_);
    //login_dialog_->show();
    //注册界面
    connect(login_dialog_, &LoginDialog::switchRegister, this, &MainWindow::slotSwitchRegister);
    register_dialog_ = new RegisterDialog(this);//设置MainwWindow为父窗口
    //设置为无边框窗口，使其嵌入主窗口
    login_dialog_->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    register_dialog_->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    register_dialog_->hide();
}

MainWindow::~MainWindow() {
    delete ui;
//    if(login_dialog_){
//        delete login_dialog_;
//        login_dialog_ = nullptr;
//    }
//
//    if (register_dialog_){
//        delete register_dialog_;
//        register_dialog_ = nullptr;
//    }
}

void MainWindow::slotSwitchRegister() {
    setCentralWidget(register_dialog_);
    login_dialog_->hide();
    register_dialog_->show();
}
