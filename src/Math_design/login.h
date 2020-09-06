#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QValidator>
#include <QRegExpValidator>
#include <QDir>
#include <QFile>
#include <QTextCodec>
#include <QTextStream>
#include <QTimer>
#include "zcwidget.h"


namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT
    
public:
    explicit login(QWidget *parent = 0);
    ~login();
    QSqlDatabase db;
    QStringList zhanghao;
    bool g_an;


    
public slots:
    void on_pushButton_clicked();
    void zhuce();
    void updateInfo();

    void on_pushButton_2_clicked();

private:
    Ui::login *ui;
    QTimer *time;
};

#endif // LOGIN_H
