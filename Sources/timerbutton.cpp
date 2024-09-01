/**
  ******************************************************************************
  * @file           : timerbutton.cpp
  * @author         : 16649
  * @brief          : None
  * @attention      : None
  * @date           : 24-8-19
  ******************************************************************************
 **/

#include "timerbutton.h"
#include <QMouseEvent>
#include <QDebug>
timerbutton::timerbutton(QWidget *parent) : QPushButton(parent), counter_(10) {
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, [this]{
        counter_--;
        if (counter_ <= 0){
            timer_->stop();
            counter_ = 10;
            this->setText("获取");
            this->setEnabled(true);
            return ;
        }
        this->setText(QString::number(counter_));
    });
}

timerbutton::~timerbutton() {
    timer_->stop();
    delete timer_;
}

void timerbutton::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        // 在这里处理鼠标左键释放事件
        qDebug() << "MyButton was released!";
        this->setEnabled(false);
        this->setText(QString::number(counter_));
        timer_->start(1000);
        emit clicked();
    }
    // 调用基类的mouseReleaseEvent以确保正常的事件处理（如点击效果）
    QPushButton::mouseReleaseEvent(e);
}
