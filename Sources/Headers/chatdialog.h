
#ifndef CHATDIALOG_H
#define CHATDIALOG_H
/**
  ******************************************************************************
  * @file           : chatdialog.h
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-1
  ******************************************************************************
 **/
#include "global.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChatDialog; }
QT_END_NAMESPACE

class ChatDialog : public QWidget {
Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = nullptr);
    ~ChatDialog() override;
    void AddChatUserList();
private:
    void ShowSearch(bool b_search);
    Ui::ChatDialog *ui;
    ChatUiMode mode_;
    ChatUiMode state_;
    bool b_load_;
public slots:
    void slots_load_chat_user();
};


#endif //CHATDIALOG_H
