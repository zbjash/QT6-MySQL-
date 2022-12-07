#include "mrh_addrecord.h"
#include "ui_mrh_addrecord.h"
#include "share.h"

extern QString log_id;

mrh_addrecord::mrh_addrecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mrh_addrecord)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("达成交易"));
    //租客id只能是数字
    ui->mrh_addrecord_tenantLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]+$")));

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

    //设置date输入弹出日历
    ui->start_date->setCalendarPopup(true);
    ui->end_date->setCalendarPopup(true);
    //设置最小日期
    ui->start_date->setMinimumDate(QDate::currentDate());
    ui->end_date->setMinimumDate(QDate::currentDate());//调用QDate类返回当前日期
}

mrh_addrecord::~mrh_addrecord()
{
    delete ui;
}


void mrh_addrecord::on_mrd_addrecord_commitButton_clicked() //提交
{
    QSqlQuery query;
    QString t_id = ui->mrh_addrecord_tenantLineEdit->text();
    QString h_id = ui->comboBox->currentText();
    QString rmoney = ui->mrh_addrecord_rentmoneyLineEdit->text();

    QDate start_date = ui->start_date->date();
    QDate end_date = ui->end_date->date();

    if(t_id.length()==0){
        QMessageBox::warning(NULL,"提交失败","租客id不能为空");

    }
    else {
        query.prepare("select tenant_id from tenant_account where tenant_id = :id");
        query.bindValue(":id",t_id.toInt());
        if(query.exec()){
            if(query.next()){

                    QSqlQuery query2;
                    query2.prepare("insert into record (tenant_id,landlord_id,house_id,date_start,date_end,rent)"
                                                  "values (:t_id,:l_id,:h_id,:start_date,:end_date,:rm)");
                    query2.bindValue(":t_id",t_id.toInt());
                    query2.bindValue(":h_id",h_id.toInt());
                    query2.bindValue(":l_id",log_id.toInt());
                    query2.bindValue(":start_date",start_date);
                    query2.bindValue(":end_date",end_date);
                    query2.bindValue(":rm",rmoney.toInt());

                    if(query2.exec()){
                        QMessageBox::information(NULL,"提交成功","您已成功添加出租记录,该记录若存在不实，您或租客可以联系管理员进行修改",QMessageBox::Ok);
                    }
                    else {
                        QMessageBox::warning(NULL,"提交失败","提交失败，请稍后重试");
                    }

            }
            else{
                QMessageBox::warning(NULL,"提交失败","该租客id不存在,请核对后重试");
            }
        }
    }


}


void mrh_addrecord::on_start_date_userDateChanged()
{
     ui->end_date->setMinimumDate(ui->start_date->date());//设置截止日期永远大于等于起始日期
}


void mrh_addrecord::on_mrd_addrecord_cancelButton_clicked()
{
    this->close();
}

