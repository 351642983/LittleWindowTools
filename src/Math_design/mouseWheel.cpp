#include "mouseWheel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QProcess>
#include <QApplication>
#include "widget.h"
#include "handoption.h"
QSpinBox *thevalue;
int g_buttonnumber[]=
{
    Qt::Key_0,
    Qt::Key_1,
    Qt::Key_2,
    Qt::Key_3,
    Qt::Key_4,
    Qt::Key_5,
    Qt::Key_6,
    Qt::Key_7,
    Qt::Key_8,
    Qt::Key_9,
    Qt::Key_Q,
    Qt::Key_W,
    Qt::Key_E,
    Qt::Key_R,
    Qt::Key_T,
    Qt::Key_Y,
    Qt::Key_U,
    Qt::Key_I,
    Qt::Key_O,
    Qt::Key_P,
    Qt::Key_A,
    Qt::Key_S,
    Qt::Key_D,
    Qt::Key_F,
    Qt::Key_G,
    Qt::Key_H,
    Qt::Key_J,
    Qt::Key_K,
    Qt::Key_L,
    Qt::Key_Z,
    Qt::Key_X,
    Qt::Key_C,
    Qt::Key_V,
    Qt::Key_B,
    Qt::Key_N,
    Qt::Key_M,
    Qt::Key_Space,
    'A',
    'B',
    'C',
    'D',
    'E',
    'F',
    'G',
    'H',
    'I',
    'J',
    'K',
    'L',
    'M',
    'N',
    'O',
    'P',
    'Q',
    'R',
    'S',
    'T',
    'U',
    'V',
    'W',
    'X',
    'Y',
    'Z',
    VK_RETURN,
    187,
    189,
    VK_DECIMAL,
    VK_OEM_1,
    188,
    VK_OEM_7,
    VK_OEM_2,
    VK_OEM_7,
    VK_OEM_2,
    189,
    187,
    190,
    188,
    192,
    192,
    219,
    219,
    221,
    221,
    220,
    220,
    VK_TAB,
    VK_OEM_1,
    Qt::Key_1,
    Qt::Key_2,
    Qt::Key_3,
    Qt::Key_4,
    Qt::Key_5,
    Qt::Key_6,
    Qt::Key_7,
    Qt::Key_8,
    Qt::Key_9,
    Qt::Key_0

};
QChar c_button[]=
{
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'q',
    'w',
    'e',
    'r',
    't',
    'y',
    'u',
    'i',
    'o',
    'p',
    'a',
    's',
    'd',
    'f',
    'g',
    'h',
    'j',
    'k',
    'l',
    'z',
    'x',
    'c',
    'v',
    'b',
    'n',
    'm',
    ' ',
    'A',
    'B',
    'C',
    'D',
    'E',
    'F',
    'G',
    'H',
    'I',
    'J',
    'K',
    'L',
    'M',
    'N',
    'O',
    'P',
    'Q',
    'R',
    'S',
    'T',
    'U',
    'V',
    'W',
    'X',
    'Y',
    'Z',
    '\n',
    '+',
    '-',
    '.',
    ';',
    ',',
    '\'',
    '?',
    '\"',
    '/',
    '_',
    '=',
    '>',
    '<',
    '`',
    '~',
    '[',
    '{',
    ']',
    '}',
    '|',
    '\\',
    '\t',
    ':',
    '!',
    '@',
    '#',
    '$',
    '%',
    '^',
    '&',
    '*',
    '(',
    ')'
};
QChar c_Shift[]=
{
    '?',
    '\"',
    '+',
    '_',
    '>',
    '<',
    '~',
    '{',
    '}',
    '|',
    ':',
    '!',
    '@',
    '#',
    '$',
    '%',
    '^',
    '&',
    '*',
    '(',
    ')'
};
bool g_count=false;
QTime Lost_Time;
int g_addtion=0;
bool g_zhuantai;
HHOOK mouseHook=NULL;
QTextEdit *textedit;
// for key pushing

mouseWheel::mouseWheel(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainlayout=new QVBoxLayout;
    g_zhuantai=false;
    pb_hotkey=new QPushButton("开启热键");
    //returnMain=new QPushButton("返回小工具集合");
    textedit=new QTextEdit;
    jiange=new QLabel("滚轮滑动时按键间响应的时间间隔(毫秒*2) 范围(1-500ms)：");
    mainlayout->addWidget(pb_hotkey);
    mainlayout->addWidget(textedit);
    QHBoxLayout *anothelayout=new QHBoxLayout;
    anothelayout->addWidget(jiange);
    thevalue=new QSpinBox;
    thevalue->setRange(1,500);
    thevalue->setValue(1);
    anothelayout->addWidget(thevalue);
    mainlayout->addLayout(anothelayout);
    //mainlayout->addWidget(returnMain);
    setLayout(mainlayout);
    setFixedSize(400,300);
    connect(pb_hotkey,SIGNAL(clicked()),this,SLOT(changeinfo()));
    //connect(returnMain,SIGNAL(clicked()),this,SLOT(window_return()));
    setWindowTitle("滚轮热键模拟");
    setWindowFlags(Qt::WindowCloseButtonHint);


}



