/**
  ******************************************************************************
  * @file           : ListItem.h
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-4
  ******************************************************************************
 **/

#ifndef LISTITEM_H
#define LISTITEM_H
#include "global.h"


class ListItem:public QWidget {
    Q_OBJECT;
public:
    explicit ListItem(QWidget* parent = nullptr);
    void SetItemType(ListItemType type);

    ListItemType GetItemType();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    ListItemType type_;

public slots:

signals:

};



#endif //LISTITEM_H
