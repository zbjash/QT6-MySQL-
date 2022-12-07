#ifndef TENANT_UPASSWORD_H
#define TENANT_UPASSWORD_H

#include <QWidget>

namespace Ui {
class tenant_upassword;
}

class tenant_upassword : public QWidget
{
    Q_OBJECT

public:
    explicit tenant_upassword(QWidget *parent = nullptr);
    ~tenant_upassword();

private slots:
    void on_tup_commitButton_clicked();

    void on_tup_cancelButton_2_clicked();

private:
    Ui::tenant_upassword *ui;
};

#endif // TENANT_UPASSWORD_H
