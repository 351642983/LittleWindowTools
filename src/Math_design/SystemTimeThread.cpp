#include "SystemTimeThread.h"

SystemTimeThread::SystemTimeThread(QObject *parent) :  QThread(parent)
{
    m_time = m_time.currentTime();
}

void SystemTimeThread::run()
{
    while(1)
    {
        msleep(500);
        m_time = m_time.currentTime();
        emit CurrentTimeChanged(m_time);
    }
}
