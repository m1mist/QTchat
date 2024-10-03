/**
  ******************************************************************************
  * @file           : ClickedButton.cpp
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-1
  ******************************************************************************
 **/

#include "ClickedButton.h"

#include "global.h"

ClickedButton::ClickedButton(QWidget *parent):QPushButton(parent) {
    setCursor(Qt::PointingHandCursor);
}

ClickedButton::~ClickedButton() {
}

void ClickedButton::SetState(QString normal, QString hover, QString press) {
    normal_ = normal;
    hover_ = hover;
    press_ = press;

    setProperty("state",normal);
    repolish(this);
    update();
}

void ClickedButton::enterEvent(QEnterEvent *event) {
    setProperty("state",hover_);
    repolish(this);
    update();
    QPushButton::enterEvent(event);
}

void ClickedButton::leaveEvent(QEvent *event) {
    setProperty("state",normal_);
    repolish(this);
    update();
    QPushButton::leaveEvent(event);
}

void ClickedButton::mousePressEvent(QMouseEvent *event) {
    setProperty("state",press_);
    repolish(this);
    update();
    QPushButton::mousePressEvent(event);
}

void ClickedButton::mouseReleaseEvent(QMouseEvent *event) {
    setProperty("state",normal_);
    repolish(this);
    update();
    QPushButton::mouseReleaseEvent(event);
}
