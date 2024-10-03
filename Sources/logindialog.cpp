/**
  ******************************************************************************
  * @file           : logindialog.cpp
  * @author         : 16649
  * @brief          : None
  * @attention      : None
  * @date           : 24-7-11
  ******************************************************************************
 **/

// You may need to build the project (run Qt uic code generator) to get "ui_LoginDialog.h" resolved

#include "logindialog.h"
#include "Forms/ui_LoginDialog.h"
#include "HttpManager.h"
#include "TcpManager.h"


LoginDialog::LoginDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::LoginDialog) {
    ui->setupUi(this);
    connect(ui->register_button, &QPushButton::clicked,
            this, &LoginDialog::switchRegister);
    ui->forget_label->SetState("normal","hover","",
                               "selected","selected_hover","");
    connect(ui->forget_label, &ClickedLabel::clicked,
            this, &LoginDialog::slot_forget_pwd);
    initHttpHandlers();
    //连接登录回包信号
    connect(HttpManager::GetInstance().get(), &HttpManager::sig_login_mod_finish, this,
            &LoginDialog::slot_login_mod_finish);
    //连接tcp连接请求的信号和槽函数
    connect(this, &LoginDialog::sig_connect_tcp, TcpManager::GetInstance().get(), &TcpManager::slot_tcp_connect);
    //连接tcp管理者发出的连接成功信号
    connect(TcpManager::GetInstance().get(), &TcpManager::sig_con_success, this, &LoginDialog::slot_tcp_con_finish);
    //连接tcp失败
    connect(TcpManager::GetInstance().get(),&TcpManager::sig_login_failed, this, &LoginDialog::slot_login_failed);
}

LoginDialog::~LoginDialog() {
    delete ui;
}

void LoginDialog::initHttpHandlers() {
    //注册获取登录回包逻辑
    handlers_.insert(ReqId::ID_LOGIN_USER, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"),false);
            enableBtn(true);
            return;
        }
        auto user = jsonObj["user"].toString();

        ServerInfo si;
        si.uid = jsonObj["uid"].toInt();
        si.host = jsonObj["host"].toString();
        si.port = jsonObj["port"].toString();
        si.token = jsonObj["token"].toString();
        uid_ = si.uid;
        token_ = si.token;
        showTip(tr("登录成功"), true);
        qDebug()<< "user is " << user << " uid is " << si.uid <<" host is "
                << si.host << " Port is " << si.port << " Token is " << si.token;
        emit sig_connect_tcp(si);
    });
}

void LoginDialog::slot_forget_pwd() {
    qDebug()<<"slot forget pwd";
    emit switchReset();
}

void LoginDialog::on_login_button_clicked() {
    qDebug()<<"login btn clicked";
    if(!checkUserValid()){
        return;
    }

    if(!checkPassValid()){
        return ;
    }

    auto user = ui->user_edit->text();
    auto pwd = ui->password_edit->text();
    //发送http请求登录
    QJsonObject json_obj;
    json_obj["name"] = user;
    json_obj["passwd"] = xor_string(pwd);
    HttpManager::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/user_login"),
                                        json_obj, ReqId::ID_LOGIN_USER,Modules::LOGIN);
}

bool LoginDialog::checkUserValid() {
    auto user = ui->user_edit->text();
    if(user.isEmpty()){
        qDebug() << "User empty " ;
        return false;
    }
    return true;
}

bool LoginDialog::checkPassValid() {
    auto pass = ui->password_edit->text();

    if(pass.length() < 6 || pass.length()>15){
        //提示长度不准确
        AddTipErr(TipErr::TIP_PWD_ERR, tr("密码长度应为6~15"));
        return false;
    }
    return true;
}

void LoginDialog::AddTipErr(TipErr tipErr, const QString &str) {
    tip_errs_[tipErr] = str;
    showTip(str, false);
}

void LoginDialog::DelTipErr(TipErr tipErr) {
    tip_errs_.remove(tipErr);
    if (tip_errs_.empty()){
        ui->error_label->clear();
        return;
    }
}

void LoginDialog::showTip(const QString& str, bool b_ok) {
    if(b_ok) {
        ui->error_label->setText(str);
        ui->error_label->setProperty("state","normal");
        repolish(ui->error_label);
    }
    else {
        ui->error_label->setText(str);
        ui->error_label->setProperty("state","err");
        repolish(ui->error_label);
    }
}

void LoginDialog::slot_login_mod_finish(ReqId id, QString res, ErrorCodes err) {
    if(err != ErrorCodes::SUCCESS){
        showTip(tr("网络请求错误"), false);
        return;
    }

    //解析json
    auto jsonDocument = QJsonDocument::fromJson(res.toUtf8());

    if(jsonDocument.isNull()){
        showTip(tr("json解析失败"), false);
        return;
    }
    if(!jsonDocument.isObject()){
        showTip(tr("json解析失败"), false);
        return;
    }

    handlers_[id](jsonDocument.object());
}

void LoginDialog::slot_tcp_con_finish(bool b_success) {
    if(b_success){
        showTip(tr("聊天服务连接成功，正在登录..."),true);
        QJsonObject jsonObj;
        jsonObj["uid"] = uid_;
        jsonObj["token"] = token_;

        QJsonDocument doc(jsonObj);
        QString jsonString = doc.toJson(QJsonDocument::Indented);

        //发送tcp请求给chat server
        emit TcpManager::GetInstance()->sig_send_data(ReqId::ID_CHAT_LOGIN, jsonString);

    }else{
        showTip(tr("网络异常"),false);
        enableBtn(true);
    }

}

void LoginDialog::slot_login_failed(int err) {
    QString result = QString("登录失败, err is %1").arg(err);
    showTip(result,false);
    enableBtn(true);
}

bool LoginDialog::enableBtn(bool) {
    ui->login_button->setEnabled(true);
    ui->register_button->setEnabled(true);
    return true;
}




