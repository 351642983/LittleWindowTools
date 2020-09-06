#include <QTime>
#include <QMessageBox>
#include "g_Snakemath.h"
#include "option.h"
#include "Gamerefresh.h"
#include "handoption.h"


int theCarry[5][2]=
{
    {0,0},
    {0,-1},
    {1,0},
    {0,1},
    {-1,0}
};


g_snakemath::g_snakemath(int ty,QGraphicsObject *parent)
    :QGraphicsObject(parent)
{
    setFlag(QGraphicsItem::ItemIsFocusable, true); //用来设置这个item可以获取焦点
    type=ty;
    currentDirt=NOMOVE;
    g_eatnum=0;
    g_snum=0;
}



QRectF g_snakemath::boundingRect() const
{
    //蛇实体运动的范围限制；
    return QRectF(0,0,800,600);
}

void g_snakemath::restore_food()
{

    bool g_check;
    do
    {
        QTime t;
        t= QTime::currentTime();
        qsrand(t.msec()+t.second()*1000);
        g_check=false;
        food=QPointF(abs(qrand())%(800/(int)LENTH)+1,abs(qrand())%(600/(int)LENTH)+1);
        foreach(QPointF thep,tail)
        {
            if(thep==food)
            {
                g_check=true;
            }
        }
    }while(g_check);
    update();
    //setPos(mapFromScene(changeXY(food.x(),food.y())));

}

bool g_snakemath::eatFoodCheck()
{

    if(food==head)
    {
        g_eatnum++;
        return true;
    }
    return false;
}

QPainterPath g_snakemath::shape()
{
    QPainterPath path;
    foreach(QPointF thep,tail)
    {
        path.addRect(QRectF(mapFromScene(changeXY((int)thep.x(),(int)thep.y())),QSizeF(LENTH,LENTH)));

    }
    return path;
}

void g_snakemath::addBody(qreal x, qreal y)
{
    if(g_snum==0)
    {
        head=QPointF(x,y);
        tail<<head;
    } 
    if(g_snum==1)
    {
        tail.insert(0,QPointF(head.x()-1,head.y()));

    }
     else if(g_snum>1)
        tail.insert(0,QPointF(2*tail.first().x()-tail.at(1).x(),2*tail.first().y()-tail.at(1).y()));
    g_snum++;
}
QPointF g_snakemath::changeXY(int x,int y)
{
    return QPointF((x-1)*LENTH,(y-1)*LENTH);
}
void g_snakemath::nextCarry()
{
    if(currentDirt!=NOMOVE)
    {

        head.rx()+=theCarry[currentDirt][0];
        head.ry()+=theCarry[currentDirt][1];
        tail.takeFirst();
        tail<<head;

        update();
        //setPos(mapFromScene(changeXY(head.x(),head.y())));
    }
}

bool g_snakemath::isoutgame()
{
    if(head.x()==800/LENTH+1||head.y()==600/LENTH+1||head.x()==0||head.y()==0)
        return true;
    int i=1;
    foreach(QPointF thep,tail)
    {
        if(i!=tail.count()&&thep==head)
            return true;
        i++;
    }
    return false;
}


void g_snakemath::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    if(type==1)
    {
        painter->fillPath(shape(), (Qt::GlobalColor)(g_snum%13+6));
        painter->setPen(Qt::red);
        painter->setBrush((Qt::GlobalColor)((g_snum+1)%13+6));
        painter->drawEllipse(mapFromScene(((food.x()-1)*LENTH+LENTH/2),((food.y()-1)*LENTH+LENTH/2)),LENTH/2,LENTH/2);
    }

    painter->restore();
}
