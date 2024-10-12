/**
  ******************************************************************************
  * @file           : ChatView.h
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-7
  ******************************************************************************
 **/

#ifndef CHATVIEW_H
#define CHATVIEW_H
#include <QScrollArea>
#include <QTimer>
#include <QVBoxLayout>

class ChatView:public QWidget{
    Q_OBJECT
public:
    explicit ChatView(QWidget *parent = Q_NULLPTR);
    void appendChatItem(QWidget *item);                 //尾插
    void prependChatItem(QWidget *item);                //头插
    void insertChatItem(QWidget *before, QWidget *item);//中间插

protected:
    bool eventFilter(QObject *o, QEvent *e) override;
    void paintEvent(QPaintEvent *event) override;
private slots:
    void onScrollBarMoved(int min, int max);

private:
    void initStyleSheet();
    //QWidget *m_pCenterWidget;
    QVBoxLayout *p_layout_{};
    QScrollArea *p_scroll_area_;
    bool b_appended_;

};



#endif //CHATVIEW_H
