#ifndef MRH_ADDRECORD_H
#define MRH_ADDRECORD_H

#include <QWidget>

namespace Ui {
class mrh_addrecord;
}

class mrh_addrecord : public QWidget
{
    Q_OBJECT

public:
    explicit mrh_addrecord(QWidget *parent = nullptr);
    ~mrh_addrecord();

private slots:
    void on_mrd_addrecord_commitButton_clicked();

    void on_start_date_userDateChanged();

    void on_mrd_addrecord_cancelButton_clicked();

private:
    Ui::mrh_addrecord *ui;
};

#endif // MRH_ADDRECORD_H
