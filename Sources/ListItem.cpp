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

ListItem::ListItem(QWidget *parent):QWidget(parent) {
}

void ListItem::SetItemType(ListItemType type) {
    type_ = type;
}

ListItemType ListItem::GetItemType() {
    return  type_;
}
