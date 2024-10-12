/**
  ******************************************************************************
  * @file           : chatdialog.cpp
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-10-1
  ******************************************************************************
 **/

// You may need to build the project (run Qt uic code generator) to get "ui_ChatDialog.h" resolved

#include "Headers/chatdialog.h"

#include <loadingdialog.h>

#include "Forms/ui_ChatDialog.h"
#include <QRandomGenerator>

#include "widgetchatuser.h"

ChatDialog::ChatDialog(QWidget *parent) :
    QWidget(parent), ui(new Ui::ChatDialog),mode_(CHAT),state_(CHAT),b_load_(false) {
    ui->setupUi(this);
    ui->button_plus->SetState("normal","hover","press");
    ui->edit_search->max_len = 15;
    //搜索栏
    auto* search_action = new QAction(ui->edit_search);
    search_action->setIcon(QIcon(":/res/res/search.png"));
    ui->edit_search->addAction(search_action,QLineEdit::LeadingPosition);
    ui->edit_search->setPlaceholderText(QStringLiteral("搜索"));
    //清除搜索栏内容
    auto* clear_action = new QAction(ui->edit_search);
    clear_action->setIcon(QIcon(":/res/res/close_transparent.png"));
    ui->edit_search->addAction(clear_action, QLineEdit::TrailingPosition);

    // 当需要显示清除图标时，更改为实际的清除图标
    connect(ui->edit_search, &QLineEdit::textChanged, [clear_action](const QString &text) {
        if (!text.isEmpty()) {
            clear_action->setIcon(QIcon(":/res/res/close_search.png"));
        } else {
            clear_action->setIcon(QIcon(":/res/res/close_transparent.png")); // 文本为空时，切换回透明图标
        }

    });

    // 连接清除动作的触发信号到槽函数，用于清除文本
    connect(clear_action, &QAction::triggered, [this, clear_action]() {
        ui->edit_search->clear();
        clear_action->setIcon(QIcon(":/res/res/close_transparent.png")); // 清除文本后，切换回透明图标
        ui->edit_search->clearFocus();
        //清除按钮被按下则不显示搜索框
        ShowSearch(false);
    });
    ShowSearch(false);
    connect(ui->list_chat_user,&ChatUserList::sig_load_chat_user,this,&ChatDialog::slots_load_chat_user);
    AddChatUserList();
}

ChatDialog::~ChatDialog() {
    delete ui;
}
//test
std::vector<QString>  strs ={"hello world !",
                             "nice to meet u",
                             "New year，new life",
                            "You have to love yourself",
                            "My love is written in the wind ever since the whole world is you"};

std::vector<QString> heads = {
    ":/res/res/head_1.jpg",
    ":/res/res/head_2.jpg",
    ":/res/res/head_3.jpg",
    ":/res/res/head_4.jpg",
    ":/res/res/head_5.jpg",
    ":/res/res/head_6.jpg"
};

std::vector<QString> names = {
    "llfc",
    "zack",
    "golang",
    "cpp",
    "java",
    "nodejs",
    "python",
    "rust"
};

void ChatDialog::AddChatUserList() {
    // 创建QListWidgetItem，并设置自定义的widget
    for(int i = 0; i < 13; i++){
        int random_value = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
        int str_i = random_value%strs.size();
        int head_i = random_value%heads.size();
        int name_i = random_value%names.size();

        auto *chat_user_wid = new WidgetChatUser();
        chat_user_wid->SetInfo(names[name_i], heads[head_i], strs[str_i]);
        auto *item = new QListWidgetItem;
        //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
        item->setSizeHint(chat_user_wid->sizeHint());
        ui->list_chat_user->addItem(item);
        ui->list_chat_user->setItemWidget(item, chat_user_wid);
    }
}

void ChatDialog::ShowSearch(bool b_search) {
    if(b_search){
        ui->list_chat_user->hide();
        ui->list_contacts->hide();
        ui->list_search->show();
        mode_ = SEARCH;
    }else if(state_ == CHAT){
        ui->list_chat_user->show();
        ui->list_contacts->hide();
        ui->list_search->hide();
        mode_ = CHAT;
    }else if(state_ == CONTACTS){
        ui->list_chat_user->hide();
        ui->list_search->hide();
        ui->list_contacts->show();
        mode_ = CONTACTS;
    }
}

void ChatDialog::slots_load_chat_user() {
    if (b_load_) {
        return;
    }
    b_load_ = true;

    auto loading_dialog = new LoadingDialog(this);
    loading_dialog->setModal(true);
    loading_dialog->show();

    qDebug() << "add new data to list...";
    AddChatUserList();

    loading_dialog->deleteLater();
    b_load_ = false;

}
