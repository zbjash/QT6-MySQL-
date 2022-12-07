#include "tenantwindow.h"
#include "tenant_upassword.h"
#include "ui_tenantwindow.h"
#include "share.h"

#include "tenant_update.h"
#include "tenant_upassword.h"
#include "myrentinghouse.h"

extern QString log_id; //引用全局变量id
extern int mode; //引用全局变量模式

tenantwindow::tenantwindow(QWidget *parent ) :
    QMainWindow(parent),

    ui(new Ui::tenantwindow)
{
    ui->setupUi(this);



    //更新房屋数据库,将已过期的房屋恢复出租状态
        QSqlQuery query,query1;
        query.prepare("select house_id from house where timestampdiff(day,renting_end,now())>0");
        if(query.exec()){
           while (query.next()){
                   query1.exec(QString("update house set house_tenant = null ,renting_end =null where house_id = %1").arg(query.value(0).toInt()));
                }

            }


    //设置数据库视图窗口
    this->setWindowTitle(QStringLiteral("房屋出租管理系统"));
    model_home = new QSqlTableModel(this);
    model_home ->setTable("s_house");

    model_home->select();
    //绑定
    ui->Home_view ->setModel(model_home);
    //修改TableView选项
    ui->Home_view->setSelectionBehavior(QAbstractItemView::SelectRows);    //一次只能选择一行
    ui->Home_view->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止更改
    ui->Home_view->verticalHeader()->hide();  //隐藏左侧索引
    ui->Home_view->resizeColumnsToContents();   //自适应调整
    ui->Home_view->setAlternatingRowColors(true);  //行之间颜色变化

    //设置个人信息
    if(mode ==0){
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
    else if(mode == 1){
        QString t_id ;
        QString t_name;
        QString t_email;
        QString t_TEL;
        QString t_age;
        QString t_site;

        QSqlQuery query;
        query.prepare("select landlord_id , landlord_name , landlord_email,landlord_TEL,landlord_age,landlord_site from landlord where landlord_id = :input");
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

}

tenantwindow::~tenantwindow()
{

    delete ui;
}

void tenantwindow::on_Home_SearchButton_clicked()       //关键字查询
{
    QString input = ui->Home_SearchLineEdit->text();

    if(ui->checkBox->isChecked()){
        model_home->setTable("empty_house");
        QString filter  = QObject::tr("房屋信息 like '%%1%' or 房屋名字 like '%%1%' or 房屋城市 like '%%1%'").arg(input);
        model_home ->setFilter(filter);

        model_home ->select();

        ui->Home_view->resizeColumnsToContents();

    }
    else{
        model_home->setTable("s_house");
        QString filter  = QObject::tr("房屋信息 like '%%1%' or 房屋名字 like '%%1%' or 房屋城市 like '%%1%'").arg(input);
        model_home ->setFilter(filter);

        model_home->select();

        ui->Home_view->resizeColumnsToContents();
    }
}


void tenantwindow::on_Home_myhomeButton_clicked()       //我的住房
{
    if(mode==0){
        model_home->setTable("tenant_house");
        QString filter  = QObject::tr("租客id like '%%1%'").arg(log_id);
        model_home->setFilter(filter);
        model_home->select();
        ui->Home_view->setColumnHidden(4,true);
        ui->Home_view->resizeColumnsToContents();
    }
    else if(mode ==1){
        myrentinghouse *mrhw = new myrentinghouse();
        mrhw->show();


    }
}


void tenantwindow::on_quitButton_clicked()      //退出
{
    this->close();
}


void tenantwindow::on_Home_CallButton_clicked() //联系房东
{

    int row= ui->Home_view->currentIndex().row();

    QModelIndex index = model_home->index(row,0);
    QVariant house_id = model_home->data(index);

    QSqlQuery query;
    query.prepare("select landlord_TEL from landlord,house where house.house_landlord = landlord.landlord_id and house_id = :input");
    query.bindValue(":input",house_id.toInt());
    if(query.exec()){
        if(query.first()){
            QString expression1 = QString("房屋id为");
            expression1 +=house_id.toString();
            QString expression2 =QString("的房屋，该房东电话是：");
            expression2 += query.value(0).toString();
            expression1 += expression2;
            QMessageBox::information(NULL,"查询成功",expression1,QMessageBox::Ok);
        }
        else{
            QMessageBox::warning(NULL,"查询失败","请先选择想联系房东的房屋");
        }
    }
    else {
        QMessageBox::warning(NULL,"查询失败","查询失败，请稍后重试");
    }



}


void tenantwindow::on_Mine_uiButton_clicked()       //进入更改个人信息界面
{
    tenant_update *tuw = new tenant_update();
    tuw->show();
}


void tenantwindow::on_Mine_refreshButton_clicked()  //查询or刷新
{

    if(mode ==0){
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
    else if(mode == 1){
        QString t_id ;
        QString t_name;
        QString t_email;
        QString t_TEL;
        QString t_age;
        QString t_site;

        QSqlQuery query;
        query.prepare("select landlord_id , landlord_name , landlord_email,landlord_TEL,landlord_age,landlord_site from landlord where landlord_id = :input");
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
}


void tenantwindow::on_Mine_quitButton_clicked() //退出
{
    this->close();
}


void tenantwindow::on_Mine_upButton_clicked() //
{
    tenant_upassword* tup =  new tenant_upassword();
    tup ->show();

}

