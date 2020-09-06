#ifndef TIMETHREAD_H
#define TIMETHREAD_H

#include <QDateTime>
#include <QThread>
#include <Windows.h>

#define   REMAIN_TIME            0
#define   TO_SHUTDOWN         1
#define   SHUTDOWN_ERROR  2

class TimeThread : public QThread
{
    Q_OBJECT

public:
    QTime m_time;
    bool m_start;

public:
    TimeThread(QObject *parent = 0);
    void SetCountTime(QTime time, bool start);
    bool MySystemShutdown();

signals:
    void RemainTimeChanged(const QTime &time, int type);

protected:
    void run();
};

#endif
