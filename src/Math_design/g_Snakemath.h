#ifndef G_SNAKEMATH_H
#define G_SNAKEMATH_H
#include <QGraphicsObject>
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>

enum DIRT
{
    NOMOVE,
    UPMOVE,
    RIGHTMOVE,
    DOWNMOVE,
    LEFTMOVE
};

class g_snakemath:public QGraphicsObject
{


public:
    g_snakemath(int,QGraphicsObject *parent=0);
    QPointF changeXY(int,int);
    QRectF boundingRect() const;
    int g_eatnum,g_snum;
    QPointF head,food;
    DIRT currentDirt;


    QPainterPath shape();
    void restore_food();
    bool eatFoodCheck();
    void addBody(qreal x,qreal y);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void nextCarry();
    bool isoutgame();




private:
    int type;
    QList<QPointF> tail;




};

#endif // G_SNAKEMATH_H
