/**
  ******************************************************************************
  * @file           : registerdialog.cpp
  * @author         : 16649
  * @brief          : None
  * @attention      : None
  * @date           : 24-7-12
  ******************************************************************************
 **/

// You may need to build the project (run Qt uic code generator) to get "ui_RegisterDialog.h" resolved

#include "Headers/registerdialog.h"
#include "Forms/ui_RegisterDialog.h"
#include "global.h"
#include "HttpManager.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::RegisterDialog) {
    ui->setupUi(this);
    ui->password_edit->setEchoMode(QLineEdit::Password);
    ui->confirm_edit->setEchoMode(QLineEdit::Password);
    ui->error_label->setProperty("state","normal");
    repolish(ui->error_label);
    connect(HttpManager::getInstance().get(), &HttpManager::sig_reg_mod_finish,
            this, &RegisterDialog::slot_reg_mod_finish);
    initHttpHandlers();
}

RegisterDialog::~RegisterDialog() {
    delete ui;
}

void RegisterDialog::on_get_verify_code_button_clicked(){
    auto email = ui->email_edit->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch();
    if(match){
        //发送http验证码
        QJsonObject json_obj;
        json_obj["email"] = email;
        HttpManager::getInstance()->PostHttpReq(QUrl(gate_url_prefix+"/verify_code"),
                                            json_obj, ReqId::ID_GET_AUTH,Modules::REGISTER);
    }else{
        showTip(tr("错误的邮箱地址"), false);
    }
}

void RegisterDialog::showTip(QString str,bool b_ok) {
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

void RegisterDialog::slot_reg_mod_finish(ReqId id, QString str, ErrorCodes err) {
    if(err != ErrorCodes::SUCCESS){
        showTip(tr("网络请求错误"), false);
        return;
    }

    //解析json
    auto jsonDocument = QJsonDocument::fromJson(str.toUtf8());

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

void RegisterDialog::initHttpHandlers() {
    handlers_.insert(ReqId::ID_GET_AUTH,[this](const QJsonObject& jsonObject){
        int error = jsonObject["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"), false);
            qDebug() << error;
            return;
        }

        auto email = jsonObject["email"].toString();
        showTip(tr("验证码已发送"), true);
        qDebug() << "email is " << email;
    });
    //注册注册用户回包逻辑
    handlers_.insert(ReqId::ID_REGISTER_USER, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            qDebug()<<error;
            showTip(tr("参数错误"),false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("用户注册成功"), true);
        qDebug()<< "email is " << email ;
    });
}

void RegisterDialog::on_confirm_button_clicked() {
    //发送http请求注册用户
    QJsonObject json_obj;
    json_obj["user"] = ui->user_edit->text();
    json_obj["email"] = ui->email_edit->text();
    json_obj["passwd"] = ui->password_edit->text();
    json_obj["confirm"] = ui->confirm_edit->text();
    json_obj["verifycode"] = ui->verify_edit->text();
    HttpManager::getInstance()->PostHttpReq(QUrl(gate_url_prefix+"/user_register"),
                                        json_obj, ReqId::ID_REGISTER_USER,Modules::REGISTER);
}
