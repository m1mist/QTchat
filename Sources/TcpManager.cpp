/**
  ******************************************************************************
  * @file           : TcpManager.cpp
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-9-13
  ******************************************************************************
 **/

#include "TcpManager.h"

#include "UserManager.h"

TcpManager::TcpManager():
    host_(""), port_(0), b_recv_pending_(false), message_id_(0), message_len_(0){
    QObject::connect(&socket_, &QTcpSocket::connected, [&](){
        qDebug() << "Connected to Server!";
        emit sig_con_success(true);
    });
    QObject::connect(&socket_, &QTcpSocket::readyRead, [&](){
        //可读时
        //读取所有数据
        buffer_.append(socket_.readAll());
        QDataStream stream(&buffer_, QIODevice::ReadOnly);
        stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);

        forever{
            if (!b_recv_pending_){
                // 检查缓冲区中的数据是否足够解析出一个消息头（消息ID + 消息长度）
                if (buffer_.size() < static_cast<int>(sizeof(quint16) * 2)){
                    return ;//数据不够
                }
                // 预读取消息ID和消息长度，但不从缓冲区中移除
                stream >> message_id_ >> message_len_;

                //将buffer 中的前四个字节移除
                buffer_ = buffer_.mid(sizeof(quint16) * 2);

                // 输出读取的数据
                qDebug() << "Message ID:" << message_id_ << ", Length:" << message_len_;
            }
            //buffer剩余长读是否满足消息体长度，不满足则退出继续等待接受
            if(buffer_.size() < message_len_){
                b_recv_pending_ = true;
                return;
            }

            b_recv_pending_ = false;
            // 读取消息体
            QByteArray message_body = buffer_.mid(0, message_len_);
            qDebug() << "receive body msg is " << message_body ;

            buffer_ = buffer_.mid(message_len_);
            handleMsg(ReqId(message_id_), message_len_, message_body);
        }
    });

       QObject::connect(&socket_, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred), [&](QAbstractSocket::SocketError socketError) {
           Q_UNUSED(socketError)
           qDebug() << "Error:" << socket_.errorString();
       });

    // 处理连接断开
    QObject::connect(&socket_, &QTcpSocket::disconnected, [&]() {
        qDebug() << "Disconnected from server.";
    });

    QObject::connect(this, &TcpManager::sig_send_data, this, &TcpManager::slot_send_data);
    initHandlers();
}

void TcpManager::slot_tcp_connect(const ServerInfo& si) {
    qDebug()<< "receive tcp connect signal";
    // 尝试连接到服务器
    qDebug() << "Connecting to server...";
    host_ = si.host;
    port_ = static_cast<uint16_t>(si.port.toUInt());
    socket_.connectToHost(si.host, port_);
}

void TcpManager::slot_send_data(ReqId reqId, const QString& data)
{
    uint16_t id = reqId;

    // 将字符串转换为UTF-8编码的字节数组
    QByteArray dataBytes = data.toUtf8();

    // 计算长度（使用网络字节序转换）
    auto len = static_cast<quint16>(data.size());

    // 创建一个QByteArray用于存储要发送的所有数据
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    // 设置数据流使用网络字节序(大端)
    out.setByteOrder(QDataStream::BigEndian);

    // 写入ID和长度
    out << id << len;

    // 添加字符串数据
    block.append(dataBytes);

    // 发送数据
    socket_.write(block);
}

void TcpManager::initHandlers() {
    handlers_.insert(ReqId::ID_CHAT_LOGIN_RSP, [this](ReqId id, int len, const QByteArray& data){
        Q_UNUSED(len)
        qDebug()<< "handle id is "<< id << " data is " << data;

        QJsonDocument json_doc = QJsonDocument::fromJson(data);

        if(json_doc.isNull()){
            qDebug() << "Failed to create QJsonDocument.";
            return;
        }

        QJsonObject json_obj = json_doc.object();
        if(!json_obj.contains("error")){
            int err = ErrorCodes::ERROR_JSON;
            qDebug() << "Login Failed, error: Json Parse Error" << err ;
            emit sig_login_failed(err);
            return;
        }

        int err = json_obj["error"].toInt();
        if(err != ErrorCodes::SUCCESS){
            qDebug() << "Login Failed, error: " << err ;
            emit sig_login_failed(err);
            return;
        }
    UserManager::GetInstance()->SetUid(json_obj["uid"].toInt());
    UserManager::GetInstance()->SetName(json_obj["name"].toString());
    UserManager::GetInstance()->SetToken(json_obj["token"].toString());
    emit sig_switch_chatdialog();
    });
}

void TcpManager::handleMsg(ReqId id, int len, QByteArray data) {
    auto it = handlers_.find(id);
    if (it == handlers_.end()){
        qDebug() << "handle error: not found id[" << id << "]" << "!\n";
    }
    it.value()(id, len, std::move(data));
}




