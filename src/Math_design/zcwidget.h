#ifndef ZCWIDGET_H
#define ZCWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>

namespace Ui {
class Zcwidget;
}

class Zcwidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Zcwidget(QWidget *parent = 0);
    ~Zcwidget();
    QStringList ook;
    QSqlDatabase db;
private slots:
    void on_pushButton_clicked();

private:
    Ui::Zcwidget *ui;
};

#endif // ZCWIDGET_H
