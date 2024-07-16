
#ifndef LLFCCHAT_MAINWINDOW_H
#define LLFCCHAT_MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include "registerdialog.h"
/**
  ******************************************************************************
  * @file           : MainWindow.h
  * @author         : 16649
  * @brief          : None
  * @attention      : None
  * @date           : 24-7-11
  ******************************************************************************
 **/


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;
public slots:
    void slotSwitchRegister();
private:
    Ui::MainWindow *ui;
    LoginDialog *login_dialog_;
    RegisterDialog *register_dialog_;
};


#endif //LLFCCHAT_MAINWINDOW_H
