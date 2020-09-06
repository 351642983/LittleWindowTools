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
    "贪吃蛇",
    "迷宫算法",
    "井字棋",
    "每日文件更新器",
//    "文件加密",
    "随机数值抽取器",
    "滚轮热键",
//    "文件夹简单检测",
    "将中文转换为拼音",
    "每日一文",
    "吉凶测试",
//    "sql连接",
    "截图功能(alt+q截屏快捷键)",
    "截图识字(alt+r截屏快捷键)",
//    "用户留言",
    "计时关机",
    "网页图片爬取",
    "压缩图片大小",
    "阴阳师悬赏任务查询",
    "测试CPU分数",
    "检查更新"

};
const char *shuoming[]=
{
    "一款贪吃蛇的小游戏，玩家可以通过键盘的WSAD控制蛇的上下左右，当蛇吃到别的颜色食物的食物之后，就会变成食物的颜色，每吃到一个食物，分数就会加1分，在开始游戏的小窗口可以设置一开始的时候蛇的长度，还有游戏的速度",
    "一款玩家用WSAD控制小红点寻找小绿点（终点）的迷宫小游戏，游戏开始的时候会随机生成一个迷宫。然后玩家走到终点的时间越短，则得的分数越高",
    "这是一款井字棋游戏",
    "这是一款可以每天都更新文件的小工具，在QInfo.txt中写上要下载的文件的地址之后，打开每日文件更新器点击监听并不关闭他的话，就会自动在每天的0:00的时间就会开始更新QInfo.txt里面的地址到程序的文件夹中，格式为：日期(YYYY.MM.DD),换行写写需要更新的文件的地址,换行写需要更新的文件的地址(可以写入多个)...",
//    "这是一款小工具，用于保护文件里面的内容，可以对除了文件夹以外的任何文件进行加密，加密完会对文件里面的一切数据进行修改，所以杀毒软件会报毒（我也很绝望），安全性特别的高，即使是我写的加密规则我也完全不知道要怎么破解文件，但是其不验证性使得用户必须牢记其中密码才行，还可以对文件进行多次加密，就是加密之后再加密，但是必须牢记密码及其密码的顺序才行，否则就不要多次加密了，一次加密后基本上是不可能破解出文件来的，在解锁文件的时候必须知道设置的密码的顺序，然后反过来才可以解锁文件，形象点说加密的时候就像穿大衣一样，解锁文件的时候就像是脱大衣一样。特别注意的是，文件在加密的时候千万别把程序给关闭了！！最后就是多次加密的文件后解锁文件我给个例子吧：假如我对一个文件以\n1234\n222234\n43222\n的密码依次加密文件，解锁文件密码的输入顺序就是\n43222\n222234\n1234\n只有这样文件才能被正常解锁",
    "一个抽取随机数的小工具，里面提供了可以抽取0-99999的数，有不抽取重复的数的功能，这项功能默认不开启，开启后里面的抽取全部的按钮才能被启用。设置好之后点击开启抽取进程，就可以抽取随机数了...注意：最下边有可以设置抽取的数值的范围哦",
    "这是一个突发奇想的小工具，可以将滚轮上下滚动替换为其他按钮的功能，在输入框里面输入键盘上可以输入的按键，点击开启热键后滚动滚轮就会顺序模拟你在输入框中输入内容的按钮，就是利用这个功能，我在金山打字通里面的英文输入以2900字/分钟打败了全国100%的用户。\n注意：是模拟按键而不是输入按键哦，所以在输入框里面输入中文的话不能被模拟出来，然后就是因为一般游戏中的虚拟键值都是独立的，我尝试在CS中滑动滚轮自动模拟跳跃的功能，但是失败了，LOL中的按键模拟也会失效。其他的游戏暂时没有测试。",
//    "一个简单文件信息功能显示的小工具，选中一个文件夹就可以知道里面有几个几种类型的文件，虽然我也不知道这工具有什么用，但是还是写了出来了",
    "这是一个将中文转换为拼音的小工具，可以将文件夹里面的中文的文件名转换为拼音的文件名(如果文件夹中有包含中文的文件名，那么里面的中文就会被转换为拼音)，或者可以将中文的内容输入到输入框里面，然后就可以转换为拼音了，里面有像首字母大写的功能，还有全部都转换为大写字母，只显示首字母的选项；很多人可能不知道这个功能有什么用吧，这里我举一个例子，这个功能可以实现将文件夹里面的中文文件名命名为拼音的文件名(如果量很多的话，就可以比较简单了，这就是这个工具的用途)，因为一些文件名在其他软件中不能支持中文语言，会导致乱码等问题，我们需要将其一个一个命名为拼音或者英文字母的话特别麻烦，所以这里就可以将这些文件都放置到一个文件中，然后通过里面的功能就可以对那些文件进行操作了，另外如果有别的原因要对文字进行拼音的转换的话，那么还可以将文字输入到输入框里面进行转换。",
    "每天一篇文章,看看也是不错的",
    "测试今天的吉凶吧,看看运气怎么样,仅供参考",
//    "连接sql的一个小软件，提供了简单的命令执行及其连接的功能，现在功能尚且不完善，以后若有时间的话会对其进行更新",
    "一个截屏功能,截屏时,程序会自动隐藏到后台,方便用户截屏，使用快捷键alt+q可以快速使用这个功能,截屏后的图片如果没有另存为的话双击会保存到右击的粘贴板中,转载自CSDN的一篇文章,功能和QQ的截屏类似",
    "一个截屏识别截图中存在的文字的一个小工具，用alt+r可以快速使用这个功能，在用户联网的情况下，用户圈定截屏区域后,识别截图中的文字并且保存到右击的粘贴板中。",
//    "用户可以登录账户在这里留言,然后可以反馈建议bug什么的,也可以在这里与我交流,也可以和大家一起交流哦",
    "CSDN飘云的定时关机小工具,转载",
    "这个工具能够爬取http网址上显示的图片，并下载该网页上所显示的图片到指定文件夹，暂时并不支持https的网址",
    "这是一个压缩图片大小（质量）的工具,使用简单，当你在网页中需要上传图片的时候显示图片过大，那么就使用这个工具吧，这个工具能很快地将你想要压缩的图片压缩到你想要的大小",
    "阴阳师悬赏任务查询分布情况，在搜索框中输入要查询的怪物的名称拼音或者拼音简写，就可以找出相对应的怪物的分布情况了",
    "通过运算圆周率的计算分数，得出CPU单个核心的运行得分",
    "检查更新的功能，有bug或有什么好的建议，想法的话，欢迎找我反馈，我会考虑着添加你想要的功能的。欢迎联系QQ351642983,讨论群为：376642936,有什么提议也可以到这个群里面讨论"

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
                fullWidget->setType(0); //设置为截屏模式
                QPixmap Picture = fullWidget->getShotPicture();

                emit fullWidget->loadBackgroundPicture(Picture); //发送信号，使用当前的屏幕的图片作背景图片
                fullWidget->show();
                fullWidget->activateWindow();
                fullWidget->raise();
                    return TRUE; // 不再往CallNextHookEx传递，直接返回
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
                    fullWidget->setType(1); //设置为截屏识别文字模式
                    QPixmap Picture = fullWidget->getShotPicture();

                    emit fullWidget->loadBackgroundPicture(Picture); //发送信号，使用当前的屏幕的图片作背景图片
                    fullWidget->show();
                    fullWidget->activateWindow();
                    fullWidget->raise();
                }
                else
                {
                    QMessageBox::about(NULL,"提醒","对不起，您的设备未联网无法使用截图识别文字功能");
                }
                    return TRUE; // 不再往CallNextHookEx传递，直接返回
            }
        }
    }
    return CallNextHookEx(g_KeyBoardHook, nCode, wParam, lParam);
}


