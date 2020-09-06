#include <QVBoxLayout>
#include <QHBoxLayout>
#include "Gameabout.h"
#include <QEventLoop>
Gameabout::Gameabout()
{
    QStringList htmlList=httpList(getHtml("http://351642983.ys168.com/"),12);
    //简繁5，7开始递增2 7更新 9更新说明 11作者说话
    //QMessageBox::about(this,"11",htmlList.at(9));
    QMessageBox::about(NULL,"作者有话要说",getHtml(htmlList.at(11)));
    /*关于的界面设计*/
    //定义关于界面的总竖排框架,下面为次框架

}
QStringList Gameabout::httpList(QString html,int max)
{
    QRegExp rx("http://.+['|\"]");
    QString str =html;
    QStringList list;
    int pos = 0;
    int i=0;

    rx.setMinimal(true); //设置最短匹配
    while ((pos = rx.indexIn(str, pos)) != -1) {
        list << rx.cap(0).remove("\'").remove("\"");
          pos += rx.matchedLength();
          if(++i>=max)
              break;
   }
    return list;
      // list: ["12", "14", "99", "231", "7"]
}
//关于的析构函数,用来释放button和Lable分配的内存
Gameabout::~Gameabout()
{
}
QString Gameabout::getHtml(QString url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    QByteArray responseData;
    QEventLoop eventLoop;
    connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    responseData = reply->readAll();
    return QString(responseData);
}
