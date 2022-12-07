#include "mrh_cancelrent.h"
#include "ui_mrh_cancelrent.h"
#include "share.h"

extern QString log_id;
mrh_cancelrent::mrh_cancelrent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mrh_cancelrent)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("取消出租 "));
    //获取房屋id
    QSqlQuery query;
    query.prepare("Select house_id from house where house_landlord = :id and house_tenant is null");
    query.bindValue(":id",log_id);
    if(query.exec()){
        while(query.next()){
            QString expression = query.value(0).toString();
             ui->comboBox->addItem(expression);
        }
    }

}

mrh_cancelrent::~mrh_cancelrent()
{
    delete ui;
}

void mrh_cancelrent::on_mrh_cancelrent_cancelButton_clicked()   //取消
{
    this->close();
}


void mrh_cancelrent::on_mrh_cancelrent_commitButton_clicked() //确认
{
        QString house_id = ui->comboBox->currentText();
        QSqlQuery query;
        query.prepare("delete from house where house_id = :id");
        query.bindValue(":id",house_id.toInt());
        if(query.exec()){
            QMessageBox::information(NULL,"取消成功","房屋已取消出租",QMessageBox::Ok);
            this->close();
        }
        else {
            QMessageBox::warning(NULL,"取消失败","取消失败，请稍后再试");
        }





}