mouseWheel::~mouseWheel()
{

}
void mouseWheel::window_return()
{
    g_zhuantai=false;
    UnhookWindowsHookEx(mouseHook);
    QProcess::startDetached(QCoreApplication::applicationFilePath().remove(QString("_")+QString(VERSION)), QStringList());
    exit(0);
}
void mouseWheel::changeinfo()
{
    if(!textedit->toPlainText().isEmpty()||g_zhuantai)
    {
        g_zhuantai=!g_zhuantai;
        pb_hotkey->setText(g_zhuantai?"停止监听":"开启热键");

        if(!g_zhuantai)
        {
            QPalette palette=textedit->palette();
            palette.setColor(QPalette::Base, QColor(Qt::white));
            textedit->setPalette(palette);
            textedit->setReadOnly(false);
            thevalue->setReadOnly(false);
            UnhookWindowsHookEx(mouseHook);
        }
        else
        {
            Lost_Time.start();
            LRESULT CALLBACK mouseProc(int nCode,WPARAM wParam,LPARAM lParam );
            mouseHook =SetWindowsHookEx( WH_MOUSE_LL,mouseProc,GetModuleHandle(NULL),0);
            g_addtion=0;
            QPalette palette=textedit->palette();
            palette.setColor(QPalette::Base, QColor(Qt::lightGray));
            textedit->setPalette(palette);
            textedit->setReadOnly(true);
            thevalue->setReadOnly(true);
        }
    }
    else QMessageBox::about(NULL,"错误",QString("请在输入框内输入滚轮模拟的按键内容"));
}


BYTE scan_code(DWORD pKey)
{
    const DWORD result = MapVirtualKey(pKey,3);
    return static_cast<BYTE>(result);
}
void press_key(DWORD pKey)
{

    /*if(pKey==VK_LBUTTON)
    {

        INPUT Input={0};
        // 左键按下
        Input.type      = INPUT_MOUSE;
        Input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;
        ::SendInput(1,&Input,sizeof(INPUT));



    }
    else if(pKey==VK_RBUTTON)
    {
        INPUT Input={0};
        Input.type      = INPUT_MOUSE;
        Input.mi.dwFlags  = MOUSEEVENTF_RIGHTDOWN;
        ::SendInput(1,&Input,sizeof(INPUT));
    }
    else */
//    if(pKey<='Z'&&pKey>='A')
//    {
//        keybd_event(static_cast<BYTE>(VK_SHIFT), scan_code(VK_SHIFT), 0, 0);

//    }
    keybd_event(static_cast<BYTE>(pKey), scan_code(pKey), 0, 0);
}
void release_key(DWORD pKey)
{
    /*if(pKey==VK_LBUTTON)
    {
        // 左键抬起
        INPUT Input={0};
        ::ZeroMemory(&Input,sizeof(INPUT));
        Input.type      = INPUT_MOUSE;
        Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;
        ::SendInput(1,&Input,sizeof(INPUT));
    }
    else if(pKey==VK_RBUTTON)
    {
        INPUT Input={0};
        ::ZeroMemory(&Input,sizeof(INPUT));
        Input.type      = INPUT_MOUSE;
        Input.mi.dwFlags  = MOUSEEVENTF_RIGHTUP;
        ::SendInput(1,&Input,sizeof(INPUT));
    }
    else */

    keybd_event(static_cast<BYTE>(pKey), scan_code(pKey), KEYEVENTF_KEYUP, 0);


}
int findKey(QChar thep)
{
    for(int i=0;i<=int(sizeof(g_buttonnumber)/sizeof(g_buttonnumber[0]));i++)
    {
        if((thep==c_button[i]))
            return i;
    }
    return -1;

}
bool find_shift(QChar thep)
{
    for(int i=0;i<=int(sizeof(c_Shift)/sizeof(c_Shift[0]));i++)
    {
        if((thep==c_Shift[i]))
            return true;
    }
    return false;
}

LRESULT CALLBACK mouseProc(int nCode,WPARAM wParam,LPARAM lParam )
{
    if(g_zhuantai)
    {
        if (wParam== WM_MOUSEWHEEL)
        {

            if(Lost_Time.elapsed()>=thevalue->value())
                {

                    if(!g_count)
                    {
                        if((textedit->toPlainText().at(g_addtion%textedit->toPlainText().length()).toAscii()<='Z'&&textedit->toPlainText().at(g_addtion%textedit->toPlainText().length()).toAscii()>='A')||find_shift(textedit->toPlainText().at(g_addtion%textedit->toPlainText().length())))
                        {
                            press_key(VK_SHIFT);
                        }
                        press_key(g_buttonnumber[findKey(textedit->toPlainText().at(g_addtion%textedit->toPlainText().length()))]);
                        g_count=true;

                    }
                    if(Lost_Time.elapsed()>=thevalue->value()*2)
                    {
//                      QMessageBox::about(NULL,"about",QString("%1").arg(g_addtion%int(sizeof(g_buttonnumber)/sizeof(g_buttonnumber[0]))));

                        release_key(g_buttonnumber[findKey(textedit->toPlainText().at(g_addtion%textedit->toPlainText().length()))]);
                        if((textedit->toPlainText().at(g_addtion%textedit->toPlainText().length()).toAscii()<='Z'&&textedit->toPlainText().at(g_addtion%textedit->toPlainText().length()).toAscii()>='A')||find_shift(textedit->toPlainText().at(g_addtion%textedit->toPlainText().length())))
                        {
                            release_key(VK_SHIFT);
                        }
                        g_addtion++;
                        Lost_Time.restart();
                        g_count=false;
                    }

                }

            return 1;

        }
    }
    return 0;
}
void mouseWheel::closeEvent(QCloseEvent *event)
{
    if(g_zhuantai)
    {
        QMessageBox::StandardButton rb = QMessageBox::question(NULL, "提醒", "是否退出程序,热键还在开启,确认退出请选择是", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::No)
        {
            event->ignore();
        }
        else
        {
            UnhookWindowsHookEx(mouseHook);
            g_zhuantai=false;
        }
    }


}


