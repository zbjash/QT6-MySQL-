#ifndef LANDLORDWINDOW_H
#define LANDLORDWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QString>
namespace Ui {
class landlordwindow;
}



class landlordwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit landlordwindow (QWidget *parent=nullptr);



    ~landlordwindow();

private slots:
    void on_Home_SearchButton_clicked();

    void on_Home_myhomeButton_clicked();

    void on_quitButton_clicked();

    void on_Home_CallButton_clicked();

    void on_Mine_uiButton_clicked();

    void on_Mine_refreshButton_clicked();

private:

    Ui::landlordwindow *ui;
    QSqlTableModel *model_home;



};

#endif // LANDLORDWINDOW_H
