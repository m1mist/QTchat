/**
  ******************************************************************************
  * @file           : TcpManager.h
  * @author         : hupujun
  * @brief          : None
  * @attention      : None
  * @date           : 24-9-13
  ******************************************************************************
 **/

#ifndef LLFCCHAT_TCPMANAGER_H
#define LLFCCHAT_TCPMANAGER_H

#include "global.h"
#include "singleton.hpp"

class TcpManager:public QObject, public Singleton<TcpManager>,
        public enable_shared_from_this<TcpManager>{
    Q_OBJECT;
public:
    TcpManager();
private:
    QTcpSocket socket_;
    QString host_;
    uint16_t port_{};
    QByteArray buffer_;
    bool b_recv_pending_{};//等待接收
    quint16 message_id_{};
    quint16 message_len_{};
public slots:
    void slot_tcp_connect(ServerInfo);
    void slot_send_data(ReqId reqId, QString data);
signals:
    void sig_con_success(bool b_success);
    void sig_send_data(ReqId reqId, QString data);
};


#endif //LLFCCHAT_TCPMANAGER_H