//卸载钩子
VOID __stdcall UninstallHookEv()
{
    //UnhookWindowsHookEx(g_KeyBoardHook);
    UnhookWindowsHookEx(g_LowKeyBoardHook);
    //UnhookWindowsHookEx(g_MouseHook);
}

//安装钩子,调用该函数即安装钩子
VOID __stdcall InstallHookEv()
{
    //g_KeyBoardHook = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, theApp.m_hInstance, 0);
    QWidget a;
    g_LowKeyBoardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)LowLevelKeyboardProc,GetModuleHandle(NULL) , 0);
    //g_MouseHook = SetWindowsHookEx(WH_MOUSE, (HOOKPROC)MouseProc, theApp.m_hInstance, 0);
}
//寻找字符串对应id位置
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

//点击选择框确定界面时所执行的操作
void Widget::startgame()
{
    //测试程序是否正常响应设置的对话框
    //QMessageBox::about(NULL, "About", QString("About this application%1").arg(type));

    //获取选择的模式类型,用来判断显示串口

    type=findPosition(Lw->currentItem()->text().toStdString().c_str());


    if(type==findPosition("贪吃蛇"))
    {
        //显示贪吃蛇游戏开始界面,尚未进行美化

        g_snake *window1=new g_snake;
        window1->setWindowTitle(QString(gamename[type]));
        window1->show();
        window1->setFixedWidth(400);
        window1->move((QApplication::desktop()->width() - window1->width()) / 2, (QApplication::desktop()->height() -  window1->height()) / 2);
        mainwindow->g_tixin=false;
        mainwindow->close();


    }
    else if(type==findPosition("迷宫算法"))
    {
        g_mgview *window2=new g_mgview;
        window2->show();
        mainwindow->g_tixin=false;
        mainwindow->close();


    }
    else if(type==findPosition("测试CPU分数"))
    {
        CPUTest *a=new CPUTest();
        a->show();
    }
    else if(type==findPosition("井字棋"))
    {
        pWidget *a=new pWidget;
        a->show();
    }
    else if(type==findPosition("文件加密"))
    {
        filelock *fw=new filelock;
        fw->activateWindow();
        mainwindow->g_tixin=false;
        mainwindow->close();
    }
    else if(type==findPosition("随机数值抽取器"))
    {
        ransl *sl=new ransl;
        sl->show();
        sl->move((QApplication::desktop()->width() - sl->width()) / 2, (QApplication::desktop()->height() -  sl->height()) / 2);
        //mainwindow->g_tixin=false;
        //mainwindow->close();


    }
    else if(type==findPosition("滚轮热键"))
    {
        mouseWheel *hotkey=new mouseWheel;
        hotkey->show();
        hotkey->move((QApplication::desktop()->width() - hotkey->width()) / 2, (QApplication::desktop()->height() -  hotkey->height()) / 2);
        //mainwindow->g_tixin=false;
        //mainwindow->close();
    }
    else if(type==findPosition("文件夹简单检测"))
    {
        changece *ce=new changece;
        ce->show();
        ce->move((QApplication::desktop()->width() - ce->width()) / 2, (QApplication::desktop()->height() -  ce->height()) / 2);
        mainwindow->g_tixin=false;
        mainwindow->close();



    }
    else if(type==findPosition("将中文转换为拼音"))
    {
        chinesechange *cc=new chinesechange;
        cc->show();
        //mainwindow->g_tixin=false;
        //mainwindow->close();

    }
    else if(type==findPosition("每日一文"))
    {
        daypass *a=new daypass;
        a->show();
        a->setWindowTitle(gamename[type]);
    }
    else if(type==findPosition("吉凶测试"))
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
    else if(type==findPosition("截图功能(alt+q截屏快捷键)"))
    {
        mainwindow->hide();
        mainwindow->tray->show();
        //mainwindow->tray->showMessage("小工具集合","已经对程序进行最小化操作,防止其窗口界面挡住视角");
        QTime dieTime = QTime::currentTime().addMSecs(150);
        while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        ScreenShot *fullWidget=new ScreenShot;
        fullWidget->setType(0); //设置为截屏模式
        QPixmap Picture = fullWidget->getShotPicture();
        fullWidget->show();
        emit fullWidget->loadBackgroundPicture(Picture); //发送信号，使用当前的屏幕的图片作背景图片
        mainwindow->showNormal();
    }
    else  if(type==findPosition("截图识字(alt+r截屏快捷键)"))
    {
        QHostInfo info = QHostInfo::fromName(QString("www.baidu.com"));
        if(!info.addresses().isEmpty())
        {
            mainwindow->hide();
            mainwindow->tray->show();
            //mainwindow->tray->showMessage("小工具集合","已经对程序进行最小化操作,防止其窗口界面挡住视角");
            QTime dieTime = QTime::currentTime().addMSecs(150);
            while( QTime::currentTime() < dieTime )
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            ScreenShot *fullWidget=new ScreenShot;
            fullWidget->setType(1); //设置为截屏识别文字模式
            QPixmap Picture = fullWidget->getShotPicture();
            fullWidget->show();
            emit fullWidget->loadBackgroundPicture(Picture); //发送信号，使用当前的屏幕的图片作背景图片
            mainwindow->showNormal();
        }
        else
        {
            QMessageBox::about(NULL,"提醒","对不起，您的设备未联网无法使用截图功能");
        }
    }
    else if(type==findPosition("计时关机"))
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
//            QMessageBox::about(NULL,"提醒","抱歉,得登录账号才能进行留言,点击登录按钮可以进行注册账号的操作");
//        }
//    }
    else if(type==findPosition("网页图片爬取"))
    {
        PasteHtml *ph=new PasteHtml();
        ph->show();
    }
    else if(type==findPosition("每日文件更新器"))
    {
        WidgetUpdate *wu=new WidgetUpdate();
        wu->show();
    }
    else if(type==findPosition("压缩图片大小"))
    {
        Enmin *en=new Enmin();
        en->show();
    }
    else if(type==findPosition("阴阳师悬赏任务查询"))
    {
        YYSTask *a=new YYSTask();
        a->show();


    }
    else if(type==findPosition("检查更新"))
    {
        newversion *cc=new newversion;
        cc->show();
        mainwindow->g_tixin=false;
        mainwindow->close();
    }


}

