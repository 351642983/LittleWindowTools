#ifndef RANKS_H
#define RANKS_H

#include <QDialog>
#include <QListWidget>
#include <QFile>
#include <QDir>
#include <QPushButton>
#include <QLabel>


class ranks:public QDialog
{
    Q_OBJECT
public:
    ranks(QWidget *parent=0);
    ~ranks();
    void showrank(int);
    int insertrank(const char*,int,int);

private: 
    QListWidget *wlist[3];
    QPushButton *button[3];
    QLabel *info[3];
    int g_type;

private slots:
    void change_allselect(QListWidgetItem*);
    void del_allline();
    void del_line();

};

#endif // RANKS_H
