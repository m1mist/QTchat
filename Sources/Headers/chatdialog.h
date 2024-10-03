
#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QWidget>
/**
  ******************************************************************************
  * @file           : chatdialog.h
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-1
  ******************************************************************************
 **/


QT_BEGIN_NAMESPACE
namespace Ui { class ChatDialog; }
QT_END_NAMESPACE

class ChatDialog : public QWidget {
Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = nullptr);
    ~ChatDialog() override;

private:
    Ui::ChatDialog *ui;
};


#endif //CHATDIALOG_H
