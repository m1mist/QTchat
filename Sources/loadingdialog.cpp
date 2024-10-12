/**
  ******************************************************************************
  * @file           : loadingdialog.cpp
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-5
  ******************************************************************************
 **/

// You may need to build the project (run Qt uic code generator) to get "ui_LoadingDialog.h" resolved

#include "loadingdialog.h"
#include "Forms/ui_LoadingDialog.h"
#include <QMovie>

LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::LoadingDialog) {
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground); // 设置背景透明
    // 获取屏幕尺寸
    setFixedSize(parent->size()); // 设置对话框为全屏尺寸

    QMovie *movie = new QMovie(":/res/res/loading.gif"); // 加载动画的资源文件
    ui->label_loading->setMovie(movie);
    movie->start();
}

LoadingDialog::~LoadingDialog() {
    delete ui;
}
