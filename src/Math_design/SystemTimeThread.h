#ifndef SYSTEMTIMETHREAD_H
#define SYSTEMTIMETHREAD_H

#include <QDateTime>
#include <QThread>

class SystemTimeThread : public QThread
{
    Q_OBJECT

public:
    QTime m_time;

public:
    SystemTimeThread(QObject *parent = 0);

signals:
    void CurrentTimeChanged(const QTime &time);

protected:
    void run();
};

#endif
