
#ifndef WIDGETCHATUSER_H
#define WIDGETCHATUSER_H
#include "ListItem.h"
/**
  ******************************************************************************
  * @file           : widgetchatuser.h
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-4
  ******************************************************************************
 **/


QT_BEGIN_NAMESPACE
namespace Ui { class WidgetChatUser; }
QT_END_NAMESPACE

class WidgetChatUser : public ListItem {
    Q_OBJECT
public:
    explicit WidgetChatUser(QWidget *parent = nullptr);
    ~WidgetChatUser();

    QSize sizeHint() const override {
        return {250, 70}; // 返回自定义的尺寸
    }

    void SetInfo(QString name, QString head, QString msg);

private:
    Ui::WidgetChatUser *ui;
    QString _name;
    QString _head;
    QString _msg;
};


#endif //WIDGETCHATUSER_H
