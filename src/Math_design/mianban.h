#ifndef MIANBAN_H
#define MIANBAN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

namespace Ui {
class mianban;
}

class mianban : public QWidget
{
    Q_OBJECT
    
public:
    explicit mianban(QWidget *parent = 0);
    ~mianban();
    QStringList zhanghao;
    QSqlDatabase db;
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::mianban *ui;
};

#endif // MIANBAN_H
