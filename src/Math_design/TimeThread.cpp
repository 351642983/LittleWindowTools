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
    //�������Ƿ���ȷ
    if(dwFlags!=EWX_LOGOFF&&dwFlags!=EWX_REBOOT&&dwFlags!=EWX_SHUTDOWN)
        return FALSE;
    //���ϵͳ�İ汾��Ϣ�������Ǻ���ȷ���Ƿ���Ҫ����ϵͳȨ��
    OSVERSIONINFO osvi={0};
    //��ò����Ĵ�С�����ṩ��GetVersionEx���ж�����һ���°汾��OSVERSIONINFO�����Ǿɰ汾��
    //�°汾��OSVERSIONINFOEX������汾
    osvi.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
    if(!GetVersionEx(&osvi))
    {
        return FALSE;
    }
    //������ϵͳ�İ汾�������NT���͵�ϵͳ����Ҫ����ϵͳȨ��
    if(osvi.dwPlatformId==VER_PLATFORM_WIN32_NT)
    {
        //EnableShutDownPriv();
    }
    //�ж��Ƿ���ǿ�ƹػ���ǿ�ƹر�ϵͳ���̡�
    dwFlags|=(bForce!=FALSE)?EWX_FORCE:EWX_FORCEIFHUNG;
    //����API
    return ExitWindowsEx(dwFlags,0);
}
//ReSetWindows(EWX_SHUTDOWN,true);//�ػ�
//ReSetWindows(EWX_LOGOFF,false);//ע��
//ReSetWindows(EWX_REBOOT,true);//����
bool TimeThread::MySystemShutdown()
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    //��ȡ���̱�־
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
        return false;

    //��ȡ�ػ���Ȩ��LUID
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 	&tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    //��ȡ������̵Ĺػ���Ȩ
    AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
    if (GetLastError() != ERROR_SUCCESS) return false;

    //ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,
    //SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE |	SHTDN_REASON_FLAG_PLANNED)
    // ǿ�ƹرռ����
    if (  !ReSetWindows(EWX_SHUTDOWN,true))
         return false;
    return true;
}
//#pragma region ����ʵ��


