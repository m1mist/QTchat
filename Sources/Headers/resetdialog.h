
#ifndef LLFCCHAT_RESETDIALOG_H
#define LLFCCHAT_RESETDIALOG_H

#include <QDialog>
#include "global.h"
/**
  ******************************************************************************
  * @file           : resetdialog.h
  * @author         : 16649
  * @brief          : None
  * @attention      : None
  * @date           : 24-9-9
  ******************************************************************************
 **/


QT_BEGIN_NAMESPACE
namespace Ui { class ResetDialog; }
QT_END_NAMESPACE

class ResetDialog : public QDialog {
Q_OBJECT

public:
    explicit ResetDialog(QWidget *parent = nullptr);

    ~ResetDialog() override;

private slots:
    void on_cancel_button_clicked();
    void on_get_verify_code_button_clicked();
    void on_confirm_button_clicked();

    void slot_reset_mod_finish(ReqId id, QString res, ErrorCodes err);
private:
    bool checkUserValid();
    bool checkPassValid();
    bool checkEmailValid();
    bool checkVerifyValid();

    void showTip(QString str,bool b_ok);
    void AddTipErr(TipErr te,QString tips);
    void DelTipErr(TipErr te);

    void initHandlers();
    Ui::ResetDialog *ui;
    QMap<TipErr, QString> _tip_errs;
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;

signals:
    void switchLogin();
};


#endif //LLFCCHAT_RESETDIALOG_H
