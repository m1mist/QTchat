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
    MainWindow w;
    w.show();
    return QApplication::exec();
}
