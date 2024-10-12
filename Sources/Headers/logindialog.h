
#ifndef LLFCCHAT_LOGINDIALOG_H
#define LLFCCHAT_LOGINDIALOG_H

#include "QDialog"
#include "global.h"
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
    int uid_;
    QString token_;
    bool enableBtn(bool );
    void showTip(const QString&,bool);
    void initHttpHandlers();
    QMap<ReqId, std::function<void(const QJsonObject&)>> handlers_;

    //错误提示
    QMap<TipErr, QString> tip_errs_;
    void AddTipErr(TipErr, const QString&);
    void DelTipErr(TipErr);

    //检测
    bool checkUserValid();
    bool checkPassValid();

signals:
    void switchRegister();
    void switchReset();
    void sig_connect_tcp(ServerInfo);
private slots:
    void slot_forget_pwd();
    void on_login_button_clicked();
    void slot_login_mod_finish(ReqId id, QString res, ErrorCodes err);
    void slot_tcp_con_finish(bool b_success);
    void slot_login_failed(int err);
};


#endif //LLFCCHAT_LOGINDIALOG_H
