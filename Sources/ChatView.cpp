/**
  ******************************************************************************
  * @file           : ChatView.cpp
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-7
  ******************************************************************************
 **/

#include "ChatView.h"

#include <QEvent>
#include <QPainter>
#include <QScrollBar>
#include <QStyleOption>

ChatView::ChatView(QWidget *parent):QWidget(parent),b_appended_(false) {
    //创建垂直布局
    auto main_layout = new QVBoxLayout();
    this->setLayout(main_layout);
    //设置边距
    main_layout->setContentsMargins(0,0,0,0);
    //创建滚动区域
    p_scroll_area_ = new QScrollArea();
    p_scroll_area_->setObjectName("chat_area");
    main_layout->addWidget(p_scroll_area_);

    auto widget = new QWidget();
    widget->setObjectName("chat_background");
    widget->setAutoFillBackground(true);

    auto V_layout_1 = new QVBoxLayout();
    V_layout_1->addWidget(new QWidget,100000);
    widget->setLayout(V_layout_1);
    p_scroll_area_->setWidget(widget);

    p_scroll_area_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScrollBar *scroll_bar = p_scroll_area_->verticalScrollBar();
    connect(scroll_bar, &QScrollBar::rangeChanged,this, &ChatView::onScrollBarMoved);
    //把垂直ScrollBar放到上边 而不是原来的并排
    auto V_layout_2 = new QHBoxLayout();
    V_layout_2->addWidget(scroll_bar, 0, Qt::AlignRight);
    V_layout_2->setContentsMargins(0,0,0,0);
    p_scroll_area_->setLayout(V_layout_2);
    scroll_bar->setHidden(true);

    p_scroll_area_->setWidgetResizable(true);
    p_scroll_area_->installEventFilter(this);
//    initStyleSheet();
}

void ChatView::appendChatItem(QWidget *item) {
    auto layout = qobject_cast<QVBoxLayout *>(p_scroll_area_->widget()->layout());
    layout->insertWidget(layout->count()-1, item);
    b_appended_ = true;
}

bool ChatView::eventFilter(QObject *o, QEvent *e) {
    /*if(e->type() == QEvent::Resize && o == )
{

}
else */if(e->type() == QEvent::Enter && o == p_scroll_area_)
{
    p_scroll_area_->verticalScrollBar()->setHidden(p_scroll_area_->verticalScrollBar()->maximum() == 0);
}
    else if(e->type() == QEvent::Leave && o == p_scroll_area_)
    {
        p_scroll_area_->verticalScrollBar()->setHidden(true);
    }
    return QWidget::eventFilter(o, e);
}

void ChatView::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ChatView::onScrollBarMoved(int min, int max) {
    if(b_appended_) //添加item可能调用多次
    {
        QScrollBar *scroll_bar = p_scroll_area_->verticalScrollBar();
        scroll_bar->setSliderPosition(scroll_bar->maximum());
        //500毫秒内可能调用多次
        QTimer::singleShot(500, [this]()
        {
            b_appended_ = false;
        });
    }
}
