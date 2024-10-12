/**
  ******************************************************************************
  * @file           : ChatItem.cpp
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-8
  ******************************************************************************
 **/

#include "Headers/ChatItem.h"

ChatItem::ChatItem(ChatRole role, QWidget *parent)
    : QWidget(parent)
    , role_(role)
{
    //创建昵称标签
    p_name_label_ = new QLabel();
    p_name_label_->setObjectName("chat_user_name");

    //设置昵称字体
    QFont font("Microsoft YaHei");
    font.setPointSize(9);
    p_name_label_->setFont(font);
    p_name_label_->setFixedHeight(20);

    //头像标签
    p_icon_label_ = new QLabel();
    p_icon_label_->setScaledContents(true);
    p_icon_label_->setFixedSize(42, 42);

    p_bubble_widget_ = new QWidget();
    auto *pGLayout = new QGridLayout();
    pGLayout->setVerticalSpacing(3);
    pGLayout->setHorizontalSpacing(3);
    pGLayout->setContentsMargins(3,3,3,3);

    auto *pSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    //判断发气泡的角色
    if(role_ == ChatRole::Self)
    {
        //放置各部件
        p_name_label_->setContentsMargins(0,0,8,0);
        p_name_label_->setAlignment(Qt::AlignRight);
        pGLayout->addWidget(p_name_label_, 0,1, 1,1);
        pGLayout->addWidget(p_icon_label_, 0, 2, 2,1, Qt::AlignTop);
        pGLayout->addItem(pSpacer, 1, 0, 1, 1);
        pGLayout->addWidget(p_bubble_widget_, 1,1, 1,1);
        pGLayout->setColumnStretch(0, 2);
        pGLayout->setColumnStretch(1, 3);
    }else{
        //放置各部件
        p_name_label_->setContentsMargins(8,0,0,0);
        p_name_label_->setAlignment(Qt::AlignLeft);
        pGLayout->addWidget(p_icon_label_, 0, 0, 2,1, Qt::AlignTop);
        pGLayout->addWidget(p_name_label_, 0,1, 1,1);
        pGLayout->addWidget(p_bubble_widget_, 1,1, 1,1);
        pGLayout->addItem(pSpacer, 2, 2, 1, 1);
        pGLayout->setColumnStretch(1, 3);
        pGLayout->setColumnStretch(2, 2);
    }
    this->setLayout(pGLayout);
}

void ChatItem::setUserName(const QString &name) const {
    p_name_label_->setText(name);
}

void ChatItem::setUserIcon(const QPixmap &icon) const {
    p_icon_label_->setPixmap(icon);
}

void ChatItem::setWidget(QWidget *w) {
    auto pGLayout = (qobject_cast<QGridLayout *>)(this->layout());
    pGLayout->replaceWidget(p_bubble_widget_, w);
    delete p_bubble_widget_;
    p_bubble_widget_ = w;
}
