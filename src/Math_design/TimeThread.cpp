#include "TimeThread.h"
#define EWX_FORCEIFHUNG 0x00000010
TimeThread::TimeThread(QObject *parent) : QThread(parent)
{
    m_time = QTime(1, 0, 0);
    m_start = false;
}

void TimeThread::SetCountTime(QTime time, bool start)
{
    m_time = time;
    m_start = start;
}

void TimeThread::run()
{
    QTime  oldTime, newTime;
    oldTime.setHMS(QTime::currentTime().hour(), QTime::currentTime().minute(), QTime::currentTime().second(), 0);
    while(m_start)
    {
        msleep(250);
        newTime.setHMS(QTime::currentTime().hour(), QTime::currentTime().minute(), QTime::currentTime().second(), 0);
        if ( oldTime != newTime )
        {
            oldTime = newTime;
            m_time = m_time.addSecs(-1);
        }
        emit  RemainTimeChanged(m_time, REMAIN_TIME);
        if ( m_time == QTime(0, 0, 0) )
        {
            emit  RemainTimeChanged(m_time, TO_SHUTDOWN);
            if ( !MySystemShutdown() )
            {
                emit  RemainTimeChanged(m_time, SHUTDOWN_ERROR);
            }
            break;
        }
    }
}
BOOL ReSetWindows(DWORD dwFlags,BOOL bForce)
{
    //检查参数是否正确
    if(dwFlags!=EWX_LOGOFF&&dwFlags!=EWX_REBOOT&&dwFlags!=EWX_SHUTDOWN)
        return FALSE;
    //获得系统的版本信息，让我们后面确定是否需要提升系统权限
    OSVERSIONINFO osvi={0};
    //获得参数的大小，以提供给GetVersionEx来判断这是一个新版本的OSVERSIONINFO，还是旧版本的
    //新版本是OSVERSIONINFOEX。扩充版本
    osvi.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
    if(!GetVersionEx(&osvi))
    {
        return FALSE;
    }
    //检查操作系统的版本，如果是NT类型的系统，需要提升系统权限
    if(osvi.dwPlatformId==VER_PLATFORM_WIN32_NT)
    {
        //EnableShutDownPriv();
    }
    //判断是否是强制关机，强制关闭系统进程。
    dwFlags|=(bForce!=FALSE)?EWX_FORCE:EWX_FORCEIFHUNG;
    //调用API
    return ExitWindowsEx(dwFlags,0);
}
//ReSetWindows(EWX_SHUTDOWN,true);//关机
//ReSetWindows(EWX_LOGOFF,false);//注销
//ReSetWindows(EWX_REBOOT,true);//重启
bool TimeThread::MySystemShutdown()
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    //获取进程标志
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
        return false;

    //获取关机特权的LUID
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 	&tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    //获取这个进程的关机特权
    AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
    if (GetLastError() != ERROR_SUCCESS) return false;

    //ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,
    //SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE |	SHTDN_REASON_FLAG_PLANNED)
    // 强制关闭计算机
    if (  !ReSetWindows(EWX_SHUTDOWN,true))
         return false;
    return true;
}
//#pragma region 功能实现


