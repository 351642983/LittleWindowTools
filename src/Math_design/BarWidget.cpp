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
        QMessageBox::StandardButton rb = QMessageBox::question(NULL, "提醒", "是否退出程序,点击Yes按钮退出程序，点击No按钮隐藏到托盘", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::No)
        {
            event->ignore();
            tray->show();
            tray->showMessage("小工具集合","已经隐藏到托盘，右击图标可以退出程序");
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
