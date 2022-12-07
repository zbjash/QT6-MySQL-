#ifndef TENANT_UPDATE_H
#define TENANT_UPDATE_H

#include <QWidget>

namespace Ui {
class tenant_update;
}

class tenant_update : public QWidget
{
    Q_OBJECT

public:
    explicit tenant_update(QWidget *parent = nullptr);
    ~tenant_update();

private slots:
    void on_tu_commitButton_clicked();

private:
    Ui::tenant_update *ui;
};

#endif // TENANT_UPDATE_H
