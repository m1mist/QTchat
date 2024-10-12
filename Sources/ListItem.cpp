/**
  ******************************************************************************
  * @file           : ListItem.cpp
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-4
  ******************************************************************************
 **/

#include "Headers/ListItem.h"

#include <QPainter>
#include <QStyleOption>

ListItem::ListItem(QWidget *parent): QWidget(parent), type_() {
}

void ListItem::SetItemType(ListItemType type) {
    type_ = type;
}

ListItemType ListItem::GetItemType() {
    return  type_;
}

void ListItem::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
