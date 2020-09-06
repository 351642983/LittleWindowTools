#include "shutdown.h"
#include <QtGui>

ShutDown::ShutDown(QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags)
{
    if (objectName().isEmpty())  setObjectName(QString::fromUtf8("ShutDown"));
    setFixedSize(264, 261);

    setWindowFlags(Qt::WindowMinimizeButtonHint);

    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8("Resources/shutdown.png")), QIcon::Normal, QIcon::Off);
    setWindowIcon(icon);

    createActions();
    createTrayIcon();

    chooseGroup = new QGroupBox(this);
    chooseGroup->setGeometry(QRect(20, 10, 221, 191));
    chooseGroup->setAlignment(Qt::AlignCenter);
    countDownRadio = new QRadioButton(chooseGroup);
    countDownRadio->setGeometry(QRect(20, 30, 101, 21));
    timerRadio = new QRadioButton(chooseGroup);
    timerRadio->setGeometry(QRect(20, 70, 101, 21));
    countEdit = new QTimeEdit(chooseGroup);
    countEdit->setGeometry(QRect(120, 30, 81, 22));
    countEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    countEdit->setTime(QTime(1, 0, 0));
    timeEdit = new QTimeEdit(chooseGroup);
    timeEdit->setGeometry(QRect(120, 70, 81, 22));
    timeEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    remainText = new QLabel(chooseGroup);
    remainText->setGeometry(QRect(20, 110, 81, 21));
    remainTimeLine = new QLineEdit(chooseGroup);
    remainTimeLine->setGeometry(QRect(110, 110, 91, 20));
    remainTimeLine->setAlignment(Qt::AlignCenter);
    remainTimeLine->setReadOnly(true);
    systemTimeLine = new QLineEdit(chooseGroup);
    systemTimeLine->setGeometry(QRect(110, 150, 91, 20));
    systemTimeLine->setAlignment(Qt::AlignCenter);
    systemTimeLine->setReadOnly(true);
    currentTimeText = new QLabel(chooseGroup);
    currentTimeText->setGeometry(QRect(20, 150, 81, 21));
    startButton = new QPushButton(this);
    startButton->setGeometry(QRect(30, 220, 101, 23));
    exitButton = new QPushButton(this);
    exitButton->setGeometry(QRect(140, 220, 91, 23));

    countDownRadio->setChecked(true);
    timerRadio->setChecked(false);
    m_time = countEdit->time();
    remainTimeLine->setText(m_time.toString(tr("hh时mm分ss秒")));
    m_start = false;
    m_countDown = true;
    m_mini = false;
    m_suspend = true;

    connect(&m_timeThread, SIGNAL(RemainTimeChanged(const QTime &, int)), this, SLOT(SetRemainTime(const QTime &, int)));
    connect(&m_systemTimeThread, SIGNAL(CurrentTimeChanged(const QTime &)), this, SLOT(SetCurrentTime(const QTime &)));
    m_systemTimeThread.start();
    swidget = new SusWidget(0);

    connect(exitButton, SIGNAL(clicked()), this, SLOT(HideOrExit()));    //reject()
    connect(countEdit, SIGNAL(timeChanged(const QTime &)), this, SLOT(CountTimeChanged(const QTime &)));
    connect(countDownRadio, SIGNAL(clicked()), this, SLOT(ClickedCountDownRadio()));
    connect(timeEdit, SIGNAL(timeChanged(const QTime &)), this, SLOT(doTimeChanged(const QTime &)));
    connect(timerRadio, SIGNAL(clicked()), this, SLOT(ClickedTimerRadio()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(ClickedStartButton()));
    connect(this, SIGNAL(RemainTimeChanged(const QTime &, int)), swidget, SLOT(SetRemainTime(const QTime &, int)));

    chooseGroup->setTitle("关机菜单");
    countDownRadio->setText("倒计时关机");
    timerRadio->setText("设定关机时间");
    remainText->setText("剩余时间");
    currentTimeText->setText("当前时间");
    startButton->setText("开始计时");
    exitButton->setText("隐藏或关闭");
}

ShutDown::~ShutDown()
{
    m_systemTimeThread.terminate();
    m_systemTimeThread.wait();
}



void  ShutDown::HideOrExit()
{
    int choose = QMessageBox::question(this, tr("最小化到托盘或退出程序"),	tr("温情提示：\n      是否将程序最小化到托盘？最小化请点击Yes，退出程序请点击No。\n最小化后如需退出程序，请在托盘图标上点击右键，选择退出！") ,
                                             QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if( choose == QMessageBox::Yes )
    {
        hide();
        trayIcon->show();
        m_mini = true;
        if(m_start)  trayIcon->setToolTip(tr("定时关机程序正在运行"));
        else trayIcon->setToolTip(tr("定时关机程序已经停止运行"));
        m_suspend = true;
        if(m_start) swidget->show();
    }
    else
    {
        reject();
    }
}

void ShutDown::createActions()
{
    susAction = new QAction(tr("隐藏悬浮窗"), this);
    connect(susAction, SIGNAL(triggered()), this, SLOT(ShowSusWidget()));
    restoreAction = new QAction(tr("还原窗口"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(ShowDialog()));

    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8("Resources/sus.png")), QIcon::Normal, QIcon::Off);
    susAction->setIcon(icon);
    QIcon icon1;
    icon1.addPixmap(QPixmap(QString::fromUtf8("Resources/restore.png")), QIcon::Normal, QIcon::Off);
    restoreAction->setIcon(icon1);

}

