#include "g_mgmath.h"
#include <QCoreApplication>
#include <QEventLoop>



qreal s[5][2]=
{
    {0.0,0.0},
    {0.0,-SPEEDSET},
    {SPEEDSET,0.0},
    {0.0,SPEEDSET},
    {-SPEEDSET,0.0}

};

qreal bc[5][2]=
{
    {0.0,0.0},
    {0.0,BACKSPEEDSET},
    {-BACKSPEEDSET,0.0},
    {0.0,-BACKSPEEDSET},
    {BACKSPEEDSET,0.0}

};


g_mgmath::g_mgmath(int type)
{
    currentDirt=NOMOVE;
    pos=QPointF(LENTH/2,LENTH/2);
    g_type=type;
    checkp=QPoint(1,1);
    turnp<<checkp;
    g_check[0][0]=true;
    haveDirt=new QList<TheInfo>();
    theFinalPoint=new QPoint();
    haveCheckp=new QPoint();
    haveTurnp=new QList<QPoint>();


}
g_mgmath::~g_mgmath()
{

}

bool g_mgmath::isrunover()
{
    for(int i=0;i<LENNUM;i++)
    {
        for(int j=0;j<HEINUM;j++)
        {
            if(!g_check[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
QList<int> g_mgmath::thePointdirt(int x,int y)
{
    QList<int> dirtnum;
    if(y>=2)
    {
        if(!g_check[x-1][y-2])
            dirtnum<<1;
    }
    if(x<LENNUM)
    {
        if(!g_check[x][y-1])
            dirtnum<<2;
    }
    if(y<HEINUM)
    {
        if(!g_check[x-1][y])
            dirtnum<<3;
    }
    if(x>=2)
    {
        if(!g_check[x-2][y-1])
            dirtnum<<4;
    }
    if(dirtnum.isEmpty())
    {
        dirtnum<<0;
    }
    return dirtnum;
}

int g_mgmath::random_num(int x,int y)
{
    static bool g_i=false;
    static QTime tlast=QTime::currentTime();
    if(!g_i)
    {
        qsrand((uint)QTime(0,0,0,0).msecsTo(tlast));
        g_i=true;
    }
    else if(QTime(0,0,0,0).msecsTo(tlast)!=QTime(0,0,0,0).msecsTo(QTime::currentTime()))
    {
        tlast=QTime::currentTime();
        qsrand((uint)QTime(0,0,0,0).msecsTo(tlast));
    }
    return ((qrand()*qrand())%(y-x+1)+x);
}

void g_mgmath::nextCarry()
{

    if(g_type==1&&currentDirt!=NOMOVE)
    {
        pos=QPointF(pos.x()+s[currentDirt][0],pos.y()+s[currentDirt][1]);
        update();

    }
}


void g_mgmath::backCarry()
{
//    pos=QPointF(pos.x()+bc[currentDirt][0]*10,pos.y()+bc[currentDirt][1]*10);
    if(lastDirt!=NOMOVE)
    {
        if(lastDirt==UPMOVE)
            pos=QPointF(pos.x(),(int)(pos.y()/LENTH)*LENTH+LENTH/2);
        else if(lastDirt==RIGHTMOVE)
            pos=QPointF((int)(pos.x()/LENTH)*LENTH+LENTH/2,pos.y());
        else if(lastDirt==LEFTMOVE)
            pos=QPointF((int)(pos.x()/LENTH)*LENTH+LENTH/2,pos.y());
        else if(lastDirt==DOWNMOVE)
            pos=QPointF(pos.x(),(int)(pos.y()/LENTH)*LENTH+LENTH/2);

    }
    update();
}

void g_mgmath::addLine(qreal x,qreal y ,qreal z,qreal w)
{
    onep.setX(x);
    onep.setY(y);
    anp.setX(z);
    anp.setY(w);
    update();
}

QRectF g_mgmath::boundingRect() const
{

    return QRectF(0,0,800,600);
}
QPainterPath g_mgmath::shape() const
{
    QPainterPath pp;

    if(g_type==2)
    {
        pp.addRect(QRectF(onep,anp));
        return pp;
    }
    else if(g_type==1)
    {
        pp.addRect(QRectF(pos.x()-2.5,pos.y()-2.5,5,5));
        return pp;
    }
    return pp;

}


void g_mgmath::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    if(g_type==1)
    {
        if(pos.x()<-5||pos.y()<-5||pos.x()>805||pos.y()>605)
            pos=QPointF(LENTH/2,LENTH/2);
        painter->setPen(Qt::green);
        painter->setBrush(Qt::red);
        painter->drawEllipse(mapFromScene(pos.x()-2.5,pos.y()-2.5),5,5);


    }
    else if(g_type==2)
    {
        painter->setPen(Qt::black);
        painter->setBrush(Qt::red);
        painter->drawLine(mapFromScene(onep),mapFromScene(anp));
    }

    painter->restore();
}
