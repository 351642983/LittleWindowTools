
#include "qizi.h"

qizi::qizi(int ty)
{
    type=ty;
    string1="ËÍ¸ø³¬¿É°®µÄÅíÉÙÄê";
    //if(ty==0)
    {
        g_num=(g_start1)%string1.length();
        g_start1++;
    }
}
qizi::~qizi()
{

}
int qizi::g_start1=0;
bool qizi::g_run=false;
QRectF qizi::boundingRect() const
{

    return QRectF(LENGTH/LTIMES/-2,HIGH/HTIMES/-2,LENGTH/LTIMES,HIGH/HTIMES);
}
QPainterPath qizi::shape() const
{
    QPainterPath sp;
    sp.addRect(LENGTH/LTIMES/-4,HIGH/HTIMES/-4,LENGTH/LTIMES/2,HIGH/HTIMES/2);
    return sp;
}


void qizi::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(type==0)
    {
        painter->setPen(QPen(Qt::red,2));
        if(!g_run)
        {
            painter->drawLine(QPointF(LENGTH/LTIMES/-4,HIGH/HTIMES/-4),QPointF(LENGTH/LTIMES/4,HIGH/HTIMES/4));
            painter->drawLine(QPointF(LENGTH/LTIMES/-4,HIGH/HTIMES/4),QPointF(LENGTH/LTIMES/4,HIGH/HTIMES/-4));
        }
        else
        {
            QFont font("Î¢ÈíÑÅºÚ",100,QFont::AbsoluteSpacing,false);
            painter->setFont(font);
            painter->drawText(-60,50,string1.at(g_num));
        }

    }
    else
    {
        painter->setPen(QPen(Qt::white,1));
        if(!g_run)
        {
            QRectF rectangle(LENGTH/LTIMES/-4,HIGH/HTIMES/-4,LENGTH/LTIMES/2,HIGH/HTIMES/2);
            int startAngle=0*16;
            int spanAngle=360*16;
            painter->drawArc(rectangle, startAngle, spanAngle);
        }
        else
        {
            QFont font("Î¢ÈíÑÅºÚ",100,QFont::AbsoluteSpacing,false);
            painter->setFont(font);
            painter->drawText(-60,50,string1.at(g_num));
        }
    }


}
