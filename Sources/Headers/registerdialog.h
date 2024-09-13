
#ifndef LLFCCHAT_REGISTERDIALOG_H
#define LLFCCHAT_REGISTERDIALOG_H
/**
  ******************************************************************************
  * @file           : registerdialog.h
  * @author         : 16649
  * @brief          : 注册页
  * @attention      : None
  * @date           : 24-7-12
  ******************************************************************************
 **/
#include <QDialog>
#include "global.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RegisterDialog; }
QT_END_NAMESPACE

class RegisterDialog : public QDialog {
Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);

    ~RegisterDialog() override;


private:
    Ui::RegisterDialog *ui;
    void showTip(QString,bool);
    void initHttpHandlers();
    QMap<ReqId, std::function<void(const QJsonObject&)>> handlers_;

    //提示
    QMap<TipErr, QString> tip_errs_;
    void AddTipErr(TipErr, const QString&);
    void DelTipErr(TipErr);

    //检查可用性
    bool checkUserValid();
    bool checkEmailValid();
    bool checkPassValid();
    bool checkConfirmValid();
    bool checkVerifyValid();

    //注册完成后，自动返回
    QTimer *timer_;
    int countdown_;
    void ChangeToTipPage();

private slots:
    void on_get_verify_code_button_clicked();
    void slot_reg_mod_finish(ReqId id, QString str, ErrorCodes err);
    void on_confirm_button_clicked();
    void on_return_button_clicked();
    void on_cancel_button_clicked();
signals:
    void switchLogin();
};


#endif //LLFCCHAT_REGISTERDIALOG_H
