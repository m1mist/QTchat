/**
  ******************************************************************************
  * @file           : ClickedLabel.h
  * @author         : 16649
  * @brief          : None
  * @attention      : None
  * @date           : 24-9-1
  ******************************************************************************
 **/

#ifndef LLFCCHAT_CLICKEDLABEL_H
#define LLFCCHAT_CLICKEDLABEL_H

#include <QLabel>

#include "global.h" //ClickLbState

class ClickedLabel: public QLabel{
    Q_OBJECT
public:
    explicit ClickedLabel(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void SetState(QString normal="", QString hover="", QString press="",
                  QString select="", QString select_hover="", QString select_press="");

    //ClickLbState定义在global.h中，包含两种状态一个是普通状态，一个是选中状态。而Label中的六种状态就是基于这两种状态嵌套实现的。
    ClickLbState GetCurState();
private:
    QString normal_;
    QString normal_hover_;
    QString normal_press_;

    QString selected_;
    QString selected_hover_;
    QString selected_press_;

    ClickLbState cur_state_;
signals:
    void clicked();
};


#endif //LLFCCHAT_CLICKEDLABEL_H
