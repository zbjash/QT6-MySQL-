#include "mrh_rent.h"
#include "ui_mrh_rent.h"
#include "share.h"
#include <qmessagebox.h>

extern QString log_id;

mrh_rent::mrh_rent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mrh_rent)
{

    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("我要出租"));
}

mrh_rent::~mrh_rent()
{
    delete ui;
}




void mrh_rent::on_mrh_rent_commitButton_clicked()   //提交
{

    QString name = ui->mrh_rent_nameLineEdit->text();
    QString city = ui->mrh_rent_cityLineEdit->text();
    QString info = ui->mrh_rent_infoTextEdit->toPlainText() ;
    if(name.length()!=0){
        if(city.length()!=0 ){
            QSqlQuery query;
            query.prepare("INSERT INTO house (house_id,house_name,house_site,house_info,house_landlord) VALUES (0,:name,:city,:info,:id)");
            query.bindValue(":name",name);
            query.bindValue(":city",city);
            query.bindValue(":info",info);
            query.bindValue(":id",log_id);
            if(query.exec()){
                QMessageBox::information(NULL,"提交成功","房屋出租信息已提交",QMessageBox::Ok);
                ui->mrh_rent_nameLineEdit->clear();
                ui->mrh_rent_cityLineEdit->clear();
                ui->mrh_rent_infoTextEdit->clear();

            }
            else {
                QMessageBox::warning(NULL,"提交失败","提交失败，请稍后重试");
            }
        }
        else {
            QMessageBox::warning(NULL,"提交失败","房屋地址不能为空");
        }
    }
    else {
        QMessageBox::warning(NULL,"提交失败","房屋名不能为空");
    }




}

void mrh_rent::on_mrh_rent_cancelButton_clicked() //取消
{
    this->close();
}

void mrh_rent::on_mrh_rent_infoTextEdit_textChanged()
{
    QString textContent = ui->mrh_rent_infoTextEdit->toPlainText(); //限制最大输入长度
        int length = textContent.length();
        int maxLength = 40; // 最大字符数
        if(length > maxLength) {
            int position = ui->mrh_rent_infoTextEdit->textCursor().position();
            QTextCursor textCursor = ui->mrh_rent_infoTextEdit->textCursor();
            textContent.remove(position - (length - maxLength), length - maxLength);
            ui->mrh_rent_infoTextEdit->setText(textContent);
            textCursor.setPosition(position - (length - maxLength));
            ui->mrh_rent_infoTextEdit->setTextCursor(textCursor);

        }

}
