#include <QApplication>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSettings>
#include <QProcess>
#include <QTextCodec>
#include <QTextStream>
#include <QMenuBar>
#include <afxres.h>
#include <QAction>
#include <QStyle>


#include "ransl.h"
#include "widget.h"
#include "g_Snake.h"
#include "g_mgview.h"
#include "checkupdate.h"
#include "filelock.h"
#include "changece.h"
#include "windows.h"
#include "tchar.h"
#include "mouseWheel.h"
#include "chinesechange.h"
#include "daypass.h"
#include "Gameabout.h"
#include "form.h"
//#include "sqlhandle.h"
//#include "login.h"
#include "ScreenShot.h"
//#include "mianban.h"
#include "qipan.h"
#include "shutdown.h"
#include "pastehtml.h"
#include "Enmin.h"
#include "YYSTask.h"
#include "CPUTest.h"
#include "CheckFail.h"
#include "widgetUpdate.h"
//login *lg;
bool g_noshow=false;
const char *gamename[]=
{
    "̰����",
    "�Թ��㷨",
    "������",
    "ÿ���ļ�������",
//    "�ļ�����",
    "�����ֵ��ȡ��",
    "�����ȼ�",
//    "�ļ��м򵥼��",
    "������ת��Ϊƴ��",
    "ÿ��һ��",
    "���ײ���",
//    "sql����",
    "��ͼ����(alt+q������ݼ�)",
    "��ͼʶ��(alt+r������ݼ�)",
//    "�û�����",
    "��ʱ�ػ�",
    "��ҳͼƬ��ȡ",
    "ѹ��ͼƬ��С",
    "����ʦ���������ѯ",
    "����CPU����",
    "������"

};
const char *shuoming[]=
{
    "һ��̰���ߵ�С��Ϸ����ҿ���ͨ�����̵�WSAD�����ߵ��������ң����߳Ե������ɫʳ���ʳ��֮�󣬾ͻ���ʳ�����ɫ��ÿ�Ե�һ��ʳ������ͻ��1�֣��ڿ�ʼ��Ϸ��С���ڿ�������һ��ʼ��ʱ���ߵĳ��ȣ�������Ϸ���ٶ�",
    "һ�������WSAD����С���Ѱ��С�̵㣨�յ㣩���Թ�С��Ϸ����Ϸ��ʼ��ʱ����������һ���Թ���Ȼ������ߵ��յ��ʱ��Խ�̣���õķ���Խ��",
    "����һ�������Ϸ",
    "����һ�����ÿ�춼�����ļ���С���ߣ���QInfo.txt��д��Ҫ���ص��ļ��ĵ�ַ֮�󣬴�ÿ���ļ�������������������ر����Ļ����ͻ��Զ���ÿ���0:00��ʱ��ͻῪʼ����QInfo.txt����ĵ�ַ��������ļ����У���ʽΪ������(YYYY.MM.DD),����дд��Ҫ���µ��ļ��ĵ�ַ,����д��Ҫ���µ��ļ��ĵ�ַ(����д����)...",
//    "����һ��С���ߣ����ڱ����ļ���������ݣ����ԶԳ����ļ���������κ��ļ����м��ܣ����������ļ������һ�����ݽ����޸ģ�����ɱ������ᱨ������Ҳ�ܾ���������ȫ���ر�ĸߣ���ʹ����д�ļ��ܹ�����Ҳ��ȫ��֪��Ҫ��ô�ƽ��ļ��������䲻��֤��ʹ���û������μ�����������У������Զ��ļ����ж�μ��ܣ����Ǽ���֮���ټ��ܣ����Ǳ����μ����뼰�������˳����У�����Ͳ�Ҫ��μ����ˣ�һ�μ��ܺ�������ǲ������ƽ���ļ����ģ��ڽ����ļ���ʱ�����֪�����õ������˳��Ȼ�󷴹����ſ��Խ����ļ��������˵���ܵ�ʱ����񴩴���һ���������ļ���ʱ��������Ѵ���һ�����ر�ע����ǣ��ļ��ڼ��ܵ�ʱ��ǧ���ѳ�����ر��ˣ��������Ƕ�μ��ܵ��ļ�������ļ��Ҹ������Ӱɣ������Ҷ�һ���ļ���\n1234\n222234\n43222\n���������μ����ļ��������ļ����������˳�����\n43222\n222234\n1234\nֻ�������ļ����ܱ���������",
    "һ����ȡ�������С���ߣ������ṩ�˿��Գ�ȡ0-99999�������в���ȡ�ظ������Ĺ��ܣ������Ĭ�ϲ�����������������ĳ�ȡȫ���İ�ť���ܱ����á����ú�֮����������ȡ���̣��Ϳ��Գ�ȡ�������...ע�⣺���±��п������ó�ȡ����ֵ�ķ�ΧŶ",
    "����һ��ͻ�������С���ߣ����Խ��������¹����滻Ϊ������ť�Ĺ��ܣ��������������������Ͽ�������İ�������������ȼ���������־ͻ�˳��ģ��������������������ݵİ�ť����������������ܣ����ڽ�ɽ����ͨ�����Ӣ��������2900��/���Ӵ����ȫ��100%���û���\nע�⣺��ģ�ⰴ�����������밴��Ŷ������������������������ĵĻ����ܱ�ģ�������Ȼ�������Ϊһ����Ϸ�е������ֵ���Ƕ����ģ��ҳ�����CS�л��������Զ�ģ����Ծ�Ĺ��ܣ�����ʧ���ˣ�LOL�еİ���ģ��Ҳ��ʧЧ����������Ϸ��ʱû�в��ԡ�",
//    "һ�����ļ���Ϣ������ʾ��С���ߣ�ѡ��һ���ļ��оͿ���֪�������м����������͵��ļ�����Ȼ��Ҳ��֪���⹤����ʲô�ã����ǻ���д�˳�����",
    "����һ��������ת��Ϊƴ����С���ߣ����Խ��ļ�����������ĵ��ļ���ת��Ϊƴ�����ļ���(����ļ������а������ĵ��ļ�������ô��������ľͻᱻת��Ϊƴ��)�����߿��Խ����ĵ��������뵽��������棬Ȼ��Ϳ���ת��Ϊƴ���ˣ�������������ĸ��д�Ĺ��ܣ�����ȫ����ת��Ϊ��д��ĸ��ֻ��ʾ����ĸ��ѡ��ܶ��˿��ܲ�֪�����������ʲô�ðɣ������Ҿ�һ�����ӣ�������ܿ���ʵ�ֽ��ļ�������������ļ�������Ϊƴ�����ļ���(������ܶ�Ļ����Ϳ��ԱȽϼ��ˣ������������ߵ���;)����ΪһЩ�ļ�������������в���֧���������ԣ��ᵼ����������⣬������Ҫ����һ��һ������Ϊƴ������Ӣ����ĸ�Ļ��ر��鷳����������Ϳ��Խ���Щ�ļ������õ�һ���ļ��У�Ȼ��ͨ������Ĺ��ܾͿ��Զ���Щ�ļ����в����ˣ���������б��ԭ��Ҫ�����ֽ���ƴ����ת���Ļ�����ô�����Խ��������뵽������������ת����",
    "ÿ��һƪ����,����Ҳ�ǲ����",
    "���Խ���ļ��װ�,����������ô��,�����ο�",
//    "����sql��һ��С������ṩ�˼򵥵�����ִ�м������ӵĹ��ܣ����ڹ������Ҳ����ƣ��Ժ�����ʱ��Ļ��������и���",
    "һ����������,����ʱ,������Զ����ص���̨,�����û�������ʹ�ÿ�ݼ�alt+q���Կ���ʹ���������,�������ͼƬ���û�����Ϊ�Ļ�˫���ᱣ�浽�һ���ճ������,ת����CSDN��һƪ����,���ܺ�QQ�Ľ�������",
    "һ������ʶ���ͼ�д��ڵ����ֵ�һ��С���ߣ���alt+r���Կ���ʹ��������ܣ����û�����������£��û�Ȧ�����������,ʶ���ͼ�е����ֲ��ұ��浽�һ���ճ�����С�",
//    "�û����Ե�¼�˻�����������,Ȼ����Է�������bugʲô��,Ҳ�������������ҽ���,Ҳ���Ժʹ��һ����Ŷ",
    "CSDNƮ�ƵĶ�ʱ�ػ�С����,ת��",
    "��������ܹ���ȡhttp��ַ����ʾ��ͼƬ�������ظ���ҳ������ʾ��ͼƬ��ָ���ļ��У���ʱ����֧��https����ַ",
    "����һ��ѹ��ͼƬ��С���������Ĺ���,ʹ�ü򵥣���������ҳ����Ҫ�ϴ�ͼƬ��ʱ����ʾͼƬ������ô��ʹ��������߰ɣ���������ܺܿ�ؽ�����Ҫѹ����ͼƬѹ��������Ҫ�Ĵ�С",
    "����ʦ���������ѯ�ֲ��������������������Ҫ��ѯ�Ĺ��������ƴ������ƴ����д���Ϳ����ҳ����Ӧ�Ĺ���ķֲ������",
    "ͨ������Բ���ʵļ���������ó�CPU�������ĵ����е÷�",
    "�����µĹ��ܣ���bug����ʲô�õĽ��飬�뷨�Ļ�����ӭ���ҷ������һῼ�����������Ҫ�Ĺ��ܵġ���ӭ��ϵQQ351642983,����ȺΪ��376642936,��ʲô����Ҳ���Ե����Ⱥ��������"

};


