#ifndef SQLHANDLE_H
#define SQLHANDLE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>


namespace Ui {
class sqlhandle;
}

class sqlhandle : public QWidget
{
    Q_OBJECT
    
public:
    explicit sqlhandle(QWidget *parent = 0);
    ~sqlhandle();
    QSqlDatabase db;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::sqlhandle *ui;
};

#endif // SQLHANDLE_H
