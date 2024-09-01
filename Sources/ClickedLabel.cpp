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
    QLabel::mousePressEvent(event);
}
