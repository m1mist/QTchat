/**
  ******************************************************************************
  * @file           : ClickedButton.h
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-1
  ******************************************************************************
 **/

#ifndef CLICKEDBUTTON_H
#define CLICKEDBUTTON_H
#include<QPushButton>


class ClickedButton:public QPushButton {
    Q_OBJECT;
public:
    explicit ClickedButton(QWidget *parent = nullptr);
    ~ClickedButton() override;
    void SetState(QString normal, QString hover, QString press);
protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    QString normal_;
    QString hover_;
    QString press_;

};



#endif //CLICKEDBUTTON_H
