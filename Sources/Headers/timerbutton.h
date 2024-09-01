/**
  ******************************************************************************
  * @file           : timerbutton.h
  * @author         : 16649
  * @brief          : 点击获取验证码后需要让按钮显示倒计时，然后倒计时结束后再次可点击。
  * @attention      : None
  * @date           : 24-8-19
  ******************************************************************************
 **/

#ifndef LLFCCHAT_TIMERBUTTON_H
#define LLFCCHAT_TIMERBUTTON_H
#include <QPushButton>
#include <QTimer>

class timerbutton: public QPushButton{
public:
    timerbutton(QWidget *parent = nullptr);
    ~timerbutton();

    virtual void mouseReleaseEvent(QMouseEvent *e) override;
private:
    QTimer *timer_;
    int counter_;
};


#endif //LLFCCHAT_TIMERBUTTON_H
