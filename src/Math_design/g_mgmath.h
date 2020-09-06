#ifndef G_MGMATH_H
#define G_MGMATH_H

#include <QGraphicsItem>
#include <QTime>
#include <QPainter>
#include "handoption.h"
#include <map>

enum DIRT
{
    NOMOVE,
    UPMOVE,
    RIGHTMOVE,
    DOWNMOVE,
    LEFTMOVE
};

#define LENNUM 800/(int)LENTH
#define HEINUM 600/(int)LENTH
class TheInfo
{
    int x,y;
public:
    TheInfo()
    {
        numList=new QList<int>();
    }
    QList<int> *numList;

    int getX()
    {
        return x;
    }
    void setX(int x)
    {
        this->x=x;
    }
    void setY(int y)
    {
        this->y=y;
    }
    void setXY(int x,int y)
    {
        this->x=x;
        this->y=y;
    }
    int getY()
    {
        return y;
    }
    int at(int i)
    {
        return numList->at(i);
    }
    void add(int info)
    {
        numList->append(info);
    }
    void remove(int i)
    {
        numList->removeAt(i);
    }
    QList<int> *getList()
    {
        return numList;
    }
    void removeDirt(int dirt)
    {
        for(int i=0;i<numList->size();i++)
        {
            if(numList->at(i)==dirt)
            {
                numList->removeAt(i);
                break;
            }
        }
    }


};

class g_mgmath:public QGraphicsItem
{
public:
    g_mgmath(int);
    ~g_mgmath();
    int random_num(int,int);
    DIRT currentDirt;
    DIRT lastDirt;
    void nextCarry();
    void backCarry();
    QPointF pos,onep,anp;
    int g_type;
    void addLine(qreal,qreal,qreal,qreal);
    QList<QPoint> turnp;
    bool g_check[LENNUM][HEINUM];
    QPoint checkp;
    bool isrunover();
    QList<int> thePointdirt(int x,int y);

    QList<int> *getHaveDirt(int x,int y)
    {

        foreach(TheInfo it,*haveDirt)
        {
            if(it.getX()==x&&it.getY()==y)
            {
                return it.getList();
            }
        }
        return NULL;
    }
    void InsetHaveDirt(int x,int y,int dirt)
    {
        foreach(TheInfo it,*haveDirt)
        {
            if(it.getX()==x&&it.getY()==y)
            {
                if(!it.getList()->contains(dirt))
                    it.add(dirt);
                break;
            }
        }
    }
    int getHaveDiretion(int x,int y)
    {
        int z=0;
        foreach(TheInfo it,*haveDirt)
        {
            if(it.getX()==x&&it.getY()==y)
            {
                if(it.getList()->size()==0)
                    return 0;
                else
                {
                    int k=0;

                    foreach(int num,*it.getList())
                    {
                        if(num==1)
                        {
                            if(getHaveDirt(x,y-1)->size()>k)
                            {
                                k=getHaveDirt(x,y-1)->size();
                                z=num;
                            }
                        }
                        else if(num==2)
                        {
                            if(getHaveDirt(x+1,y)->size()>k)
                            {
                                k=getHaveDirt(x+1,y)->size();
                                z=num;
                            }
                        }
                        else if(num==3)
                        {
                            if(getHaveDirt(x,y+1)->size()>k)
                            {
                                k=getHaveDirt(x,y+1)->size();
                                z=num;
                            }
                        }
                        else if(num==4)
                        {
                            if(getHaveDirt(x-1,y)->size()>k)
                            {
                                k=getHaveDirt(x-1,y)->size();
                                z=num;
                            }
                        }
                    }
                    break;
                }
                break;

            }
        }
        return z;
    }
    void setHaveCheckp(int z)
    {
        if(z==1)
        {
            haveCheckp->setY(haveCheckp->y()-1);
        }
        else if(z==2)
        {
            haveCheckp->setX(haveCheckp->x()+1);
        }
        else if(z==3)
        {
            haveCheckp->setY(haveCheckp->y()+1);
        }
        else if(z==4)
        {
            haveCheckp->setX(haveCheckp->x()-1);
        }
    }


    void addHaveXY(int x,int y)
    {
        TheInfo *info=new TheInfo();
        info->setXY(x,y);
        haveDirt->append(*info);
    }
    bool isHaveExist(int x,int y)
    {
        foreach(TheInfo it,*haveDirt)
        {
            if(it.getX()==x&&it.getY()==y)
            {
                return true;
            }
        }
        return false;
    }
    void removeHaveDirt(int x,int y,int dirt)
    {
        foreach(TheInfo it,*haveDirt)
        {
            if(it.getX()==x&&it.getY()==y)
            {
                it.removeDirt(dirt);
//                if(it.getList()->size()==0)
//                    haveDirt->removeAt(getHaveXY(x,y));
                break;
            }
        }
    }

    int getHaveXY(int x,int y)
    {
        for(int i=0;i<haveDirt->size();i++)
        {
            TheInfo it=haveDirt->at(i);
            if(it.getX()==x&&it.getY()==y)
            {
                return i;
            }
        }
        return -1;
    }

    void setTheFinalPoint(int x,int y)
    {
        theFinalPoint->setX(x);
        theFinalPoint->setY(y);
    }
    QPoint *getFinalPoint()
    {
        return theFinalPoint;
    }
    QPoint *haveCheckp;
    QList<QPoint> *haveTurnp;

    QList<TheInfo> *getHaveDirtList()
    {
        return haveDirt;
    }
    bool containHaveTurnp(int x,int y)
    {
        foreach(QPoint it,*haveTurnp)
        {
            if(it.rx()==x&&it.ry()==y)
            {
                return true;
            }
        }
        return false;
    }
    TheInfo getHaveDirtAt(int i)
    {
        return haveDirt->at(i);
    }




private:
    QList<TheInfo> *haveDirt;//储存变量信息

    QPoint *theFinalPoint;


//    void InsetHaveDirt(int x,int y,int dirt);

    //QGraphicsItem *g_item;

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
};



#endif // G_MGMATH_H
