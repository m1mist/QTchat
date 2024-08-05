#include <QApplication>
#include <QPushButton>
#include <QFile>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QFile qss(":/style/styles.qss");
    if(qss.open(QFile::ReadOnly)){
        qDebug(".qss open");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }else{
        qDebug(".qss open failed");
    }
    //读取ini配置文件
    QSettings settings("config.ini", QSettings::IniFormat);
    QString gate_host = settings.value("GateServer/host").toString();
    QString gate_port = settings.value("GateServer/port").toString();
    gate_url_prefix = "http://"+gate_host+":"+gate_port;
    MainWindow w;
    w.show();
    return QApplication::exec();
}
