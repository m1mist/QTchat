/**
  ******************************************************************************
  * @file           : Bubble.cpp
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-8
  ******************************************************************************
 **/

#include "Headers/Bubble.h"

#include <QPainter>
constexpr int WIDTH_TRIANGLE  = 8;  //气泡的三角区域宽度
Bubble::Bubble(ChatRole role, QWidget *parent) :QFrame(parent)
    ,m_role(role)
    ,m_margin(3)
{
    m_pHLayout = new QHBoxLayout();
    if(m_role == ChatRole::Self)
        m_pHLayout->setContentsMargins(m_margin, m_margin, WIDTH_TRIANGLE + m_margin, m_margin);
    else
        m_pHLayout->setContentsMargins(WIDTH_TRIANGLE + m_margin, m_margin, m_margin, m_margin);

    this->setLayout(m_pHLayout);
}

void Bubble::setMargin(const int margin) {
    m_margin = margin;
}

void Bubble::setWidget(QWidget *w) const {
    if(m_pHLayout->count() > 0)
        return ;
    else{
        m_pHLayout->addWidget(w);
    }
}

void Bubble::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    if(m_role == ChatRole::Other)
    {
        //画气泡
        QColor bk_color(Qt::white);
        painter.setBrush(QBrush(bk_color));
        QRect bk_rect = QRect(WIDTH_TRIANGLE, 0, this->width()-WIDTH_TRIANGLE, this->height());
        painter.drawRoundedRect(bk_rect,5,5);
        //画小三角
        QPointF points[3] = {
            QPointF(bk_rect.x(), 12),
            QPointF(bk_rect.x(), 10+WIDTH_TRIANGLE +2),
            QPointF(bk_rect.x()-WIDTH_TRIANGLE, 10+WIDTH_TRIANGLE-WIDTH_TRIANGLE/2),
        };
        painter.drawPolygon(points, 3);
    }
    else
    {
        QColor bk_color(158,234,106);
        painter.setBrush(QBrush(bk_color));
        //画气泡
        QRect bk_rect = QRect(0, 0, this->width()-WIDTH_TRIANGLE, this->height());
        painter.drawRoundedRect(bk_rect,5,5);
        //画三角
        QPointF points[3] = {
            QPointF(bk_rect.x()+bk_rect.width(), 12),
            QPointF(bk_rect.x()+bk_rect.width(), 12+WIDTH_TRIANGLE +2),
            QPointF(bk_rect.x()+bk_rect.width()+WIDTH_TRIANGLE, 10+WIDTH_TRIANGLE-WIDTH_TRIANGLE/2),
        };
        painter.drawPolygon(points, 3);

    }

    return QFrame::paintEvent(e);
}
