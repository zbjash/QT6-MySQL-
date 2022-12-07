#ifndef MRH_CANCELRENT_H
#define MRH_CANCELRENT_H

#include <QWidget>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
namespace Ui {
class mrh_cancelrent;
}

class mrh_cancelrent : public QWidget
{
    Q_OBJECT

public:
    explicit mrh_cancelrent(QWidget *parent = nullptr);
    ~mrh_cancelrent();

private slots:
    void on_mrh_cancelrent_cancelButton_clicked();

    void on_mrh_cancelrent_commitButton_clicked();

private:
    Ui::mrh_cancelrent *ui;



};

#endif // MRH_CANCELRENT_H