HHOOK g_KeyBoardHook = NULL;
HHOOK g_LowKeyBoardHook = NULL;
//HHOOK g_MouseHook = NULL;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode,
                WPARAM wParam,
                LPARAM lParam
                )
{
    if(nCode==HC_ACTION)
    {
        if(wParam== WM_SYSKEYDOWN)
        {
            KBDLLHOOKSTRUCT *kblp=(KBDLLHOOKSTRUCT*)lParam;
           // BOOL bCtrlKeyDown = GetAsyncKeyState(VK_CONTROL)>>((sizeof(SHORT) * 8) - 1);
            if ( (kblp->vkCode==Qt::Key_Q)&& ((kblp->flags & LLKHF_ALTDOWN)!=0)/*&& ((GetKeyState(VK_CONTROL) & 0x8000)!=0) */ )
            {
//                QTime dieTime = QTime::currentTime().addMSecs(150);
//                while( QTime::currentTime() < dieTime )
//                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);Q
                ScreenShot *fullWidget=new ScreenShot;
                fullWidget->setType(0); //����Ϊ����ģʽ
                QPixmap Picture = fullWidget->getShotPicture();

                emit fullWidget->loadBackgroundPicture(Picture); //�����źţ�ʹ�õ�ǰ����Ļ��ͼƬ������ͼƬ
                fullWidget->show();
                fullWidget->activateWindow();
                fullWidget->raise();
                    return TRUE; // ������CallNextHookEx���ݣ�ֱ�ӷ���
            }
            else if((kblp->vkCode==Qt::Key_R)&& ((kblp->flags & LLKHF_ALTDOWN)!=0)/*&& ((GetKeyState(VK_CONTROL) & 0x8000)!=0) */ )
            {
                QHostInfo info = QHostInfo::fromName(QString("www.baidu.com"));
                if(!info.addresses().isEmpty())
                {
    //                QTime dieTime = QTime::currentTime().addMSecs(150);
    //                while( QTime::currentTime() < dieTime )
    //                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);Q
                    ScreenShot *fullWidget=new ScreenShot;
                    fullWidget->setType(1); //����Ϊ����ʶ������ģʽ
                    QPixmap Picture = fullWidget->getShotPicture();

                    emit fullWidget->loadBackgroundPicture(Picture); //�����źţ�ʹ�õ�ǰ����Ļ��ͼƬ������ͼƬ
                    fullWidget->show();
                    fullWidget->activateWindow();
                    fullWidget->raise();
                }
                else
                {
                    QMessageBox::about(NULL,"����","�Բ��������豸δ�����޷�ʹ�ý�ͼʶ�����ֹ���");
                }
                    return TRUE; // ������CallNextHookEx���ݣ�ֱ�ӷ���
            }
        }
    }
    return CallNextHookEx(g_KeyBoardHook, nCode, wParam, lParam);
}


