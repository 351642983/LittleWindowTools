#include "CPUTest.h"
#include "windows.h"
#include "stdio.h"
#include "string.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>

//Type==1 CPUSpeed,Type==2 CPUName;
QString getCPUInfo(int Type)
{
    HKEY  hKey;
    LONG lReturn;
    DWORD type;
    DWORD dwSize = 100;
    DWORD dwMHz;
    WCHAR szCPUName[100] = {0};

    //打开注册表
    lReturn = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                            L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
                            0,
                            KEY_READ,
                            &hKey);
    if(lReturn != ERROR_SUCCESS)
        return NULL;
    //获取CPU名称
    if(Type==1)
    {
        lReturn = RegQueryValueExW(hKey, L"ProcessorNameString", NULL, &type, (BYTE *)szCPUName, &dwSize);
        if(lReturn != ERROR_SUCCESS)
            return NULL;

        QString CPUName;
        for(int i=0;i<100;i++)
        {
            if(szCPUName[i]!=0)
            {
              CPUName+=(QChar)szCPUName[i];
            }
        }
        return CPUName;
    }
    //获取CPU主频
    if(Type==2)
    {
        lReturn = RegQueryValueExW(hKey, L"~MHz", NULL, NULL, (LPBYTE)&dwMHz, &dwSize);
        if(lReturn != ERROR_SUCCESS)
            return NULL;
        RegCloseKey(hKey);
          QString CPUSpeed;
        CPUSpeed.sprintf("%d Mhz",(int)dwMHz);
        return CPUSpeed;
    }
    return NULL;
}

CPUTest::CPUTest(QWidget *parent):
    QWidget(parent)
{
    QString theCpuInfo="";
    QString tempFormat;
    SYSTEM_INFO  sysInfo;
    OSVERSIONINFOEX osvi;
    GetSystemInfo(&sysInfo);
    theCpuInfo+=tempFormat.sprintf("OemId : %u\n", sysInfo.dwOemId);
    theCpuInfo+=tempFormat.sprintf("处理器架构 : %u\n", sysInfo.wProcessorArchitecture);
    theCpuInfo+=tempFormat.sprintf("页面大小 : %u\n", sysInfo.dwPageSize);
    theCpuInfo+=tempFormat.sprintf("应用程序最小地址 : %u\n", sysInfo.lpMinimumApplicationAddress);
    theCpuInfo+=tempFormat.sprintf("应用程序最大地址 : %u\n", sysInfo.lpMaximumApplicationAddress);
    theCpuInfo+=tempFormat.sprintf("处理器掩码 : %u\n", sysInfo.dwActiveProcessorMask);
    theCpuInfo+=tempFormat.sprintf("处理器数量 : %u\n", sysInfo.dwNumberOfProcessors);
    theCpuInfo+=tempFormat.sprintf("处理器类型 : %u\n", sysInfo.dwProcessorType);
    theCpuInfo+=tempFormat.sprintf("虚拟内存分配粒度 : %u\n", sysInfo.dwAllocationGranularity);
    theCpuInfo+=tempFormat.sprintf("处理器级别 : %u\n", sysInfo.wProcessorLevel);
    theCpuInfo+=tempFormat.sprintf("处理器版本 : %u\n", sysInfo.wProcessorRevision);
    osvi.dwOSVersionInfoSize=sizeof(osvi);
    if (GetVersionEx((LPOSVERSIONINFOW)&osvi))
    {
        theCpuInfo+=tempFormat.sprintf("Version     : %u.%u\n", osvi.dwMajorVersion, osvi.dwMinorVersion);
        theCpuInfo+=tempFormat.sprintf("Build       : %u\n", osvi.dwBuildNumber);
        theCpuInfo+=tempFormat.sprintf("Service Pack: %u.%u\n", osvi.wServicePackMajor, osvi.wServicePackMinor);
    }


    //qDebug()<<theCpuInfo; //cpu详细信息获取
    //qDebug()<<getCPUInfo(1);//cpu基本信息
    lb=new QLabel("CPU详细信息：");
    te=new QTextEdit();
    te->setReadOnly(true);
    te->append("CPU名称:"+getCPUInfo(1));
    te->append("CPU主频:"+getCPUInfo(2));
    te->append(theCpuInfo);
    te->append("注意：CPU测试过程中软件会出现可能卡主的现象");
    te->setFixedSize(400,300);
    pb=new QPushButton("测试分数");
    QVBoxLayout *mainlayout=new QVBoxLayout();
    mainlayout->addWidget(lb);
    mainlayout->addWidget(te);
    mainlayout->addWidget(pb);
    setLayout(mainlayout);
    setWindowTitle("测试CPU分数");
    setFixedSize(sizeHint().width(),sizeHint().height());

    connect(pb,SIGNAL(clicked()),this,SLOT(startTestCPU()));



}
void CPUTest::startTestCPU()
{
    acumulate.start();


    const int pointBit=10000;//运行位数


    const int ARRSIZE=pointBit+10; //定义数组大小，显示位数
      char x[ARRSIZE], z[ARRSIZE]; //x[0] x[1] . x[2] x[3] x[4] .... x[ARRSIZE-1]
      int a=1, b=3, c, d, Run=1, Cnt=0;
      memset(x,0,ARRSIZE);
      memset(z,0,ARRSIZE);
      x[1] = 2;
      z[1] = 2;
      while(Run && (++Cnt<200000000))
      {
        //z*=a;
        d = 0;
        for(int i=ARRSIZE-1; i>0; i--)
        {
          c = z[i]*a + d;
          z[i] = c % 10;
          d = c / 10;
        }
        //z/=b;
        d = 0;
        for(int i=0; i<ARRSIZE; i++)
        {
          c = z[i]+d*10;
          z[i] = c / b;
          d = c % b;
        }
        //x+=z;
        Run = 0;
        for(int i=ARRSIZE-1; i>0; i--)
        {
          c = x[i] + z[i];
          x[i] = c%10;
          x[i-1] += c/10;
          Run |= z[i];
        }
        a++;
        b+=2;
      }

      FinishMath();
}
void CPUTest::FinishMath()
{
    QMessageBox::about(NULL,"测试结果",QString("测试耗时:%1秒\n最终得分:%2").arg(acumulate.elapsed()/1000.0).arg(100000.0/(acumulate.elapsed()/1000.0)));
}

CPUTest::~CPUTest()
{

}

