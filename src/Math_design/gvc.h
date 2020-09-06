#ifndef GVC_H
#define GVC_H

#include "handle.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QMessageBox>
class gvc:public QGraphicsView
{
    Q_OBJECT
public:
    gvc(QGraphicsScene *A,QWidget *B=0):QGraphicsView(A,B){}
    ~gvc(){}
    int x;
    int y;
protected:
    void mousePressEvent(QMouseEvent *event);
signals:
    void changeAble();

};

#endif // GVC_H
