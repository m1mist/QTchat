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
    login_dialog_->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(login_dialog_);
    //login_dialog_->show();
    //注册界面
    connect(login_dialog_, &LoginDialog::switchRegister, this, &MainWindow::slotSwitchRegister);

    //连接登录界面忘记密码信号
    connect(login_dialog_, &LoginDialog::switchReset, this, &MainWindow::slotSwitchReset);
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
    register_dialog_ = new RegisterDialog(this);//设置MainwWindow为父窗口
    //设置为无边框窗口，使其嵌入主窗口
    register_dialog_->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    connect(register_dialog_, &RegisterDialog::sigSwitchLogin, this, &MainWindow::slotSwitchLogin);
    setCentralWidget(register_dialog_);
    login_dialog_->hide();
    register_dialog_->show();
}

void MainWindow::slotSwitchLogin() {
    //创建一个CentralWidget, 并将其设置为MainWindow的中心部件
    login_dialog_ = new LoginDialog(this);
    login_dialog_->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(login_dialog_);

    register_dialog_->hide();
    login_dialog_->show();
    //连接登录界面注册信号
    connect(login_dialog_, &LoginDialog::switchRegister, this, &MainWindow::slotSwitchRegister);
    //连接登录界面忘记密码信号
    connect(login_dialog_, &LoginDialog::switchReset, this, &MainWindow::slotSwitchReset);
}

void MainWindow::slotSwitchReset() {
//创建一个CentralWidget, 并将其设置为MainWindow的中心部件
    reset_dialog_ = new ResetDialog(this);
    reset_dialog_->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(reset_dialog_);

    login_dialog_->hide();
    reset_dialog_->show();
    //注册返回登录信号和槽函数
    connect(reset_dialog_, &ResetDialog::switchLogin, this, &MainWindow::slotSwitchLogin2);

}

void MainWindow::slotSwitchLogin2() {
//创建一个CentralWidget, 并将其设置为MainWindow的中心部件
    login_dialog_ = new LoginDialog(this);
    login_dialog_->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(login_dialog_);

    reset_dialog_->hide();
    login_dialog_->show();
    //连接登录界面忘记密码信号
    connect(login_dialog_, &LoginDialog::switchReset, this, &MainWindow::slotSwitchReset);
    //连接登录界面注册信号
    connect(login_dialog_, &LoginDialog::switchRegister, this, &MainWindow::slotSwitchRegister);
}
