#ifndef EDIT_H
#define EDIT_H

#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QRegularExpression>

namespace Ui {
class edit;
}

class edit : public QWidget
{
    Q_OBJECT

public:
    explicit edit(QWidget *parent = nullptr);
    ~edit();

private slots:
    void on_e_cancelButton_clicked();

    void on_e_editButton_clicked();

private:
    Ui::edit *ui;
       int mode;

private:
    bool tenant_isexists(const QString &id){
        QSqlQuery query_t;
        query_t.exec(QString("SELECT * from tenant_account WHERE tenant_id = '%1'").arg(id));
        if(query_t.next()){
            return true;
        }
        else{
            return false;
        }
    }

    bool landlord_isexists(const QString &id){
        QSqlQuery query_l;
        query_l.exec(QString("SELECT * from landlord_account WHERE landlord_id = '%1'").arg(id));
        if(query_l.next()){
            return true;
        }
        else{
            return false;
        }
    }



};


#endif // EDIT_H
