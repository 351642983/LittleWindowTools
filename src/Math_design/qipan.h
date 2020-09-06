#ifndef QIPAN_H
#define QIPAN_H

#include <QWidget>
#include <QGraphicsScene>
#include "gvc.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QEventLoop>
#include <QTime>
#include <QCoreApplication>

class pWidget : public QWidget
{
    Q_OBJECT

public:
    pWidget(QWidget *parent = 0);
    ~pWidget();



private:
    QPointF getPoint(int ,int );
    QGraphicsScene *g_scene;
    void getXY(int,int,int &x,int &y);
    gvc *g_view;
    QPushButton *start;
    QLabel *label_1,*label_2,*label_3;
    QComboBox *cbox_1,*cbox_2,*cbox_3;
    void addqizi(int,int,int);
    int juzheng[LTIMES][HTIMES];
    int random_num(int x,int y)
    {
        g_ok=true;
        static int start=QTime(0,0,0,0).msecsTo( QTime::currentTime());
        static bool g_test=false;
        int stop=QTime(0,0,0,0).msecsTo( QTime::currentTime());
        if(!g_test)
        {
            qsrand(start);
            g_test=true;
        }
        else if(stop-start>=1)
        {
            start=QTime(0,0,0,0).msecsTo( QTime::currentTime());
            qsrand(start);
        }
        g_ok=false;
        return (qrand()%(y-x+1)+x);
    }
    void setSuitableAI(int &x,int &y);
    void getcXY(int &x,int &y);
    void diannaoplay();
    bool g_start;
    void gameover();
    bool empty();
    int checkWin();
    int g_score[2];
    bool g_ok;
private slots:
    void gamestart();
    void clickg();
    int returnInt();



};

#endif // QIPAN_H
