//贪吃蛇界面实现的类头文件,使用QT自带的Graphics框架进行设计
#ifndef G_SNAKE_H
#define G_SNAKE_H

#include <QWidget>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QCoreApplication>
#include <QTimer>
#include <QTime>
#include <QKeyEvent>
#include <QLCDNumber>
#include <QLabel>
#include <QApplication>
#include <QDesktopWidget>
#include "Gamerefresh.h"
#include "gameWidget.h"



class g_snake:public QWidget
{
    Q_OBJECT

public:
    g_snake(QWidget *parent=0);
    ~g_snake();


private:
    int g_type;
    QPushButton *button[7];
    QGraphicsScene *g_scene;
    QGraphicsView *g_view;
    QTimer *timer;
    g_snakemath *snake;
    QLCDNumber *lcdnumber[3];
    QLabel *words[3];
    gamewidget *gw;
    QTime dieTime,onetime;
    int g_fps,g_knum;


    void create_rect();
    void release_new();



private slots:
    void postclose();
    void startgame();
    void setoption();
    void seerank();
    void refresh();
    void rets();
    void pause();
    void resume();
    void lcdrefresh();

protected:
    void keyPressEvent(QKeyEvent *);


};


#endif // G_SNAKE_H
