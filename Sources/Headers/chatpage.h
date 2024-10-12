
#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWidget>
/**
  ******************************************************************************
  * @file           : chatpage.h
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-5
  ******************************************************************************
 **/


QT_BEGIN_NAMESPACE
namespace Ui { class ChatPage; }
QT_END_NAMESPACE

class ChatPage : public QWidget {
Q_OBJECT

public:
    explicit ChatPage(QWidget *parent = nullptr);
    ~ChatPage() override;
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    Ui::ChatPage *ui;
    
//slots:

//signals:

};


#endif //CHATPAGE_H