//ж�ع���
VOID __stdcall UninstallHookEv()
{
    //UnhookWindowsHookEx(g_KeyBoardHook);
    UnhookWindowsHookEx(g_LowKeyBoardHook);
    //UnhookWindowsHookEx(g_MouseHook);
}

//��װ����,���øú�������װ����
VOID __stdcall InstallHookEv()
{
    //g_KeyBoardHook = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, theApp.m_hInstance, 0);
    QWidget a;
    g_LowKeyBoardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)LowLevelKeyboardProc,GetModuleHandle(NULL) , 0);
    //g_MouseHook = SetWindowsHookEx(WH_MOUSE, (HOOKPROC)MouseProc, theApp.m_hInstance, 0);
}
//Ѱ���ַ�����Ӧidλ��
int findPosition(const char *a)
{
    for(int i=0;i<(int)(sizeof(gamename)/sizeof(gamename[0]));i++)
    {
        if(strcmp(gamename[i],a)==0)
        {
            return i;
        }
    }
    return -1;
}

//���ѡ���ȷ������ʱ��ִ�еĲ���
void Widget::startgame()
{
    //���Գ����Ƿ�������Ӧ���õĶԻ���
    //QMessageBox::about(NULL, "About", QString("About this application%1").arg(type));

    //��ȡѡ���ģʽ����,�����ж���ʾ����

    type=findPosition(Lw->currentItem()->text().toStdString().c_str());


    if(type==findPosition("̰����"))
    {
        //��ʾ̰������Ϸ��ʼ����,��δ��������

        g_snake *window1=new g_snake;
        window1->setWindowTitle(QString(gamename[type]));
        window1->show();
        window1->setFixedWidth(400);
        window1->move((QApplication::desktop()->width() - window1->width()) / 2, (QApplication::desktop()->height() -  window1->height()) / 2);
        mainwindow->g_tixin=false;
        mainwindow->close();


    }
    else if(type==findPosition("�Թ��㷨"))
    {
        g_mgview *window2=new g_mgview;
        window2->show();
        mainwindow->g_tixin=false;
        mainwindow->close();


    }
    else if(type==findPosition("����CPU����"))
    {
        CPUTest *a=new CPUTest();
        a->show();
    }
    else if(type==findPosition("������"))
    {
        pWidget *a=new pWidget;
        a->show();
    }
    else if(type==findPosition("�ļ�����"))
    {
        filelock *fw=new filelock;
        fw->activateWindow();
        mainwindow->g_tixin=false;
        mainwindow->close();
    }
    else if(type==findPosition("�����ֵ��ȡ��"))
    {
        ransl *sl=new ransl;
        sl->show();
        sl->move((QApplication::desktop()->width() - sl->width()) / 2, (QApplication::desktop()->height() -  sl->height()) / 2);
        //mainwindow->g_tixin=false;
        //mainwindow->close();


    }
    else if(type==findPosition("�����ȼ�"))
    {
        mouseWheel *hotkey=new mouseWheel;
        hotkey->show();
        hotkey->move((QApplication::desktop()->width() - hotkey->width()) / 2, (QApplication::desktop()->height() -  hotkey->height()) / 2);
        //mainwindow->g_tixin=false;
        //mainwindow->close();
    }
    else if(type==findPosition("�ļ��м򵥼��"))
    {
        changece *ce=new changece;
        ce->show();
        ce->move((QApplication::desktop()->width() - ce->width()) / 2, (QApplication::desktop()->height() -  ce->height()) / 2);
        mainwindow->g_tixin=false;
        mainwindow->close();



    }
    else if(type==findPosition("������ת��Ϊƴ��"))
    {
        chinesechange *cc=new chinesechange;
        cc->show();
        //mainwindow->g_tixin=false;
        //mainwindow->close();

    }
    else if(type==findPosition("ÿ��һ��"))
    {
        daypass *a=new daypass;
        a->show();
        a->setWindowTitle(gamename[type]);
    }
    else if(type==findPosition("���ײ���"))
    {
        Form *a=new Form;
        a->show();
        a->setWindowTitle(gamename[type]);
    }
//    else if(type==10)
//    {
//        sqlhandle *sql=new sqlhandle;
//        sql->show();

//    }
    else if(type==findPosition("��ͼ����(alt+q������ݼ�)"))
    {
        mainwindow->hide();
        mainwindow->tray->show();
        //mainwindow->tray->showMessage("С���߼���","�Ѿ��Գ��������С������,��ֹ�䴰�ڽ��浲ס�ӽ�");
        QTime dieTime = QTime::currentTime().addMSecs(150);
        while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        ScreenShot *fullWidget=new ScreenShot;
        fullWidget->setType(0); //����Ϊ����ģʽ
        QPixmap Picture = fullWidget->getShotPicture();
        fullWidget->show();
        emit fullWidget->loadBackgroundPicture(Picture); //�����źţ�ʹ�õ�ǰ����Ļ��ͼƬ������ͼƬ
        mainwindow->showNormal();
    }
    else  if(type==findPosition("��ͼʶ��(alt+r������ݼ�)"))
    {
        QHostInfo info = QHostInfo::fromName(QString("www.baidu.com"));
        if(!info.addresses().isEmpty())
        {
            mainwindow->hide();
            mainwindow->tray->show();
            //mainwindow->tray->showMessage("С���߼���","�Ѿ��Գ��������С������,��ֹ�䴰�ڽ��浲ס�ӽ�");
            QTime dieTime = QTime::currentTime().addMSecs(150);
            while( QTime::currentTime() < dieTime )
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            ScreenShot *fullWidget=new ScreenShot;
            fullWidget->setType(1); //����Ϊ����ʶ������ģʽ
            QPixmap Picture = fullWidget->getShotPicture();
            fullWidget->show();
            emit fullWidget->loadBackgroundPicture(Picture); //�����źţ�ʹ�õ�ǰ����Ļ��ͼƬ������ͼƬ
            mainwindow->showNormal();
        }
        else
        {
            QMessageBox::about(NULL,"����","�Բ��������豸δ�����޷�ʹ�ý�ͼ����");
        }
    }
    else if(type==findPosition("��ʱ�ػ�"))
    {
        ShutDown *a=new ShutDown();
        a->show();
        a->setWindowTitle(gamename[type]);
    }
//    else if(type==12)
//    {
//        if(!thelist.isEmpty())
//        {
//            mianban *mb=new mianban;
//            mb->zhanghao=thelist;
//            mb->show();
//        }
//        else
//        {
//            QMessageBox::about(NULL,"����","��Ǹ,�õ�¼�˺Ų��ܽ�������,�����¼��ť���Խ���ע���˺ŵĲ���");
//        }
//    }
    else if(type==findPosition("��ҳͼƬ��ȡ"))
    {
        PasteHtml *ph=new PasteHtml();
        ph->show();
    }
    else if(type==findPosition("ÿ���ļ�������"))
    {
        WidgetUpdate *wu=new WidgetUpdate();
        wu->show();
    }
    else if(type==findPosition("ѹ��ͼƬ��С"))
    {
        Enmin *en=new Enmin();
        en->show();
    }
    else if(type==findPosition("����ʦ���������ѯ"))
    {
        YYSTask *a=new YYSTask();
        a->show();


    }
    else if(type==findPosition("������"))
    {
        newversion *cc=new newversion;
        cc->show();
        mainwindow->g_tixin=false;
        mainwindow->close();
    }


}

