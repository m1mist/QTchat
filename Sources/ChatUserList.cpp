/**
  ******************************************************************************
  * @file           : ChatUserList.cpp
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-4
  ******************************************************************************
 **/

#include "Headers/ChatUserList.h"

ChatUserList::ChatUserList(QWidget *parent):QListWidget(parent) {
    Q_UNUSED(parent);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 安装事件过滤器
    this->viewport()->installEventFilter(this);
}

bool ChatUserList::eventFilter(QObject *watched, QEvent *event) {
    // 检查事件是否是鼠标悬浮进入或离开
    if (watched == this->viewport()) {
        if (event->type() == QEvent::Enter) {
            // 鼠标悬浮，显示滚动条
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        } else if (event->type() == QEvent::Leave) {
            // 鼠标离开，隐藏滚动条
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        }
    }

    // 检查事件是否是鼠标滚轮事件
    if (watched == this->viewport() && event->type() == QEvent::Wheel) {
        auto *wheel_event = dynamic_cast<QWheelEvent*>(event);
        int degrees = wheel_event->angleDelta().y() / 8;
        int steps = degrees / 15; // 计算滚动步数

        // 设置滚动幅度
        this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - steps);

        // 检查是否滚动到底部
        QScrollBar *scroll_bar = this->verticalScrollBar();
        int max_scroll_value = scroll_bar->maximum();
        int current_scroll_value = scroll_bar->value();
        //int pageSize = 10; // 每页加载的联系人数量

        if (max_scroll_value - current_scroll_value <= 0) {
            // 滚动到底部，加载新的联系人
            qDebug()<<"load more chat user";
            //发送信号通知聊天界面加载更多聊天内容
            emit sig_load_chat_user();
        }

        return true; // 停止事件传递
    }

    return QListWidget::eventFilter(watched, event);
}
