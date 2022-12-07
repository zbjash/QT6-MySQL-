#include "myrentinghouse.h"
#include "ui_myrentinghouse.h"
#include <QSqlTableModel>
#include "share.h"
#include "mrh_rent.h"
#include "mrh_cancelrent.h"
#include "mrh_addrecord.h"

extern QString log_id;

myrentinghouse::myrentinghouse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myrentinghouse)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("我的房屋"));

    //设置数据库显示
    model = new QSqlTableModel(this);
    model ->setTable("house");
    model->setFilter(QString("house_landlord = %1").arg(log_id));
    model->select();


    //初始化界面
    myrentinghouse::settitle();

    //tableview绑定
    ui->mrh_houseview->setModel(model);

    //tableview设置
    ui->mrh_houseview->setColumnHidden(5,true);//隐藏landlord_id列
    ui->mrh_houseview->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止更改
    ui->mrh_houseview->verticalHeader()->hide();  //隐藏左侧索引
    ui->mrh_houseview->resizeColumnsToContents();   //自适应调整
    ui->mrh_houseview->setAlternatingRowColors(true);  //行之间颜色变化
}

myrentinghouse::~myrentinghouse()
{
    delete ui;
}

void myrentinghouse::on_pushButton_4_clicked()  //退出
{
    this->close();
}


void myrentinghouse::on_mrh_rentButton_clicked() //添加房屋
{
    mrh_rent *w = new mrh_rent();
     w->show();

}


void myrentinghouse::on_mrh_refreshButton_clicked() //刷新
{
    model->setTable("house");
    model->setFilter(QString("house_landlord = %1").arg(log_id));
    myrentinghouse::settitle();
    model->select();

    //tableview绑定
     ui->mrh_houseview->setModel(model);
    //tableview设置


    ui->mrh_houseview->setColumnHidden(5,true);//隐藏landlord_id列
    ui->mrh_houseview->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止更改
    ui->mrh_houseview->verticalHeader()->hide();  //隐藏左侧索引
    ui->mrh_houseview->resizeColumnsToContents();   //自适应调整
    ui->mrh_houseview->setAlternatingRowColors(true);  //行之间颜色变化

}


void myrentinghouse::on_mrh_cancelrentButton_clicked()  //取消出租
{
    mrh_cancelrent *w = new mrh_cancelrent();
    w->show();

}


void myrentinghouse::on_mrh_addrecordButton_clicked()   //达成交易
{
    mrh_addrecord *w = new mrh_addrecord();
    w->show();

}

