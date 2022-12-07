#include "tenant_update.h"
#include "ui_tenant_update.h"

#include "share.h"

extern QString log_id; //引用全局变量id
extern int mode;

tenant_update::tenant_update(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tenant_update)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("修改个人信息"));
}

tenant_update::~tenant_update()
{
    delete ui;
}

void tenant_update::on_tu_commitButton_clicked()
{
    QString name = ui->tu_nameLineEdit->text();
    QString city = ui->tu_cityLineEdit->text();
    QString age = ui->tu_ageLineEdit->text();
    QString email = ui->tu_emailLineEdit->text();
    QString Tel = ui->tu_TELLineEdit->text();

    if(Tel.length()!=11){    //是否电话正确
        QMessageBox::warning(NULL,"注册失败","请输入正确的电话号");
    }
    else{

           if(mode==0){
                QSqlQuery query_tu ;
                QString information_tu =QString("update tenant set tenant_name='%1',tenant_email ='%2',tenant_TEL = '%3',tenant_age = %4,tenant_site ='%5' where tenant_id =%6").arg(name).arg(email).arg(Tel).arg(age.toInt()).arg(city).arg(log_id.toInt());

                if(query_tu.exec(information_tu)){


                    QMessageBox::information(NULL,"修改成功","您的个人信息已经修改",QMessageBox::Ok);
                    this->close();
                }
                else
                {
                    QMessageBox::warning(NULL,"修改失败","修改失败");
                }
           }
           else if(mode ==1){
               QSqlQuery query_tu ;
               QString information_tu =QString("update landlord set landlord_name='%1',landlord_email ='%2',landlord_TEL = '%3',landlord_age = %4,landlord_site ='%5' where landlord_id =%6").arg(name).arg(email).arg(Tel).arg(age.toInt()).arg(city).arg(log_id.toInt());

               if(query_tu.exec(information_tu)){


                   QMessageBox::information(NULL,"修改成功","您的个人信息已经修改",QMessageBox::Ok);
                   this->close();
               }
               else
               {
                   QMessageBox::warning(NULL,"修改失败","修改失败");
               }
           }

    }

}

