#include "edit.h"
#include "ui_edit.h"
#include "share.h"
#include <QRegularExpressionValidator>

edit::edit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edit)
{
    ui->setupUi(this);
     this->setWindowTitle(QStringLiteral("账号注册"));
    //设置正则表达式校验器使id只能输入数字
    ui->e_idLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]+$")));
    //设置正则表达式校验器使密码只能输入数字和字母
    ui->e_passwordLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[a-zA-Z0-9]+$")));
    //设置正则表达式校验器使电话号码只能输入数字
    ui->e_TelLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]+$")));
    //设置正则表达式校验器使年龄只能输入数字
     ui->e_ageLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]+$")));

}

edit::~edit()
{
    delete ui;
}

void edit::on_e_cancelButton_clicked()
{
    this->close();
}


void edit::on_e_editButton_clicked()
{
    QString id =ui->e_idLineEdit->text();
    QString password = ui->e_passwordLineEdit->text();
    QString name = ui->e_nameLineEdit->text();
    QString city = ui->e_cityLineEdit->text();
    QString age = ui->e_ageLineEdit->text();
    QString email = ui->e_emailLineEdit->text();
    QString Tel = ui->e_TelLineEdit->text();

    //设置注册模式
    if(ui->e_tenantBox->isChecked()==true )
         edit::mode = 0;
    else if(ui->e_landlordBox->isChecked()==true)
         edit::mode = 1;
    else
         edit::mode = 2;

    if(id.length()==0 ){
        QMessageBox::warning(NULL,"注册失败","您的账号长度不符合规定,请检查后重新输入");

    }
    else{
        if(password.length()<6 || password.length()>18){
            QMessageBox::warning(NULL,"注册失败","您的密码长度不符合规定，请检查后重新输入");
        }
        else {
            if(Tel.length()!=11){    //是否电话正确
                QMessageBox::warning(NULL,"注册失败","请输入正确的电话号");
            }
            else{
                switch(mode){
                case(0):
                    if(edit::tenant_isexists(id)){
                        QMessageBox::warning(NULL,"注册失败","该账号已存在");
                    }
                    else{
                        QSqlQuery query_t ;
                        QString information_t =QString("insert into tenant values(%1,'%2','%3','%4',%5,'%6')").arg(id.toInt()).arg(name).arg(email).arg(Tel).arg(age.toInt()).arg(city);

                        if(query_t.exec(information_t)){
                            QString information_t2 = QString("UPDATE tenant_account Set tenant_password = '%1' where tenant_id = %2").arg(password).arg(id.toInt());

                            if(query_t.exec(information_t2)){
                            QMessageBox::information(NULL,"注册成功","注册成功，请记住您的账号和密码",QMessageBox::Ok);
                            }
                            this->close();
                        }
                        else{
                            QMessageBox::warning(NULL,"注册失败","该手机号已注册过");
                        }
                    }
                    break;
                case(1):
                    if(edit::landlord_isexists(id)){
                        QMessageBox::warning(NULL,"注册失败","该账号已存在");
                    }
                    else{
                        QSqlQuery query_l ;
                        QString information_l =QString("insert into landlord values(%1,'%2','%3','%4',%5,'%6')").arg(id.toInt()).arg(name).arg(email)
                                    .arg(Tel).arg(age.toInt()).arg(city);
                        if(query_l.exec(information_l)){
                            QString information_l2 = QString("UPDATE landlord_account Set landlord_password = '%1' where landlord_id = %2").arg(password).arg(id.toInt());
                            if(query_l.exec(information_l2)){
                            QMessageBox::information(NULL,"注册成功","注册成功，请记住您的账号和密码",QMessageBox::Ok);
                            this->close();
                            }
                            else {
                                QMessageBox::warning(NULL,"注册失败","注册失败，请稍后再试");
                          }
                        }
                        else{
                            QMessageBox::warning(NULL,"注册失败","该手机号已注册过");
                        }
                    }
                    break;
                case(2):
                    QMessageBox::warning(NULL,"注册失败","请选择你的身份");
                    break;
                }

            }

        }
    }
}




