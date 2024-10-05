
#ifndef MYEDIT_H
#define MYEDIT_H

#include <QLineEdit>
/**
  ******************************************************************************
  * @file           : myedit.h
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-3
  ******************************************************************************
 **/


QT_BEGIN_NAMESPACE
namespace Ui { class MyEdit; }
QT_END_NAMESPACE

class MyEdit : public QLineEdit {
    Q_OBJECT
public:
    explicit MyEdit(QWidget *parent = nullptr);
    int max_len = 0;

protected:
    void focusOutEvent(QFocusEvent *event) override;

private:
    void LimitTextLength(QString text);
    ~MyEdit() override;
    Ui::MyEdit *ui;


signals:
    void sig_focos_out();
};


#endif //MYEDIT_H
