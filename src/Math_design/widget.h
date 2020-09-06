//对游戏算法汇总的处理头文件,用以各类执行及其页面的展示
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QTextEdit>
#include <QMenuBar>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QKeyEvent>
#include "BarWidget.h"
//定义游戏类型的数目


class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    //用于储存选择的游戏模式的变量
    int type;
    QLabel *Ll;
//    QLabel *tixin;
    //建立一个联表,用于开始界面时选择打开某一类型的游戏游戏
    QListWidget *Lw;
    QPushButton *B_select;
    QPushButton *B_about;
    QTextEdit *textedit;
    //定义一个主窗口界面,用以显示各类东西
    BarWidget *mainwindow;
    //QMenuBar *bar;
    void del_kongjian(int);
    QSystemTrayIcon *tray;
//    QPushButton *dl;
    QStringList thelist;
    QTimer *starttime;
//protected:
//    void keyPressEvent(QKeyEvent *);



private slots:
    void showSay();
    void showType();
    void showabout();
    void startgame();
    void textshow(QListWidgetItem*);
    void showHide(QSystemTrayIcon::ActivationReason);
    void closePro();
    void denglu();
    void checkzhanghao();
    void relate();  //连接窗口和截屏功能：弃用
    void checkFail();



};

#endif // WIDGET_H
