#include "gvc.h"
void gvc::mousePressEvent(QMouseEvent *event)
{
    x=event->x();
    y=event->y();
    emit changeAble();
}
//void gvc::changeAble()
//{
//    QMessageBox::about(NULL,QString("Ьсаб"),QString("%1 %2").arg(x).arg(y));
//}
