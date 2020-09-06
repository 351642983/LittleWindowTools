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

    //��ע���
    lReturn = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                            L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
                            0,
                            KEY_READ,
                            &hKey);
    if(lReturn != ERROR_SUCCESS)
        return NULL;
    //��ȡCPU����
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
    //��ȡCPU��Ƶ
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
    theCpuInfo+=tempFormat.sprintf("�������ܹ� : %u\n", sysInfo.wProcessorArchitecture);
    theCpuInfo+=tempFormat.sprintf("ҳ���С : %u\n", sysInfo.dwPageSize);
    theCpuInfo+=tempFormat.sprintf("Ӧ�ó�����С��ַ : %u\n", sysInfo.lpMinimumApplicationAddress);
    theCpuInfo+=tempFormat.sprintf("Ӧ�ó�������ַ : %u\n", sysInfo.lpMaximumApplicationAddress);
    theCpuInfo+=tempFormat.sprintf("���������� : %u\n", sysInfo.dwActiveProcessorMask);
    theCpuInfo+=tempFormat.sprintf("���������� : %u\n", sysInfo.dwNumberOfProcessors);
    theCpuInfo+=tempFormat.sprintf("���������� : %u\n", sysInfo.dwProcessorType);
    theCpuInfo+=tempFormat.sprintf("�����ڴ�������� : %u\n", sysInfo.dwAllocationGranularity);
    theCpuInfo+=tempFormat.sprintf("���������� : %u\n", sysInfo.wProcessorLevel);
    theCpuInfo+=tempFormat.sprintf("�������汾 : %u\n", sysInfo.wProcessorRevision);
    osvi.dwOSVersionInfoSize=sizeof(osvi);
    if (GetVersionEx((LPOSVERSIONINFOW)&osvi))
    {
        theCpuInfo+=tempFormat.sprintf("Version     : %u.%u\n", osvi.dwMajorVersion, osvi.dwMinorVersion);
        theCpuInfo+=tempFormat.sprintf("Build       : %u\n", osvi.dwBuildNumber);
        theCpuInfo+=tempFormat.sprintf("Service Pack: %u.%u\n", osvi.wServicePackMajor, osvi.wServicePackMinor);
    }


    //qDebug()<<theCpuInfo; //cpu��ϸ��Ϣ��ȡ
    //qDebug()<<getCPUInfo(1);//cpu������Ϣ
    lb=new QLabel("CPU��ϸ��Ϣ��");
    te=new QTextEdit();
    te->setReadOnly(true);
    te->append("CPU����:"+getCPUInfo(1));
    te->append("CPU��Ƶ:"+getCPUInfo(2));
    te->append(theCpuInfo);
    te->append("ע�⣺CPU���Թ������������ֿ��ܿ���������");
    te->setFixedSize(400,300);
    pb=new QPushButton("���Է���");
    QVBoxLayout *mainlayout=new QVBoxLayout();
    mainlayout->addWidget(lb);
    mainlayout->addWidget(te);
    mainlayout->addWidget(pb);
    setLayout(mainlayout);
    setWindowTitle("����CPU����");
    setFixedSize(sizeHint().width(),sizeHint().height());

    connect(pb,SIGNAL(clicked()),this,SLOT(startTestCPU()));



}
void CPUTest::startTestCPU()
{
    acumulate.start();


    const int pointBit=10000;//����λ��


    const int ARRSIZE=pointBit+10; //���������С����ʾλ��
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
    QMessageBox::about(NULL,"���Խ��",QString("���Ժ�ʱ:%1��\n���յ÷�:%2").arg(acumulate.elapsed()/1000.0).arg(100000.0/(acumulate.elapsed()/1000.0)));
}

CPUTest::~CPUTest()
{

}