//----------------------------------------------工具更新区域在以上----------------------------------
//----------------------------------------------下面是工具集合框架----------------------------------
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{


    //win7兼容模式运行
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



    //把当前选择的的窗口类型用0来表示,以便后来析构函数的释放内存空间的判断
    type=0;
    //初始化各个私有变量,并为之赋予动态空间
    mainwindow=new BarWidget;
    Lw=new QListWidget;
    Ll=new QLabel("请选择以下的模式用以开始:");
    B_select=new QPushButton(("确认"));
    B_about=new QPushButton(("小工具功能说明"));

    Lw->setFixedSize(400,300);


    //选择游戏界面的设计
    QMenuBar *bar=new QMenuBar();

    QMenu *menu=new QMenu("功能");
    QAction *ac1=new QAction("最小化窗口",this);
    QAction *ac2=new QAction("作者有话要说",this);
    QAction *ac3=new QAction("退出",this);
    QAction *ac4=new QAction("修复图片压缩失败",this);
    ac1->setObjectName("dd");
    menu->addAction(ac4);
    menu->addAction(ac3);

    bar->addMenu(menu);
    bar->addAction(ac2);
    bar->addAction(ac1);
    bar->setStyleSheet("QMenuBar:vertical{background:white;border:1px groove lightblue;border-radius:5px;padding:2px 4px;}QMenuBar:hover{background:white;border:1px groove lightgray;border-radius:5px;padding:2px 4px;};");
    //    tixin=new QLabel("还未登录,选择");
//    dl=new QPushButton("登录");
    starttime=new QTimer();
    connect(starttime,SIGNAL(timeout()),this,SLOT(checkzhanghao()));
    connect(ac1,SIGNAL(triggered()),this,SLOT(showType()));
    connect(ac2,SIGNAL(triggered()),this,SLOT(showSay()));
    connect(ac3,SIGNAL(triggered()),this,SLOT(closePro()));
    connect(ac4,SIGNAL(triggered()),this,SLOT(checkFail()));
    //connect(dl,SIGNAL(clicked()),this,SLOT(denglu()));

    //mainwindow->tray->show();
    mainwindow->tray->setToolTip(QString("我就是托盘:小工具集合"));
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

    //获取gamename字符组中变量个数并显示在list框内
    for(int i=0;i<int(sizeof(gamename)/sizeof(gamename[0]));i++)
        Lw->addItem(tr(gamename[i]));

    //设置主界面的框架
    mainwindow->setLayout(mainlayout);
    mainwindow->setWindowTitle(QString("小工具选择框V%1").arg(VERSION));

    //设置固定并且合适的大小
    mainwindow->setFixedSize(sizeHint().width(),sizeHint().width());

    //隐藏最大最小化按钮
    mainwindow->setWindowFlags(mainwindow->windowFlags()&~Qt::WindowMaximizeButtonHint/*Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint*/);
    mainwindow->show();

    //显示置中
    mainwindow->move((QApplication::desktop()->width() - mainwindow->width()) / 2, (QApplication::desktop()->height() -  mainwindow->height()) / 2);

    //链接关于按钮显示的功能
    connect(B_about,SIGNAL(clicked()),this,SLOT(showabout()));
    connect(B_select,SIGNAL(clicked()),this,SLOT(startgame()));
    connect(Lw,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(startgame()));
    connect(mainwindow,SIGNAL(pressA()),this,SLOT(relate()));

    //判断兼容性问题,不正确则重启以适应兼容性；同时关闭组策略中
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
//弃用的alt+q截屏快捷键
void Widget::relate()
{
   // if(event->key() == Qt::Key_B  &&  event->modifiers() == (Qt::AltModifier | Qt::ControlModifier))
    {
        mainwindow->hide();
        mainwindow->tray->show();
        //mainwindow->tray->showMessage("小工具集合","已经对程序进行最小化操作,防止其窗口界面挡住视角");
        QTime dieTime = QTime::currentTime().addMSecs(150);
        while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        ScreenShot *fullWidget=new ScreenShot;
        QPixmap Picture = fullWidget->getShotPicture();
        fullWidget->show();
        emit fullWidget->loadBackgroundPicture(Picture); //发送信号，使用当前的屏幕的图片作背景图片
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

//登录窗口的显示
void Widget::denglu(){
    //QMessageBox::about(NULL,"test","ok");
//    if(dl->text()=="登录")
//    {
//        //lg=new login();
//        if(!g_noshow)
//            lg->show();
//        starttime->start(500);

//    }
//    else{
//        QMessageBox::about(NULL,"提醒","退出登录成功");
//        dl->setText("登录");
//        tixin->setText("还未登录,选择");
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

//        tixin->setText(QString("你好，%1").arg(thelist.at(1)));
//        starttime->stop();
//        dl->setText("退出");

//    }
}

//显示关于的界面信息
void Widget::showabout()
{
    QListWidget *Lw2=new QListWidget;
    for(int i=0;i<int(sizeof(gamename)/sizeof(gamename[0]));i++)
        Lw2->addItem(tr(gamename[i]));
    QWidget *jieshao=new QWidget;
    QHBoxLayout *mainlayout=new QHBoxLayout;
    QVBoxLayout *vlayout=new QVBoxLayout;
    jieshao->setWindowTitle("小工具功能介绍页面");
    Lw2->setFixedHeight(580);
    mainlayout->addWidget(Lw2);
    textedit=new QTextEdit;
    textedit->setReadOnly(true);
//    QPalette palette;
//    palette=textedit->palette();
//    palette.setColor(QPalette::Base,Qt::lightGray);
//    textedit->setPalette(palette);
    textedit->setStyleSheet("QTextEdit{font-family:幼圆;background:#ccc}");
    vlayout->addWidget(textedit);
    QHBoxLayout *hlayout=new QHBoxLayout;
    QPushButton *guanbi=new QPushButton("关闭");
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
        QMessageBox::about(NULL,"提醒","对不起，您的设备未联网，无法查看作者要说的话");
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
//            showMessage("单击");
//        break;
        case QSystemTrayIcon::DoubleClick:
            mainwindow->showNormal();
            mainwindow->activateWindow();
            mainwindow->tray->hide();
        break;
//        case QSystemTrayIcon::MiddleClick:
//            showMessage("你用的是三轮鼠标还是滚轮鼠标啊");
//        break;
        default:
        ;
    }
}

void Widget::textshow(QListWidgetItem* ook)
{
    textedit->setText(QString(shuoming[ook->listWidget()->currentRow()]));
    textedit->setStyleSheet("QTextEdit{font-family:幼圆;background:#ccc}");

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
