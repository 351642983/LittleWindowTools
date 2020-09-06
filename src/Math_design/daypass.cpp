#include "daypass.h"
#include <QMessageBox>
#include <QEventLoop>
#include <QVBoxLayout>
#include <QTextCodec>
#include <QHostInfo>
daypass::daypass(QWidget *parent):
    QWidget(parent)

{
    if(isNetWorkOnline())
    {
        QString str=getHtml("https://meiriyiwen.com/");
        textedit=new QTextEdit;
        textedit->setReadOnly(1);
        QVBoxLayout *vlayout=new QVBoxLayout;
        vlayout->addWidget(textedit);
        setLayout(vlayout);
        //str.remove(0,100);
        textedit->setHtml(str);
        //textedit->setText(str);
        textedit->setStyleSheet("QTextEdit{font-family:幼圆;}");
        setWindowState(Qt::WindowMaximized);
        //setWindowTitle("每日一文");
    }
    else
    {
        QMessageBox::about(NULL, "注意", "网络未连接");
        hide();
        close();
    }
}
daypass::~daypass()
{

}

bool daypass::isNetWorkOnline()
{
    QHostInfo info = QHostInfo::fromName(QString("www.baidu.com"));
    if(info.addresses().isEmpty())
        return false;
    else return true;

}
QString daypass::getHtml(QString url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    QByteArray responseData;
    QEventLoop eventLoop;
    connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    responseData = reply->readAll();
    QString str = QTextCodec::codecForName("utf-8")->toUnicode(responseData);//把gb2312编码转换成unicode
    QStringList lists=str.split("<");
    for(int i=0;i<lists.count();i++)
    {
//        if(lists.at(i).contains("href=")||lists.at(i).contains("id=\"menu-")||lists.at(i).contains("admin%ihx.cc")||lists.at(i).contains("友情链接")||lists.at(i).contains("|")||lists.at(i).contains("img"))
//        {
//            lists.removeAt(i);
//        }
        if(lists.at(i).contains("article_text"))
        {
            lists.replaceInStrings("article_text","article_text\" style=\"font-size:40px");

        }
    }
    str=lists.join("<");
    return str;
}
