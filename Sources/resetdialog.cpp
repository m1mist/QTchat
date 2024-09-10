/**
  ******************************************************************************
  * @file           : resetdialog.cpp
  * @author         : 16649
  * @brief          : None
  * @attention      : None
  * @date           : 24-9-9
  ******************************************************************************
 **/

// You may need to build the project (run Qt uic code generator) to get "ui_ResetDialog.h" resolved
#include "resetdialog.h"
#include "Forms/ui_resetdialog.h"
#include <QDebug>
#include <QRegularExpression>
#include "global.h"
#include "HttpManager.h"

ResetDialog::ResetDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::ResetDialog)
{
    ui->setupUi(this);

    connect(ui->user_edit,&QLineEdit::editingFinished,this,[this](){
        checkUserValid();
    });

    connect(ui->email_edit, &QLineEdit::editingFinished, this, [this](){
        checkEmailValid();
    });

    connect(ui->password_edit, &QLineEdit::editingFinished, this, [this](){
        checkPassValid();
    });


    connect(ui->verify_edit, &QLineEdit::editingFinished, this, [this](){
        checkVerifyValid();
    });

    //连接reset相关信号和注册处理回调
    initHandlers();
    connect(HttpManager::getInstance().get(), &HttpManager::sig_reset_mod_finish, this,
            &ResetDialog::slot_reset_mod_finish);

}


ResetDialog::~ResetDialog()
{
    delete ui;
}

void ResetDialog::on_cancel_button_clicked()
{
    qDebug() << "confirm btn clicked ";
    emit switchLogin();
}

void ResetDialog::on_get_verify_code_button_clicked()
{
    qDebug()<<"receive verify btn clicked ";
    auto email = ui->email_edit->text();
    auto bcheck = checkEmailValid();
    if(!bcheck){
        return;
    }

    //发送http请求获取验证码
    QJsonObject json_obj;
    json_obj["email"] = email;
    HttpManager::getInstance()->PostHttpReq(QUrl(gate_url_prefix+"/verify_code"),
                                            json_obj, ReqId::ID_GET_VERIFY, Modules::RESET);
}

void ResetDialog::slot_reset_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS){
        showTip(tr("网络请求错误"),false);
        return;
    }

    // 解析 JSON 字符串,res需转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    //json解析错误
    if(jsonDoc.isNull()){
        showTip(tr("json解析错误"),false);
        return;
    }

    //json解析错误
    if(!jsonDoc.isObject()){
        showTip(tr("json解析错误"),false);
        return;
    }


    //调用对应的逻辑,根据id回调。
    _handlers[id](jsonDoc.object());

    return;
}

bool ResetDialog::checkUserValid()
{
    if(ui->user_edit->text() == ""){
        AddTipErr(TipErr::TIP_USER_ERR, tr("用户名不能为空"));
        return false;
    }

    DelTipErr(TipErr::TIP_USER_ERR);
    return true;
}


bool ResetDialog::checkPassValid()
{
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



bool ResetDialog::checkEmailValid()
{
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

bool ResetDialog::checkVerifyValid()
{
    auto pass = ui->verify_edit->text();
    if(pass.isEmpty()){
        AddTipErr(TipErr::TIP_VARIFY_ERR, tr("验证码不能为空"));
        return false;
    }

    DelTipErr(TipErr::TIP_VARIFY_ERR);
    return true;
}

void ResetDialog::AddTipErr(TipErr te, QString tips)
{
    _tip_errs[te] = tips;
    showTip(tips, false);
}

void ResetDialog::DelTipErr(TipErr te)
{
    _tip_errs.remove(te);
    if(_tip_errs.empty()){
        ui->error_label->clear();
        return;
    }

    showTip(_tip_errs.first(), false);
}

void ResetDialog::initHandlers()
{
    //注册获取验证码回包逻辑
    _handlers.insert(ReqId::ID_GET_VERIFY, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"),false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("验证码已发送到邮箱，注意查收"), true);
        qDebug()<< "email is " << email ;
    });

    //注册注册用户回包逻辑
    _handlers.insert(ReqId::ID_RESET_PWD, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"),false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("重置成功,点击返回登录"), true);
        qDebug()<< "email is " << email ;
        qDebug()<< "user uuid is " <<  jsonObj["uuid"].toString();
    });
}

void ResetDialog::showTip(QString str, bool b_ok)
{
    if(b_ok){
        ui->error_label->setProperty("state","normal");
    }else{
        ui->error_label->setProperty("state","err");
    }

    ui->error_label->setText(str);

    repolish(ui->error_label);
}

void ResetDialog::on_confirm_button_clicked()
{
    bool valid = checkUserValid();
    if(!valid){
        return;
    }

    valid = checkEmailValid();
    if(!valid){
        return;
    }

    valid = checkPassValid();
    if(!valid){
        return;
    }

    valid = checkVerifyValid();
    if(!valid){
        return;
    }

    //发送http重置用户请求
    QJsonObject json_obj;
    json_obj["user"] = ui->user_edit->text();
    json_obj["email"] = ui->email_edit->text();
    json_obj["passwd"] = xor_string(ui->password_edit->text());
    json_obj["verifycode"] = ui->verify_edit->text();
    HttpManager::getInstance()->PostHttpReq(QUrl(gate_url_prefix+"/reset_pwd"),
                                        json_obj, ReqId::ID_RESET_PWD,Modules::RESET);
}
