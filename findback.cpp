#include "findback.h"
#include "ui_findback.h"
#include "share.h"

findback::findback(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::findback)
{
    ui->setupUi(this);
     this->setWindowTitle(QStringLiteral("找回账号密码"));

     ui->fb_TelLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]+$")));
}

findback::~findback()
{
    delete ui;
}

void findback::on_fb_fbButton_clicked()
{
    if(ui->fb_select_tenant->isChecked()==true )
         mode = 0;
    else if(ui->fb_select_landlord->isChecked()==true)
         mode = 1;
    else
         mode = 2;
    QString Tel = ui->fb_TelLineEdit->text();

    QSqlQuery query;
    QSqlQuery query2;
    QString expression;
    QString expression2;


    switch (mode) {
        case (0):
            query.prepare("select tenant_password from"
                                          "(select  tenant_TEL , tenant_id as'id' from tenant  where tenant_TEL = :input )as a,tenant_account"
                                          " where a.id = tenant_id");
            query.bindValue(":input",Tel);

            query2.prepare("select tenant_id from tenant where tenant_TEL = :input");
            query2.bindValue(":input",Tel);
            if(query.exec() && query2.exec()){

                if(query.first() && query2.first()){

                    expression += query.value(0).toString();
                    ui->fb_passwordLineEdit->setText(expression);
                    expression2 += query2.value(0).toString();
                    ui->fb_idLineEdit->setText(expression2);
                    QMessageBox::information(NULL,"找回成功","您的账号及密码如下",QMessageBox::Ok);
                }
                else{
                    QMessageBox::warning(NULL,"找回失败","该电话未注册");
                }
            }


            else{
                QMessageBox::warning(NULL,"查询错误","查询错误请稍后再试");
            }
        break;
        case(1):
            query.prepare("select landlord_password from"
                                      "(select  landlord_TEL , landlord_id as'id' from landlord  where landlord_TEL = :input )as a,landlord_account"
                                      " where a.id = landlord_id");
            query.bindValue(":input",Tel);
            query2.prepare("select landlord_id from landlord where landlord_TEL = :input");
            query2.bindValue(":input",Tel);

            if(query.exec()&&query2.exec()){

                if(query.first() && query2.first()){
                    qDebug() <<"succ1";
                    expression += query.value(0).toString();
                    ui->fb_passwordLineEdit->setText(expression);
                    expression2 += query2.value(0).toString();
                    ui->fb_idLineEdit->setText(expression2);
                    QMessageBox::information(NULL,"找回成功","您的账号及密码如下",QMessageBox::Ok);
                }

                else{
                    QMessageBox::warning(NULL,"找回失败","该电话未注册");
                }
            }
            else{
                QMessageBox::warning(NULL,"查询错误","查询错误请稍后再试");
            }
          break;
        case(2):
            QMessageBox::warning(NULL,"找回失败","请选择你的身份");
        break;

    }


}

