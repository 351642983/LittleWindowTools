#include <QApplication>
#include <QTextCodec>
#include <QSettings>

#include "widget.h"
//#include "windows.h"
//#include "tchar.h"
int main(int argc, char *argv[])
{
//win10���ݳ���,����win7����
    //const wchar_t * encodedName = reinterpret_cast<const wchar_t *>(QCoreApplication::applicationFilePath().replace("/","\\").utf16());


//    Windows 95                                                       ��ӦWIN95
//    Windows 98 / Windows Me                             ��ӦWIN98
//    Windows NT 4.0 (Service Pack 5)                  ��ӦNT4SP5
//    Windows 2000                                                   ��ӦWIN2000
//    Windows XP                                                       ��ӦWINXP
//    Windows XP (Service Pack 2)                         ��ӦWINXPSP2
//    Windows XP (Service Pack 3)                         ��ӦWINXPSP3
//    Windows Server 2003 (Service Pack 1)        ��ӦWINSRV03SP1
//    Windows Server 2008 (Service Pack 1)        ��ӦWINSRV08SP1
//    Windows Vista                                                   ��ӦVISTARTM
//    Windows Vista (Service Pack 1)                     ��ӦVISTASP1
//    Windows Vista (Service Pack 2)                     ��ӦVISTASP2
//    Windows 7                                                          ��ӦWIN7RTM


//    QSettings *reg=new QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers",QSettings::NativeFormat);
//    const QString apt=QCoreApplication::applicationFilePath().replace("/","\\");
//    reg->setValue(apt,"WIN2000");


    //����ʾ��������ΪGBK,�Է�ֹ����Ĳ���
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());


    QApplication a(argc, argv);

    //������ģʽ����Ϊwin7,��Ϊ����ʹ�õ�QT�汾����,������ݲſ����ȶ�����
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
    a.setStyleSheet("QMenu{ background-color: rgb(255, 255, 255); border: 1px solid rgb(125, 125, 125); /*�����˵�����ı߿��ϸ����ʽ����ɫ*/ \
                    border-radius: 5px; }\
                    QMenu::item { background-color: transparent;color:gray; \
                           padding:3px 20px;/*���ò˵����������º����ҵ��ڱ߾࣬Ч�����ǲ˵��е���Ŀ�����������˼��*/ \
                           margin:5px 10px;/*���ò˵������߾�: ��(height) ��(width)*/ \
                           /*border-bottom:1px solid #DBDBDB;*//*Ϊ�˵���֮����Ӻ��߼��*/\
                                color:gray}\
                    QMenu::item:selected { background-color: lightblue;/*��һ�������ò˵�����꾭��ѡ�е���ʽ*/ }\
            QLineEdit{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid gray;}\
            QLineEdit:hover{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid rgb(70,200,50);}\
            QTextEdit{border-width:1px;border-radius:4px;color:black;border:1px solid gray;}\
            QTextEdit:hover{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid rgb(70,200,50);}\
            QListWidget{border-width:1px;font-size:12px;color:black;border:1px solid #ccc;}\
            QListWidget:hover{border-width:1px;font-size:12px;color:black;border:1px solid lightblue;}\
            QListWidget::item:hover{color:red;}\
            QPushButton{font-family:��Բ;}\
            QLabel:hover{color:green}\
                         "

);

    return a.exec();
}