void ShutDown::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(susAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8("Resources/shutdown.png")), QIcon::Normal, QIcon::Off);
    trayIcon->setIcon(icon);
    connect(trayIcon, SIGNAL(activated (QSystemTrayIcon::ActivationReason)), this, SLOT(ClikedTrayIcon(QSystemTrayIcon::ActivationReason)));
    susAction->setEnabled(false);
}

void  ShutDown::ShowDialog()
{
    showNormal();
    m_mini = false;
    trayIcon->hide();
    swidget->hide();
}

void  ShutDown::ShowSusWidget()
{
    if ( m_suspend )
    {
        swidget->hide();
        susAction->setText(tr("显示悬浮窗"));
        m_suspend = false;
    }
    else
    {
        swidget->show();
        susAction->setText(tr("隐藏悬浮窗"));
        m_suspend = true;
    }
}
void ShutDown::ClikedTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    if ( reason == QSystemTrayIcon::Trigger )  ShowDialog();
}

void ShutDown::CountTimeChanged(const QTime &time)
{
    countDownRadio->setChecked(true);
    timerRadio->setChecked(false);
    m_time = countEdit->time();
    remainTimeLine->setText( m_time.toString(tr("hh时mm分ss秒")) );
    m_countDown = true;
}

void ShutDown::ClickedCountDownRadio()
{
    QTime  time = countEdit->time();
    CountTimeChanged(time);
}

void ShutDown::doTimeChanged(const QTime &time)
{
    countDownRadio->setChecked(false);
    timerRadio->setChecked(true);
    QTime systemTime;
    systemTime = systemTime.currentTime();
    QTime setTime = timeEdit->time();
    m_time = setTime.addSecs(-systemTime.hour()*60*60-systemTime.minute()*60-systemTime.second());
    remainTimeLine->setText( m_time.toString(tr("hh时mm分ss秒")) );
    m_countDown = false;
}

void ShutDown::ClickedTimerRadio()
{
    QTime  time;
    time = timeEdit->time();
    doTimeChanged(time);
}

void ShutDown::ClickedStartButton()
{
    if ( m_countDown )
    {
        m_time = countEdit->time();
        remainTimeLine->setText( m_time.toString(tr("hh时mm分ss秒")) );
        remainTimeLine->setText( m_time.toString(tr("hh时mm分ss秒")) );
    }
    else
    {
        QTime systemTime;
        systemTime = systemTime.currentTime();
        QTime setTime = timeEdit->time();
        m_time = setTime.addSecs(-systemTime.hour()*60*60-systemTime.minute()*60-systemTime.second());
        remainTimeLine->setText( m_time.toString(tr("hh时mm分ss秒")) );
    }
    if ( m_start )
    {
        //停止计时
        countDownRadio->setEnabled (true);
        timerRadio->setEnabled(true);
        timeEdit->setEnabled(true);
        countEdit->setEnabled(true);
        susAction->setEnabled(false);
        startButton->setText(tr("开始定时关机"));
        m_start = false;
        m_timeThread.SetCountTime(m_time, m_start);
        m_timeThread.terminate();
        m_timeThread.wait();
    }
    else
    {
        //开始计时
        countDownRadio->setEnabled (false);
        timerRadio->setEnabled(false);
        timeEdit->setEnabled(false);
        countEdit->setEnabled(false);
        susAction->setEnabled(true);
        startButton->setText(tr("取消定时关机"));
        m_start = true;
        m_timeThread.SetCountTime(m_time, m_start);
        m_timeThread.start();
    }
}

void  ShutDown::SetSusTime(const QTime &time, int type)
{
    emit RemainTimeChanged(time, type);
    if ( type == SHUTDOWN_ERROR )
    {
        countDownRadio->setEnabled (true);
        timerRadio->setEnabled(true);
        timeEdit->setEnabled(true);
        countEdit->setEnabled(true);
        susAction->setEnabled(false);
        startButton->setText(tr("开始定时关机"));
        m_start = false;
    }
}

void ShutDown::SetRemainTime(const QTime &time, int type)
{
    if ( !m_mini )
    {
        if ( type == REMAIN_TIME )
        {
            remainTimeLine->setText( time.toString(tr("hh时mm分ss秒")) );
        }
        if ( type == TO_SHUTDOWN )
        {
            remainTimeLine->setText( tr("正在关机") );
        }
        if ( type == SHUTDOWN_ERROR )
        {
            remainTimeLine->setText( tr("关机失败") );
            countDownRadio->setEnabled (true);
            timerRadio->setEnabled(true);
            timeEdit->setEnabled(true);
            countEdit->setEnabled(true);
            susAction->setEnabled(false);
            startButton->setText(tr("开始定时关机"));
            m_start = false;
        }
    }
    if ( m_mini && m_suspend )
    {
        SetSusTime(time, type);
    }
}

void ShutDown::SetCurrentTime(const QTime &time)
{
    systemTimeLine->setText( time.toString(tr("hh时mm分ss秒")) );
}
