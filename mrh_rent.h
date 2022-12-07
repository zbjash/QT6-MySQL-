#ifndef MRH_RENT_H
#define MRH_RENT_H

#include <QWidget>

namespace Ui {
class mrh_rent;
}

class mrh_rent : public QWidget
{
    Q_OBJECT

public:
    explicit mrh_rent(QWidget *parent = nullptr);
    ~mrh_rent();

private slots:
    void on_mrh_rent_cancelButton_clicked();

    void on_mrh_rent_commitButton_clicked();


    void on_mrh_rent_infoTextEdit_textChanged();

private:
    Ui::mrh_rent *ui;
};

#endif // MRH_RENT_H
