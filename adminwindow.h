#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>

namespace Ui {
class adminwindow;
}

class adminwindow : public QWidget
{
    Q_OBJECT

public:
    explicit adminwindow(QWidget *parent = nullptr);
    ~adminwindow();




private slots:

    void on_addButton_clicked();

    void on_cancelButton_clicked();

    void on_updateButton_clicked();

    void on_delButton_clicked();

    void on_commitButton_clicked();

    void on_pushButton_2_clicked();


private:
    Ui::adminwindow *ui;
    QSqlTableModel *model_t;
    QSqlTableModel *model_l;
    QSqlTableModel *model_h;
    QSqlTableModel *model_r;
    QSqlTableModel *model_ta;
    QSqlTableModel *model_la;


};

#endif // ADMINWINDOW_H
