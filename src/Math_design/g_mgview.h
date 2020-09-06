#ifndef G_MGVIEW_H
#define G_MGVIEW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QCoreApplication>
#include <QTextEdit>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QLCDNumber>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QInputDialog>
#include <QMessageBox>
#include <QProcess>
#include "g_mgmath.h"
#include "gameWidget.h"
#include "handoption.h"
#include "ranks.h"
#include "widget.h"


class g_mgview:public QWidget
{
    Q_OBJECT

public:
    g_mgview(QWidget *parent=0);
    ~g_mgview();


private:
    bool g_showcr;
    QPushButton *button[3];
    QGraphicsScene *g_scene;
    QGraphicsView *g_view;
    gamewidget *gw;
    QTextEdit *te;
    QLabel *word[2];
    QLCDNumber *lcdnumber;
    QTimer *timer;
    g_mgmath *gm/*,*gl[LENNUM][HEINUM-1],*gk[HEINUM][LENNUM-1],*wc[4]*/;
    QList<QPainterPath> alpath,acheckp;
    QPainterPath returnLine(int,int,int);
    QPainterPath theend,thefram;
    int g_thepathnum;
    QList<QPoint> thepath;
    QList<QPoint> *Tempturn;
    QList<QPoint> *haveUsed;
    QPoint *lastPoint;
    int changep(int,int,int);
    int timeRun;
    bool isCotain();
    void createmg();
    void nextStep();
    bool inendPoint();
    bool showpath;
    void drawlTor(QPoint,QPoint,QPen);
    void showFinalPath();
    void findNextStep();
    bool containTempTurn(int x,int y);
    QPoint returnDirtPoint(int,int,int);
    bool containHaveUsed(int x,int y)
    {
        foreach(QPoint it,*haveUsed)
        {
            if(it.x()==x&&it.y()==y)
            {
                return true;
            }
        }
        return false;
    }


private slots:
    void recreate_mg();
    void closePost();
    void openoption();
    void refresh();


protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);


};

#endif // G_MGVIEW_H
