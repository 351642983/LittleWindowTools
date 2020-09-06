#ifndef YYSTASK_H
#define YYSTASK_H
#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QFile>
#include <QTextEdit>
#include "chinesechange.h"
#include <QDir>
#include <QTextCodec>
class YYSTask:public QWidget{
    Q_OBJECT
public:
    YYSTask(QWidget *parent=0);
    ~YYSTask();
private:
    QListWidget *searchResult;
    QLineEdit *le;
    QPushButton *pb;
    QTextEdit *te;
    QLabel *l1,*l2,*l3;
    QList<QString> info; //储存所有怪物分布信息
    chinesechange *transform;

    QList<QString> getListInfo();
    int searchPosition(QString);
    QString getLetters(QString);
    void showTheInfo(int num);
private slots:
    void changeListInfo(QString);
    void selectListWidgetItem();
    void selectItem(QListWidgetItem *);




};

#endif // YYSTASK_H
