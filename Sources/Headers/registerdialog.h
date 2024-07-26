
#ifndef LLFCCHAT_REGISTERDIALOG_H
#define LLFCCHAT_REGISTERDIALOG_H
/**
  ******************************************************************************
  * @file           : registerdialog.h
  * @author         : 16649
  * @brief          : None
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
private slots:
    void on_get_auth_button_clicked();
    void slot_reg_mod_finish(ReqId id, QString str, ErrorCodes err);
private:
    Ui::RegisterDialog *ui;
    void showTip(QString,bool);
    void initHttpHandlers();
    QMap<ReqId, std::function<void(const QJsonObject&)>> handlers_;


};


#endif //LLFCCHAT_REGISTERDIALOG_H
