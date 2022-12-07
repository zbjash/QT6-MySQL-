#ifndef FINDBACK_H
#define FINDBACK_H

#include <QWidget>

namespace Ui {
class findback;
}

class findback : public QWidget
{
    Q_OBJECT

public:
    explicit findback(QWidget *parent = nullptr);
    ~findback();

private slots:
    void on_fb_fbButton_clicked();

private:
    Ui::findback *ui;
       int mode;
};

#endif // FINDBACK_H
