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
    //设定输入框输入后清空字符串
    ui->error_label->clear();

    connect(ui->user_edit,&QLineEdit::editingFinished,this,[this](){
        checkUserValid();
    });

    connect(ui->email_edit, &QLineEdit::editingFinished, this, [this](){
        checkEmailValid();
    });

    connect(ui->password_edit, &QLineEdit::editingFinished, this, [this](){
        checkPassValid();
    });

    connect(ui->confirm_edit, &QLineEdit::editingFinished, this, [this](){
        checkConfirmValid();
    });

    connect(ui->verify_edit, &QLineEdit::editingFinished, this, [this](){
        checkVerifyValid();
    });
    ui->visibility_pass->setCursor(Qt::PointingHandCursor);
    ui->visibility_confirm->setCursor(Qt::PointingHandCursor);
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
        switch (error) {
            
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
        qDebug() << "user uid is " << jsonObj["uid"].toString();
        qDebug() << "email is " << email ;
    });
}

void RegisterDialog::on_confirm_button_clicked() {
    //发送http请求注册用户
    QJsonObject json_obj;
    json_obj["user"] = ui->user_edit->text();
    json_obj["email"] = ui->email_edit->text();
    json_obj["passwd"] = xor_string(ui->password_edit->text());
    json_obj["confirm"] = xor_string(ui->confirm_edit->text());
    json_obj["verifycode"] = ui->verify_edit->text();
    HttpManager::getInstance()->PostHttpReq(QUrl(gate_url_prefix+"/user_register"),
                                        json_obj, ReqId::ID_REGISTER_USER,Modules::REGISTER);
}

bool RegisterDialog::checkUserValid() {
    if(ui->user_edit->text() == ""){
        AddTipErr(TipErr::TIP_USER_ERR, tr("用户名不能为空"));
        return false;
    }

    DelTipErr(TipErr::TIP_USER_ERR);
    return true;
}

bool RegisterDialog::checkEmailValid() {
    //验证邮箱的地址正则表达式
    auto email = ui->email_edit->text();
    // 邮箱地址的正则表达式
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
    if(!match){
        //提示邮箱不正确
        AddTipErr(TipErr::TIP_EMAIL_ERR, tr("邮箱地址不正确"));
        return false;
    }

    DelTipErr(TipErr::TIP_EMAIL_ERR);
    return true;
}

bool RegisterDialog::checkPassValid() {
    auto pass = ui->password_edit->text();

    if(pass.length() < 6 || pass.length()>15){
        //提示长度不准确
        AddTipErr(TipErr::TIP_PWD_ERR, tr("密码长度应为6~15"));
        return false;
    }

    // 创建一个正则表达式对象，按照上述密码要求
    // 这个正则表达式解释：
    // ^[a-zA-Z0-9!@#$%^&*]{6,15}$ 密码长度至少6，可以是字母、数字和特定的特殊字符
    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    bool match = regExp.match(pass).hasMatch();
    if(!match){
        //提示字符非法
        AddTipErr(TipErr::TIP_PWD_ERR, tr("不能包含非法字符"));
        return false;;
    }
    DelTipErr(TipErr::TIP_PWD_ERR);
    return true;
}

bool RegisterDialog::checkConfirmValid() {
    auto confirm = ui->confirm_edit->text();
    if (confirm != ui->password_edit->text()){
        AddTipErr(TipErr::TIP_CONFIRM_ERR, tr("两次输入的密码不同"));
        return false;
    }
    DelTipErr(TipErr::TIP_CONFIRM_ERR);
    return true;
}

bool RegisterDialog::checkVerifyValid() {
    auto pass = ui->verify_edit->text();
    if(pass.isEmpty()){
        AddTipErr(TipErr::TIP_VARIFY_ERR, tr("验证码不能为空"));
        return false;
    }

    DelTipErr(TipErr::TIP_VARIFY_ERR);
    return true;
}

void RegisterDialog::AddTipErr(TipErr tipErr, const QString& tips) {
    tip_errs_[tipErr] = tips;
    showTip(tips, false);
}

void RegisterDialog::DelTipErr(TipErr tipErr) {
    tip_errs_.remove(tipErr);
    if (tip_errs_.empty()){
        ui->error_label->clear();
        return;
    }
}
