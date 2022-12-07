#include "landlordwindow.h"
#include "ui_landlordwindow.h"
#include <QSqlTableModel>
#include <QLineEdit>
#include <QSqlQuery>
#include <QString>
#include "share.h"
#include <QMessageBox>
#include "calllandlord.h"
#include "tenant_update.h"

extern QString log_id; //引用全局变量id

landlordwindow::landlordwindow(QWidget *parent ) :
    QMainWindow(parent),

    ui(new Ui::landlordwindow)
{
    ui->setupUi(this);

    //设置数据库视图窗口
    this->setWindowTitle(QStringLiteral("房屋出租管理系统-租客"));
    model_home = new QSqlTableModel(this);
    model_home ->setTable("s_house");
    model_home->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_home->select();
    //绑定
    ui->Home_view ->setModel(model_home);
    //修改TableView选项
    ui->Home_view->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止更改
    ui->Home_view->verticalHeader()->hide();  //隐藏左侧索引
    ui->Home_view->resizeColumnsToContents();   //自适应调整
    ui->Home_view->setAlternatingRowColors(true);  //行之间颜色变化

    //设置个人信息
    QString t_id ;
    QString t_name;
    QString t_email;
    QString t_TEL;
    QString t_age;
    QString t_site;

    QSqlQuery query;
    query.prepare("select tenant_id , tenant_name , tenant_email,tenant_TEL,tenant_age,tenant_site from tenant where tenant_id = :input");
    query.bindValue(":input",log_id);
    if(query.exec()){
        if(query.next()){
            t_id = query.value(0).toString();
            t_name = query.value(1).toString();
            t_email = query.value(2).toString();
            t_TEL = query.value(3).toString();
            t_age = query.value(4).toString();
            t_site = query.value(5).toString();
        }
        ui->Mine_account->setText(t_id);
        ui->Mine_name->setText(t_name);
        ui->Mine_email->setText(t_email);
        ui->Mine_Tel->setText(t_TEL);
        ui->Mine_age->setText(t_age);
        ui->Mine_city->setText(t_site);
    }
    else {
        QMessageBox::warning(NULL,"查询失败","查询失败");
    }
}

tenantwindow::~tenantwindow()
{

    delete ui;
}

void tenantwindow::on_Home_SearchButton_clicked()       //查询
{
    QString input = ui->Home_SearchLineEdit->text();

    if(ui->checkBox->isChecked()){
        model_home->setTable("empty_house");
        QString filter  = QObject::tr("房屋名字 like '%%1%'").arg(input);
        model_home ->setFilter(filter);

        model_home ->select();

        ui->Home_view->resizeColumnsToContents();

    }
    else{
        model_home->setTable("s_house");
        QString filter  = QObject::tr("房屋名字 like '%%1%'").arg(input);
        model_home ->setFilter(filter);

        model_home->select();

        ui->Home_view->resizeColumnsToContents();
    }
}


void tenantwindow::on_Home_myhomeButton_clicked()       //我的住房
{
    model_home->setTable("tenant_house");
    QString filter  = QObject::tr("租客id like '%%1%'").arg(log_id);
    model_home->setFilter(filter);
    model_home->select();
    ui->Home_view->resizeColumnsToContents();

}


void tenantwindow::on_quitButton_clicked()      //退出
{
    this->close();
}


void tenantwindow::on_Home_CallButton_clicked()
{
    callLandlord *clw = new  callLandlord();
    clw->show();
}


void tenantwindow::on_Mine_uiButton_clicked()
{
    tenant_update *tuw = new tenant_update();
    tuw->show();
}


void tenantwindow::on_Mine_refreshButton_clicked()
{
    QString t_id ;
    QString t_name;
    QString t_email;
    QString t_TEL;
    QString t_age;
    QString t_site;

    QSqlQuery query;
    query.prepare("select tenant_id , tenant_name , tenant_email,tenant_TEL,tenant_age,tenant_site from tenant where tenant_id = :input");
    query.bindValue(":input",log_id);
    if(query.exec()){
        if(query.next()){
            t_id = query.value(0).toString();
            t_name = query.value(1).toString();
            t_email = query.value(2).toString();
            t_TEL = query.value(3).toString();
            t_age = query.value(4).toString();
            t_site = query.value(5).toString();
        }
        ui->Mine_account->setText(t_id);
        ui->Mine_name->setText(t_name);
        ui->Mine_email->setText(t_email);
        ui->Mine_Tel->setText(t_TEL);
        ui->Mine_age->setText(t_age);
        ui->Mine_city->setText(t_site);
    }
    else {
        QMessageBox::warning(NULL,"查询失败","查询失败");
    }
}

