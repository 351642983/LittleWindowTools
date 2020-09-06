#ifndef QIZI_H
#define QIZI_H
#include <QGraphicsItem>
#include <QPainter>
#include "handle.h"

class qizi:public QGraphicsItem
{
public:
    qizi(int);
    ~qizi();
    static int g_start1;
    static bool g_run;
private:
    //QGraphicsItem *g_item;

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    int type;
    int g_num;
    QString string1;
};

#endif // QIZI_H

