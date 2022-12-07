#include "login.h"
#include<QSqlDatabase>
#include <QApplication>

int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");//连接本机数据库
        db.setPort(3306);//默认端口
        db.setDatabaseName("mydesign");//数据库名称
        db.setUserName("root");//用户名
        db.setPassword("20020816jiang");//用户密码
        db.open();//连接数据库

    QApplication a(argc, argv);
    a.addLibraryPath("./plugins");


    login w;
    w.show();
    return a.exec();
}
