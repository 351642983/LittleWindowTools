
#include "suswidget.h"

SusWidget::SusWidget(QWidget *parent, Qt::WFlags flags)
: QWidget(parent, flags)
{
    setFixedSize(170, 20);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    QRect   screenSize;
    screenSize = QApplication::desktop()->rect();
    setGeometry(screenSize.width()-180, screenSize.height()-70, 170, 20);
    timeEdit = new QLineEdit(this);
    timeEdit->setGeometry(rect());

    QFont font;
    font.setFamily("��Բ");
    font.setBold(true);
    font.setWeight(75);
    timeEdit->setFont(font);
    timeEdit->setAlignment(Qt::AlignCenter);
    timeEdit->setText(tr("ͳ�ƹػ�ʱ��"));
    timeEdit->setReadOnly(true);
}

SusWidget::~SusWidget()
{

}


void SusWidget::SetRemainTime(const QTime &time, int type)
{
    if ( type == REMAIN_TIME )
    {
        timeEdit->setText( tr("��ػ����У�") + time.toString(tr("hhʱmm��ss��")) );
    }
    if ( type == TO_SHUTDOWN )
    {
        timeEdit->setText( tr("���ڹػ�") );
    }
    if ( type == SHUTDOWN_ERROR )
    {
        timeEdit->setText( tr("�ػ�ʧ��") );
    }
}

