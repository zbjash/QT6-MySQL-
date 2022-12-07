#include "tenant_upassword.h"
#include "ui_tenant_upassword.h"
#include "share.h"


extern QString log_id;
extern int mode;

tenant_upassword::tenant_upassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tenant_upassword)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("修改密码"));

}

tenant_upassword::~tenant_upassword()
{
    delete ui;
}

void tenant_upassword::on_tup_commitButton_clicked()
{
    if(mode==0){
        QString oldpassword = ui->tup_oldputLineEdit->text();
        QString newpassword = ui->tup_newputLineEdit->text();
        QSqlQuery query;
        query.prepare("select tenant_password from tenant_account where tenant_id = :input ");
        query.bindValue(":input",log_id);
        if(query.exec()){
            if(query.first()){
                if(oldpassword == query.value(0).toString()){
                    QSqlQuery query2;
                    QString instruction = QString("update tenant_account set tenant_password = '%1' where tenant_id =%2 ").arg(newpassword).arg(log_id.toInt());
                    if(query2.exec(instruction))
                    QMessageBox::information(NULL,"密码修改成功","密码已修改",QMessageBox::Ok);
                }
                else {
                    QMessageBox::warning(NULL,"密码修改失败","现密码错误");
                }
            }
        }
    }
    else if(mode == 1){
        QString oldpassword = ui->tup_oldputLineEdit->text();
        QString newpassword = ui->tup_newputLineEdit->text();
        QSqlQuery query;
        query.prepare("select landlord_password from landlord_account where landlord_id = :input ");
        query.bindValue(":input",log_id);
        if(query.exec()){
            if(query.first()){
                if(oldpassword == query.value(0).toString()){
                    QSqlQuery query2;
                    QString instruction = QString("update landlord_account set landlord_password = '%1' where landlord_id =%2 ").arg(newpassword).arg(log_id.toInt());
                    if(query2.exec(instruction))
                    QMessageBox::information(NULL,"密码修改成功","密码已修改",QMessageBox::Ok);
                }
                else {
                    QMessageBox::warning(NULL,"密码修改失败","现密码错误");
                }
            }
        }
    }
}


void tenant_upassword::on_tup_cancelButton_2_clicked()
{
    this->close();
}

