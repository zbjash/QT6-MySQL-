#include "login.h"
#include<QSqlDatabase>
#include <QApplication>

int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");//连接本机数据库
        db.setPort(3306);//默认端口
        db.setDatabaseName("AAA");//数据库名称
        db.setUserName("XXX");//用户名
        db.setPassword("YYYYYYYYYY");//用户密码
        db.open();//连接数据库

    QApplication a(argc, argv);
    a.addLibraryPath("./plugins"); //打包后能连接mysql的关键


    login w;
    w.show();
    return a.exec();
}
