#ifndef MYRENTINGHOUSE_H
#define MYRENTINGHOUSE_H

#include <QWidget>
#include <QSqlTableModel>


namespace Ui {
class myrentinghouse;
}

class myrentinghouse : public QWidget
{
    Q_OBJECT

public:
    explicit myrentinghouse(QWidget *parent = nullptr);
    ~myrentinghouse();

private slots:
    void on_pushButton_4_clicked();

    void on_mrh_rentButton_clicked();

    void on_mrh_refreshButton_clicked();

    void on_mrh_cancelrentButton_clicked();

    void on_mrh_addrecordButton_clicked();

private:
    Ui::myrentinghouse *ui;
    QSqlTableModel *model;
    void settitle(){
        model->setHeaderData(0,Qt::Horizontal,"房屋id");
        model->setHeaderData(1,Qt::Horizontal,"租客id");
        model->setHeaderData(2,Qt::Horizontal,"城市");
        model->setHeaderData(3,Qt::Horizontal,"房屋信息");
        model->setHeaderData(4,Qt::Horizontal,"房屋名");
        model->setHeaderData(6,Qt::Horizontal,"截止日期");
    }

};

#endif // MYRENTINGHOUSE_H