//----------------------------------------------���߸�������������----------------------------------
//----------------------------------------------�����ǹ��߼��Ͽ��----------------------------------
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{


    //win7����ģʽ����
    HKEY hKey;
    LPCTSTR strSubKey = L"Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers";
    long lRet = ::RegOpenKeyEx( HKEY_CURRENT_USER, strSubKey, 0, KEY_WRITE, &hKey );
    if ( lRet == ERROR_SUCCESS )
    {

        const size_t cSize = strlen(QCoreApplication::applicationFilePath().replace("/","\\").toStdString().c_str())+1;
        wchar_t* wc = new wchar_t[cSize];
        MultiByteToWideChar(CP_ACP, 0, QCoreApplication::applicationFilePath().replace("/","\\").toStdString().c_str(),
                            strlen(QCoreApplication::applicationFilePath().replace("/","\\").toStdString().c_str()) + 1, wc, sizeof(wchar_t)* cSize/ sizeof(wc[0]));

        //QCoreApplication::applicationFilePath().replace("/","\\").toLocal8Bit().data();
        lRet  = ::RegSetValueEx( hKey,wc, NULL, REG_SZ, (LPBYTE)(L"~ WIN7RTM"),18);
        RegCloseKey( hKey );
    }



    //�ѵ�ǰѡ��ĵĴ���������0����ʾ,�Ա���������������ͷ��ڴ�ռ���ж�
    type=0;
    //��ʼ������˽�б���,��Ϊ֮���趯̬�ռ�
    mainwindow=new BarWidget;
    Lw=new QListWidget;
    Ll=new QLabel("��ѡ�����µ�ģʽ���Կ�ʼ:");
    B_select=new QPushButton(("ȷ��"));
    B_about=new QPushButton(("С���߹���˵��"));

    Lw->setFixedSize(400,300);


    //ѡ����Ϸ��������
    QMenuBar *bar=new QMenuBar();

    QMenu *menu=new QMenu("����");
    QAction *ac1=new QAction("��С������",this);
    QAction *ac2=new QAction("�����л�Ҫ˵",this);
    QAction *ac3=new QAction("�˳�",this);
    QAction *ac4=new QAction("�޸�ͼƬѹ��ʧ��",this);
    ac1->setObjectName("dd");
    menu->addAction(ac4);
    menu->addAction(ac3);

    bar->addMenu(menu);
    bar->addAction(ac2);
    bar->addAction(ac1);
    bar->setStyleSheet("QMenuBar:vertical{background:white;border:1px groove lightblue;border-radius:5px;padding:2px 4px;}QMenuBar:hover{background:white;border:1px groove lightgray;border-radius:5px;padding:2px 4px;};");
    //    tixin=new QLabel("��δ��¼,ѡ��");
//    dl=new QPushButton("��¼");
    starttime=new QTimer();
    connect(starttime,SIGNAL(timeout()),this,SLOT(checkzhanghao()));
    connect(ac1,SIGNAL(triggered()),this,SLOT(showType()));
    connect(ac2,SIGNAL(triggered()),this,SLOT(showSay()));
    connect(ac3,SIGNAL(triggered()),this,SLOT(closePro()));
    connect(ac4,SIGNAL(triggered()),this,SLOT(checkFail()));
    //connect(dl,SIGNAL(clicked()),this,SLOT(denglu()));

    //mainwindow->tray->show();
    mainwindow->tray->setToolTip(QString("�Ҿ�������:С���߼���"));
    mainwindow->tray->setIcon(QApplication::style()->standardIcon(QStyle::SP_FileDialogDetailedView));
    mainwindow->tray->setContextMenu(menu);
    connect(mainwindow->tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(showHide(QSystemTrayIcon::ActivationReason)));



    QVBoxLayout *mainlayout=new QVBoxLayout;
    QHBoxLayout *HLayout=new QHBoxLayout;
    QHBoxLayout *HLayout_1=new QHBoxLayout;
    mainlayout->addWidget(bar);
    HLayout_1->addWidget(Ll,1,Qt::AlignLeft);
    //HLayout_1->addWidget(tixin);
    //HLayout_1->addWidget(dl);
    mainlayout->addLayout(HLayout_1);
    mainlayout->addWidget(Lw);
    HLayout->addWidget(B_about);
    HLayout->addStretch();
    HLayout->addWidget(B_select);
    mainlayout->addLayout(HLayout);

    //��ȡgamename�ַ����б�����������ʾ��list����
    for(int i=0;i<int(sizeof(gamename)/sizeof(gamename[0]));i++)
        Lw->addItem(tr(gamename[i]));

    //����������Ŀ��
    mainwindow->setLayout(mainlayout);
    mainwindow->setWindowTitle(QString("С����ѡ���V%1").arg(VERSION));

    //���ù̶����Һ��ʵĴ�С
    mainwindow->setFixedSize(sizeHint().width(),sizeHint().width());

    //���������С����ť
    mainwindow->setWindowFlags(mainwindow->windowFlags()&~Qt::WindowMaximizeButtonHint/*Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint*/);
    mainwindow->show();

    //��ʾ����
    mainwindow->move((QApplication::desktop()->width() - mainwindow->width()) / 2, (QApplication::desktop()->height() -  mainwindow->height()) / 2);

    //���ӹ��ڰ�ť��ʾ�Ĺ���
    connect(B_about,SIGNAL(clicked()),this,SLOT(showabout()));
    connect(B_select,SIGNAL(clicked()),this,SLOT(startgame()));
    connect(Lw,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(startgame()));
    connect(mainwindow,SIGNAL(pressA()),this,SLOT(relate()));

    //�жϼ���������,����ȷ����������Ӧ�����ԣ�ͬʱ�ر��������
    QDir *temp = new QDir;
    QString theaddress="D:/g_rank";
    if(!temp->exists(theaddress))
    {
        if(!temp->mkdir(theaddress))
        {
               theaddress= "C:/g_rank";
               temp->mkdir(theaddress);
        }
    }
    delete temp;
    QFile fs;
    fs.setFileName(QString("%1/isok.try").arg(theaddress));
    if(!fs.exists())
    {
        fs.open(QIODevice::ReadWrite|QIODevice::Text);
        fs.close();
    }
    QTextCodec *code=QTextCodec::codecForName("UTF-8");
    fs.open(QIODevice::ReadOnly|QIODevice::Text);
    QString read=QString::fromUtf8(fs.readLine());
    fs.close();

    if(read!=QCoreApplication::applicationFilePath())
    {
        //QMessageBox::about(NULL,read,QCoreApplication::applicationFilePath().replace("/","\\").toStdString().c_str());
        //fs.open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream t(&fs);
        t.setCodec(code);
        fs.open(QIODevice::WriteOnly|QIODevice::Text);
        t<<QCoreApplication::applicationFilePath();
        fs.close();
        QProcess::startDetached(QCoreApplication::applicationFilePath(), QStringList());
        exit(0);

    }

    QTime dieTime = QTime::currentTime().addMSecs(100);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    QFile *fs1=new QFile(QCoreApplication::applicationDirPath()+"/Mg_RAndOms.TRY");

    fs1->open(QIODevice::ReadWrite|QIODevice::Text);
    QString str=QString::fromUtf8(fs1->readAll());
    fs1->remove();
    fs1->close();
    QFile *fs2=new QFile(str);
    fs2->remove();
    QString fileStr=QString(QCoreApplication::applicationDirPath());
    QFileInfo fi(QCoreApplication::applicationFilePath());
    QString fileName=QString(fileStr+QString("/%1.exe").arg(fi.completeBaseName().remove(QString("_")+QString(VERSION))));
    QFile::rename(QCoreApplication::applicationFilePath(),fileName);
    mainwindow->activateWindow();
    //mainwindow->hide();

    g_noshow=true;
    //emit denglu();
    //lg->g_an=true;
    //lg->hide();
    //emit lg->on_pushButton_clicked();
    //lg->g_an=false;
    g_noshow=false;
    //setHook();
    InstallHookEv();
}
//���õ�alt+q������ݼ�
void Widget::relate()
{
   // if(event->key() == Qt::Key_B  &&  event->modifiers() == (Qt::AltModifier | Qt::ControlModifier))
    {
        mainwindow->hide();
        mainwindow->tray->show();
        //mainwindow->tray->showMessage("С���߼���","�Ѿ��Գ��������С������,��ֹ�䴰�ڽ��浲ס�ӽ�");
        QTime dieTime = QTime::currentTime().addMSecs(150);
        while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        ScreenShot *fullWidget=new ScreenShot;
        QPixmap Picture = fullWidget->getShotPicture();
        fullWidget->show();
        emit fullWidget->loadBackgroundPicture(Picture); //�����źţ�ʹ�õ�ǰ����Ļ��ͼƬ������ͼƬ
        mainwindow->showNormal();
    }
}
void Widget::checkFail()
{
    CheckFail *cf=new CheckFail;
    cf->show();
    mainwindow->g_tixin=false;
    mainwindow->close();
}

