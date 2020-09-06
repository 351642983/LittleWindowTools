#include <QVBoxLayout>
#include <QHBoxLayout>
#include "Gameabout.h"
#include <QEventLoop>
Gameabout::Gameabout()
{
    QStringList htmlList=httpList(getHtml("http://351642983.ys168.com/"),12);
    //��5��7��ʼ����2 7���� 9����˵�� 11����˵��
    //QMessageBox::about(this,"11",htmlList.at(9));
    QMessageBox::about(NULL,"�����л�Ҫ˵",getHtml(htmlList.at(11)));
    /*���ڵĽ������*/
    //������ڽ���������ſ��,����Ϊ�ο��

}
QStringList Gameabout::httpList(QString html,int max)
{
    QRegExp rx("http://.+['|\"]");
    QString str =html;
    QStringList list;
    int pos = 0;
    int i=0;

    rx.setMinimal(true); //�������ƥ��
    while ((pos = rx.indexIn(str, pos)) != -1) {
        list << rx.cap(0).remove("\'").remove("\"");
          pos += rx.matchedLength();
          if(++i>=max)
              break;
   }
    return list;
      // list: ["12", "14", "99", "231", "7"]
}
//���ڵ���������,�����ͷ�button��Lable������ڴ�
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
