#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include<QShortcut>


QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE
//QString id;


class login : public QWidget
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_l_editButton_clicked();

    void on_l_cancelButton_clicked();

    void on_findbackButton_clicked();

    void on_l_loginButton_clicked();




private:
    Ui::login *ui;
    QShortcut *enter=new QShortcut(QKeySequence(Qt::Key_Return),this); //快捷键
    QShortcut *lenter=new QShortcut(QKeySequence(Qt::Key_Enter),this); //快捷键
};
#endif // LOGIN_H
