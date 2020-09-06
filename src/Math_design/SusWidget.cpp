
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
    font.setFamily("幼圆");
    font.setBold(true);
    font.setWeight(75);
    timeEdit->setFont(font);
    timeEdit->setAlignment(Qt::AlignCenter);
    timeEdit->setText(tr("统计关机时间"));
    timeEdit->setReadOnly(true);
}

SusWidget::~SusWidget()
{

}


void SusWidget::SetRemainTime(const QTime &time, int type)
{
    if ( type == REMAIN_TIME )
    {
        timeEdit->setText( tr("离关机还有：") + time.toString(tr("hh时mm分ss秒")) );
    }
    if ( type == TO_SHUTDOWN )
    {
        timeEdit->setText( tr("正在关机") );
    }
    if ( type == SHUTDOWN_ERROR )
    {
        timeEdit->setText( tr("关机失败") );
    }
}

