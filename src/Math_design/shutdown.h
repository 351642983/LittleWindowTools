#ifndef SHUTDOWN_H
#define SHUTDOWN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTimeEdit>
#include <QRegExpValidator>
#include <QString>
#include <QDateTime>
#include <QSystemTrayIcon>

#include "TimeThread.h"
#include "SusWidget.h"
#include "SystemTimeThread.h"

class ShutDown : public QDialog
{
    Q_OBJECT

public:
    ShutDown(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~ShutDown();

private:
    QGroupBox *chooseGroup;
    QRadioButton *countDownRadio;
    QRadioButton *timerRadio;
    QTimeEdit *countEdit;
    QTimeEdit *timeEdit;
    QLabel *remainText;
    QLineEdit *remainTimeLine;
    QLineEdit *systemTimeLine;
    QLabel *currentTimeText;
    QPushButton *startButton;
    QPushButton *exitButton;

    QAction *susAction;
    QAction *restoreAction;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QTime    m_time;
    bool       m_start;
    bool       m_countDown;
    bool       m_mini;
    bool       m_suspend;
    TimeThread  m_timeThread;
    SystemTimeThread  m_systemTimeThread;
    SusWidget *swidget;

//protected:
//	void closeEvent(QCloseEvent *event);

public:
    void createActions();
    void createTrayIcon();
    void SetSusTime(const QTime &time, int type);

signals:
    void RemainTimeChanged(const QTime &time, int type);

private slots:
    void  CountTimeChanged(const QTime &time);
    void  ClickedCountDownRadio();
    void  doTimeChanged(const QTime &time);
    void  ClickedTimerRadio();
    void  ClickedStartButton();
    void  SetRemainTime(const QTime &time, int type);
    void  SetCurrentTime(const QTime &time);
    void  ShowDialog();
    void  ClikedTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void  ShowSusWidget();
    void  HideOrExit();
};

#endif // SHUTDOWN_H
