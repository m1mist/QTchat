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

void RegisterDialog::on_get_auth_button_clicked(){
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

}
