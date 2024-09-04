/**
  ******************************************************************************
  * @file           : ClickedLabel.cpp
  * @author         : 16649
  * @brief          : None
  * @attention      : None
  * @date           : 24-9-1
  ******************************************************************************
 **/

#include "ClickedLabel.h"

ClickedLabel::ClickedLabel(QWidget *parent): QLabel(parent), cur_state_(ClickLbState::Normal) {

}

void ClickedLabel::mousePressEvent(QMouseEvent *event) {
    // 处理鼠标点击事件

    if(cur_state_ == ClickLbState::Normal){
        qDebug()<<"clicked , change to selected hover: "<< selected_hover_;
        cur_state_ = ClickLbState::Selected;
        setProperty("state",selected_hover_);
        repolish(this);
        update();

    }else{
        qDebug()<<"clicked , change to normal hover: "<< normal_hover_;
        cur_state_ = ClickLbState::Normal;
        setProperty("state",normal_hover_);
        repolish(this);
        update();
    }
    emit clicked();
    QLabel::mousePressEvent(event);
}
void ClickedLabel::enterEvent(QEnterEvent *event) {
    // 处理鼠标悬停进入
    if(cur_state_ == ClickLbState::Normal){
        qDebug()<<"enter , change to normal hover: "<< normal_hover_;
        setProperty("state",normal_hover_);
        repolish(this);
        update();

    }else{
        qDebug()<<"enter , change to selected hover: "<< selected_hover_;
        setProperty("state",selected_hover_);
        repolish(this);
        update();
    }
    QLabel::enterEvent(event);
}

void ClickedLabel::leaveEvent(QEvent *event) {
    // 处理鼠标悬停离开
    if(cur_state_ == ClickLbState::Normal){
        qDebug()<<"leave , change to normal : "<< normal_;
        setProperty("state",normal_);
        repolish(this);
        update();

    }else{
        qDebug()<<"leave , change to normal hover: "<< selected_;
        setProperty("state",selected_);
        repolish(this);
        update();
    }
    QLabel::leaveEvent(event);
}
void ClickedLabel::SetState(QString normal, QString hover, QString press, QString select, QString select_hover, QString select_press) {
    normal_ = normal;
    normal_hover_ = hover;
    normal_press_ = press;

    selected_ = select;
    selected_hover_ = select_hover;
    selected_press_ = select_press;

    setProperty("state",normal);
    repolish(this);
}

ClickLbState ClickedLabel::GetCurState() {
    return  cur_state_;
}


