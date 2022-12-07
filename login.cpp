#include "login.h"
#include "ui_login.h"
#include "edit.h"
#include "findback.h"
#include "tenantwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <qDebug>
#include <QTextEdit>
#include "share.h"
#include "adminwindow.h"

QString log_id;
int mode;
login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{

    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("房屋出租信息管理系统-登录"));
    connect(login::enter,SIGNAL(activated()),this,SLOT(on_l_loginButton_clicked())) ; //大键盘回车信号连接给登录
    connect(login::lenter,SIGNAL(activated()),this,SLOT(on_l_loginButton_clicked())) ; //小键盘回车信号连接给登录

    //设置正则表达式校验器使id只能输入数字
    ui->l_idLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]+$")));
    //设置正则表达式校验器使密码只能输入数字和字母
    ui->l_passwordLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[a-zA-Z0-9]+$")));
}

login::~login()
{
    delete ui;
}


void login::on_l_editButton_clicked()   //注册按钮
{
    edit *editw = new edit();
    editw->show();

}


void login::on_l_cancelButton_clicked() //退出按钮
{
    this->close();
}


void login::on_findbackButton_clicked() //找回按钮
{
    findback *fbw = new findback();
    fbw->show();
}


void login::on_l_loginButton_clicked()  //登录按钮
{
    if(ui->l_selectBox->currentIndex()==0   )
         mode = 0;
    else if(ui->l_selectBox->currentIndex()==1)
         mode = 1;
    else if(ui->l_selectBox->currentIndex()==2)
         mode = 2;
    //获取id和password

    log_id = ui->l_idLineEdit->text();
    QString password = ui->l_passwordLineEdit->text();
    QSqlQuery query;

    switch(mode){
    case(0):
        if(log_id.length()!=0 && password.length()!=0){
            query.prepare("select tenant_password from tenant_account where tenant_id = :input ");
            query.bindValue(":input",log_id.toInt());
            if(query.exec()){
                if(query.first()){
                    if(password==query.value(0).toString()){
                        this->close();
                        tenantwindow *tw = new tenantwindow();
                        tw->show();
                           break;
                    }
                    else{

                        QMessageBox::warning(NULL,"登录失败","账号或密码错误");
                        break;
                    }
                }
                else{
                    QMessageBox::warning(NULL,"登录失败","账号错误");
                }
            }
        }
        else{
            QMessageBox::warning(NULL,"登陆失败","账号和密码不能为空");
        }
    break;
    case(1):
        if(log_id.length()!=0 && password.length()!=0){
            query.prepare("select landlord_password from landlord_account where landlord_id = :input ");
            query.bindValue(":input",log_id.toInt());
            if(query.exec()){

                if(query.first()){

                    if(password==query.value(0).toString()){
                        this->close();
                        tenantwindow *tw = new tenantwindow();
                        tw->show();

                        break;
                    }
                    else{
                        QMessageBox::warning(NULL,"登录失败","账号或密码错误");
                        break;
                    }
                }
                else{
                    QMessageBox::warning(NULL,"登录失败","账号错误");
                }
            }
        }
        else{
            QMessageBox::warning(NULL,"登陆失败","账号和密码不能为空");
        }
    break;
    case(2):
        if(log_id.length()!=0 && password.length()!=0){
            query.prepare("select admin_password from admin_account where admin_id = :input ");
            query.bindValue(":input",log_id.toInt());
            if(query.exec()){
                if(query.first()){
                    if(password==query.value(0).toString()){
                        this->close();
                        adminwindow *aw = new adminwindow();
                        aw->show();
                        break;
                    }
                    else{
                        QMessageBox::warning(NULL,"登录失败","账号或密码错误");
                        break;
                    }
                }
                else{
                    QMessageBox::warning(NULL,"登录失败","账号错误");
                }
            }
        }
        else{
            QMessageBox::warning(NULL,"登陆失败","账号和密码不能为空");
        }
    break;

    }
}

