
#ifndef LLFCCHAT_LOGINDIALOG_H
#define LLFCCHAT_LOGINDIALOG_H

#include <QDialog>
/**
  ******************************************************************************
  * @file           : logindialog.h
  * @author         : 16649
  * @brief          : None
  * @attention      : None
  * @date           : 24-7-11
  ******************************************************************************
 **/


QT_BEGIN_NAMESPACE
namespace Ui { class LoginDialog; }
QT_END_NAMESPACE

class LoginDialog : public QDialog {
Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);

    ~LoginDialog() override;

private:
    Ui::LoginDialog *ui;

signals:
    void switchRegister();
    void switchReset();
private slots:
    void slot_forget_pwd();
};


#endif //LLFCCHAT_LOGINDIALOG_H
