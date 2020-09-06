#include "BarWidget.h"
#include <QMessageBox>
BarWidget::BarWidget(QWidget *parent):
    QWidget(parent)
{
    tray=new QSystemTrayIcon;
    g_tixin=true;
}
BarWidget::~BarWidget()
{

}

void BarWidget::closeEvent(QCloseEvent *event)
{
    if(g_tixin)
    {
        QMessageBox::StandardButton rb = QMessageBox::question(NULL, "����", "�Ƿ��˳�����,���Yes��ť�˳����򣬵��No��ť���ص�����", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::No)
        {
            event->ignore();
            tray->show();
            tray->showMessage("С���߼���","�Ѿ����ص����̣��һ�ͼ������˳�����");
            hide();

        }
        else
        {
            tray->hide();
        }
    }
}
void BarWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Q  &&  event->modifiers() == (Qt::AltModifier | Qt::ControlModifier))
        emit pressA();
}