//��¼���ڵ���ʾ
void Widget::denglu(){
    //QMessageBox::about(NULL,"test","ok");
//    if(dl->text()=="��¼")
//    {
//        //lg=new login();
//        if(!g_noshow)
//            lg->show();
//        starttime->start(500);

//    }
//    else{
//        QMessageBox::about(NULL,"����","�˳���¼�ɹ�");
//        dl->setText("��¼");
//        tixin->setText("��δ��¼,ѡ��");
//        thelist.clear();
//    }

}
void Widget::checkzhanghao()
{
//    if(!lg->zhanghao.isEmpty())
//    {
//        thelist=lg->zhanghao;
//        lg->hide();
//    }
//    if(!thelist.isEmpty())
//    {

//        tixin->setText(QString("��ã�%1").arg(thelist.at(1)));
//        starttime->stop();
//        dl->setText("�˳�");

//    }
}

//��ʾ���ڵĽ�����Ϣ
void Widget::showabout()
{
    QListWidget *Lw2=new QListWidget;
    for(int i=0;i<int(sizeof(gamename)/sizeof(gamename[0]));i++)
        Lw2->addItem(tr(gamename[i]));
    QWidget *jieshao=new QWidget;
    QHBoxLayout *mainlayout=new QHBoxLayout;
    QVBoxLayout *vlayout=new QVBoxLayout;
    jieshao->setWindowTitle("С���߹��ܽ���ҳ��");
    Lw2->setFixedHeight(580);
    mainlayout->addWidget(Lw2);
    textedit=new QTextEdit;
    textedit->setReadOnly(true);
//    QPalette palette;
//    palette=textedit->palette();
//    palette.setColor(QPalette::Base,Qt::lightGray);
//    textedit->setPalette(palette);
    textedit->setStyleSheet("QTextEdit{font-family:��Բ;background:#ccc}");
    vlayout->addWidget(textedit);
    QHBoxLayout *hlayout=new QHBoxLayout;
    QPushButton *guanbi=new QPushButton("�ر�");
    hlayout->addStretch();
    hlayout->addWidget(guanbi);
    vlayout->addLayout(hlayout);
    textedit->setFont(QFont("Microsoft YaHei", 18, QFont::Normal));
    mainlayout->addLayout(vlayout);
    jieshao->setLayout(mainlayout);
    jieshao->setFixedSize(800,600);
    jieshao->move((QApplication::desktop()->width() - jieshao->width()) / 2, (QApplication::desktop()->height() -  jieshao->height()) / 2);
    jieshao->show();
    connect(guanbi,SIGNAL(clicked()),jieshao,SLOT(close()));
    connect(Lw2,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(textshow(QListWidgetItem*)));
}
void Widget::closePro()
{
    mainwindow->g_tixin=false;
    mainwindow->close();
}

