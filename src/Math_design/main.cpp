#include <QApplication>
#include <QTextCodec>
#include <QSettings>

#include "widget.h"
//#include "windows.h"
//#include "tchar.h"
int main(int argc, char *argv[])
{
//win10兼容出错,换成win7兼容
    //const wchar_t * encodedName = reinterpret_cast<const wchar_t *>(QCoreApplication::applicationFilePath().replace("/","\\").utf16());


//    Windows 95                                                       对应WIN95
//    Windows 98 / Windows Me                             对应WIN98
//    Windows NT 4.0 (Service Pack 5)                  对应NT4SP5
//    Windows 2000                                                   对应WIN2000
//    Windows XP                                                       对应WINXP
//    Windows XP (Service Pack 2)                         对应WINXPSP2
//    Windows XP (Service Pack 3)                         对应WINXPSP3
//    Windows Server 2003 (Service Pack 1)        对应WINSRV03SP1
//    Windows Server 2008 (Service Pack 1)        对应WINSRV08SP1
//    Windows Vista                                                   对应VISTARTM
//    Windows Vista (Service Pack 1)                     对应VISTASP1
//    Windows Vista (Service Pack 2)                     对应VISTASP2
//    Windows 7                                                          对应WIN7RTM


//    QSettings *reg=new QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers",QSettings::NativeFormat);
//    const QString apt=QCoreApplication::applicationFilePath().replace("/","\\");
//    reg->setValue(apt,"WIN2000");


    //将显示编码设置为GBK,以防止乱码的产生
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());


    QApplication a(argc, argv);

    //将兼容模式设置为win7,因为编译使用的QT版本较老,必须兼容才可以稳定运行
//    HKEY hKey;
//    LPCTSTR strSubKey = L"Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers";
//    long lRet = ::RegOpenKeyEx( HKEY_CURRENT_USER, strSubKey, 0, KEY_WRITE, &hKey );
//    if ( lRet == ERROR_SUCCESS )
    //    {
//        const size_t cSize = strlen(a.applicationFilePath().replace("/","\\").toLatin1().data())+1;
//        wchar_t* wc = new wchar_t[cSize];
//        mbstowcs (wc, a.applicationFilePath().replace("/","\\").toLatin1().data(), cSize);
//        lRet  = ::RegSetValueEx( hKey,wc, NULL, REG_SZ, (LPBYTE)(L"WIN7RTM"),13);
//        RegCloseKey( hKey );
//    }

    Widget w;
    a.setStyleSheet("QMenu{ background-color: rgb(255, 255, 255); border: 1px solid rgb(125, 125, 125); /*整个菜单区域的边框粗细、样式、颜色*/ \
                    border-radius: 5px; }\
                    QMenu::item { background-color: transparent;color:gray; \
                           padding:3px 20px;/*设置菜单项文字上下和左右的内边距，效果就是菜单中的条目左右上下有了间隔*/ \
                           margin:5px 10px;/*设置菜单项的外边距: 长(height) 宽(width)*/ \
                           /*border-bottom:1px solid #DBDBDB;*//*为菜单项之间添加横线间隔*/\
                                color:gray}\
                    QMenu::item:selected { background-color: lightblue;/*这一句是设置菜单项鼠标经过选中的样式*/ }\
            QLineEdit{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid gray;}\
            QLineEdit:hover{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid rgb(70,200,50);}\
            QTextEdit{border-width:1px;border-radius:4px;color:black;border:1px solid gray;}\
            QTextEdit:hover{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid rgb(70,200,50);}\
            QListWidget{border-width:1px;font-size:12px;color:black;border:1px solid #ccc;}\
            QListWidget:hover{border-width:1px;font-size:12px;color:black;border:1px solid lightblue;}\
            QListWidget::item:hover{color:red;}\
            QPushButton{font-family:幼圆;}\
            QLabel:hover{color:green}\
                         "

);

    return a.exec();
}
