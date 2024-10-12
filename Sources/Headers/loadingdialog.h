
#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H

#include <QDialog>
/**
  ******************************************************************************
  * @file           : loadingdialog.h
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-5
  ******************************************************************************
 **/


QT_BEGIN_NAMESPACE
namespace Ui { class LoadingDialog; }
QT_END_NAMESPACE

class LoadingDialog : public QDialog {
Q_OBJECT

public:
    explicit LoadingDialog(QWidget *parent = nullptr);
    ~LoadingDialog() override;

private:
    Ui::LoadingDialog *ui;


};


#endif //LOADINGDIALOG_H
