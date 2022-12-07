#ifndef TENANTWINDOW_H
#define TENANTWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QString>
namespace Ui {
class tenantwindow;
}



class tenantwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit tenantwindow (QWidget *parent=nullptr);



    ~tenantwindow();

private slots:
    void on_Home_SearchButton_clicked();

    void on_Home_myhomeButton_clicked();

    void on_quitButton_clicked();

    void on_Home_CallButton_clicked();

    void on_Mine_uiButton_clicked();

    void on_Mine_refreshButton_clicked();

    void on_Mine_quitButton_clicked();

    void on_Mine_upButton_clicked();

private:

    Ui::tenantwindow *ui;
    QSqlTableModel *model_home;



};

#endif // TENANTWINDOW_H