void Widget::showSay()
{
    QHostInfo info = QHostInfo::fromName(QString("www.baidu.com"));
    if(!info.addresses().isEmpty())
        {
        Gameabout *a=new Gameabout;
        mainwindow->show();
        mainwindow->tray->hide();
        a->hide();
    }
    else
    {
        QMessageBox::about(NULL,"����","�Բ��������豸δ�������޷��鿴����Ҫ˵�Ļ�");
    }

}

void Widget::showType()
{
    if(!mainwindow->isHidden())
    {
        mainwindow->hide();
        mainwindow->tray->show();

    }
    else
    {
        mainwindow->showNormal();
        mainwindow->tray->hide();
    }
}

void Widget::showHide(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
//        case QSystemmainwindow->trayIcon::Trigger:
//            showMessage("����");
//        break;
        case QSystemTrayIcon::DoubleClick:
            mainwindow->showNormal();
            mainwindow->activateWindow();
            mainwindow->tray->hide();
        break;
//        case QSystemTrayIcon::MiddleClick:
//            showMessage("���õ���������껹�ǹ�����갡");
//        break;
        default:
        ;
    }
}

void Widget::textshow(QListWidgetItem* ook)
{
    textedit->setText(QString(shuoming[ook->listWidget()->currentRow()]));
    textedit->setStyleSheet("QTextEdit{font-family:��Բ;background:#ccc}");

}




Widget::~Widget()
{
     del_kongjian(type);
     UninstallHookEv();
}


void Widget::del_kongjian(int t)
{
    if(t==0)
    {
        delete Lw;
        delete Ll;
        delete B_select;
        delete B_about;
        delete mainwindow;
    }
}
