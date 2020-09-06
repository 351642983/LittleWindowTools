#include <QProcess>
#include <QTime>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextCodec>
#include <QTextStream>
#include <QApplication>
#include "CheckFail.h"
#include "math.h"
const char *byty1[4]=
{
    "B",
    "KB",
    "MB",
    "GB"
};



CheckFail::CheckFail(QWidget *parent)
    :QWidget(parent)
{
    if(isNetWorkOnline())
    {
        existDir="imageformats";
        QStringList htmlList=httpList(getHtml("http://351642983.ys168.com/"),14);
        //简繁5，7开始递增2 7更新 9更新说明 11作者说话 13修复列表
        //
        //QMessageBox::about(this,"11",getHtml("https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=eU0rYIgBZkZTmdWe74kNgzBW&client_secret=Tq2Msb3gW6ovzFfKCmjuUf2u3G778Y0P"));
        //QMessageBox::about(this,"11",json.at(0));
        QString temp=getHtml(htmlList.at(13)).replace("\n"," ");
        theversion=temp.split(" ");//假设0 2 4均为下载，则1,3,5为下载类型,故7位长度

        //开始请求 下载文件
        //    QUrl  serviceUrl = QUrl("http://ozcye8ivb.bkt.clouddn.com/VERSION.txt");

        //    avatorManager = new QNetworkAccessManager(this);
        //    //get方式请求 如需加密用post
        //    avatorReply=avatorManager->get(QNetworkRequest(serviceUrl));
        //    connect(avatorReply,SIGNAL(readyRead()),this,SLOT(httpDowload()));//数据写入
        //    connect(avatorReply,SIGNAL(finished()),this,SLOT(httpDowloadFinished()));//请求完成





            QMessageBox message(QMessageBox::NoIcon, "修复确认", QString("你是否想要修复程序的图片压缩功能").arg(theversion.at(0)).arg(getHtml(htmlList.at(9))), QMessageBox::Yes | QMessageBox::No, NULL);
            if(message.exec() == QMessageBox::Yes)
            {
                QFileInfo fi;
                fi.setFile(QCoreApplication::applicationFilePath());
                QDir file;//文件夹
                fileStr=QString(QCoreApplication::applicationDirPath());
                //判断文件夹是否存在 不存在创建
                if(!file.exists(fileStr)){
                    file.mkpath(fileStr);
                }
                QDir file1;//文件夹
                QString fileStr1=QString(QCoreApplication::applicationDirPath()+"/"+existDir);
                //判断文件夹是否存在 不存在创建
                if(!file1.exists(fileStr1)){
                    file1.mkpath(fileStr1);
                }


                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                QVBoxLayout *vl=new QVBoxLayout;
                ll=new QLabel("下载中：");
                bar=new QProgressBar;
                vl->addWidget(ll);
                vl->addWidget(bar);
                setLayout(vl);
                setFixedSize(sizeHint().width()+200,sizeHint().height());
                show();


                analyzeList=DownloadAnalyze(theversion);
                 //QMessageBox::about(NULL,"D",theversion.at(analyzeList.at(g_thedownload[0])));
                if(analyzeList.size()>0)
                {
                    g_thedownload[1]=analyzeList.count();
                    g_thedownload[0]=0;
                    bar->setValue(0);
                    //QMessageBox::about(NULL,"D",theversion.at(analyzeList.at(g_thedownload[0])));


                    avatorManager = new QNetworkAccessManager(this);
                    ll->setText(QString("下载中(%1/%2)：").arg(g_thedownload[0]+1).arg(g_thedownload[1]));
                    downloadnext();
                }
                else
                {
                    QMessageBox::about(NULL,"提醒","该程序已经拥有压缩图片插件，无需继续修复");
                    QProcess::startDetached(QCoreApplication::applicationFilePath().remove(QString("_")+QString(VERSION)), QStringList());
                    exit(0);
                }
            }
            else
            {

                QMessageBox::about(NULL,"提醒","已成功修复图片压缩");
                QProcess::startDetached(QCoreApplication::applicationFilePath().remove(QString("_")+QString(VERSION)), QStringList());
                exit(0);

            }
    }
    else
    {
        QMessageBox::about(NULL,"提醒",QString("网络尚未连接,请检查一下你的网络是否连接,再进行修复"));
        QProcess::startDetached(QCoreApplication::applicationFilePath().remove(QString("_")+QString(VERSION)), QStringList());
        exit(0);

    }

}

CheckFail::~CheckFail()
{
}


//需要下载的文件分析
QList<int> CheckFail::DownloadAnalyze(QStringList infoList)
{
    QList<int> numList;
    for(int i=1;i<infoList.length();i+=2)
    {
        QUrl serviceUrl=QUrl(infoList.at(i-1));
        QFileInfo fi(serviceUrl.path());
        QFile fs(QApplication::applicationDirPath()+"/"+existDir+"/"+fi.fileName());

        if(infoList.at(i)=="0")
        {
            if(!fs.exists())
                numList<<i-1;
        }
        else
        {
            //QMessageBox::about(NULL,"D",infoList.at(i-1));
            numList<<i-1;
        }
    }
    return numList;
}

QStringList CheckFail::httpList(QString html,int max)
{
    QRegExp rx("((http://)|(ftp://)).+['|\"]");
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

bool CheckFail::isNetWorkOnline()
{


    QHostInfo info = QHostInfo::fromName(QString("www.baidu.com"));
    if(info.addresses().isEmpty())
        return false;
    else return true;

}

QString CheckFail::getHtml(QString url)
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
int changM1(qint64 x)
{
    int g_m=0;
    float type=(float)x;
    while((type/=1024)>1)
    {
        g_m++;
    }
    return g_m;

}



void CheckFail::updateProgress(qint64 nowdata, qint64 totaldata)
{
    bar->setMaximum(totaldata);
    bar->setValue(nowdata);
    ll->setText(QString("下载中(%1/%2)：").arg(g_thedownload[0]+1).arg(g_thedownload[1])+QString::number(((float)nowdata/pow(1024,changM1(nowdata))),'f',2)+QString(byty1[changM1(nowdata)])+"/"+QString::number(((float)totaldata/pow(1024,changM1(totaldata))),'f',2)+QString(byty1[changM1(totaldata)]));
}

void CheckFail::httpDowload(){
    if(avatorFile){
         avatorFile->write(avatorReply->readAll());
    }
}


//请求完成 文件下载成功
void CheckFail::httpDowloadFinished(){
    //刷新文件
    g_thedownload[0]++;
    avatorFile->flush();
    avatorFile->close();


    if(g_thedownload[0]<g_thedownload[1])
    {
        ll->setText(QString("下载中(%1/%2)：").arg(g_thedownload[0]+1).arg(g_thedownload[1]));
        downloadnext();
    }
    else
    {
        QMessageBox::about(NULL,"提醒",QString("修复压缩图片失败成功,请您再次打开程序以运行程序"));
        //QProcess::startDetached(QCoreApplication::applicationFilePath().remove(QString("_")+QString(VERSION)), QStringList());
        QTime dieTime = QTime::currentTime().addMSecs(100);
        while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        QFileInfo fi;
        fi.setFile(QCoreApplication::applicationFilePath());
        QString fileName=fileStr+QString("/%1.exe").arg(fi.completeBaseName());
        QProcess::startDetached(fileName, QStringList());
        exit(0);
    }

}
void CheckFail::downloadnext()
{
    QUrl  serviceUrl = QUrl(theversion.at(analyzeList.at(g_thedownload[0])));
    fileinfo.setFile(serviceUrl.path());
    if(avatorFile)
        avatorFile->setFileName(fileStr+"/"+existDir+"/"+fileinfo.fileName());
    else avatorFile=new QFile(fileStr+"/"+existDir+"/"+fileinfo.fileName());
    if(!avatorFile->open(QIODevice::WriteOnly)){
        QMessageBox::about(NULL,"错误","文件写入失败");
        exit(1);
        close();
        delete avatorFile;
        avatorFile=0;
        return;
    }
    avatorReply=avatorManager->get(QNetworkRequest(serviceUrl));
    connect(avatorReply,SIGNAL(readyRead()),this,SLOT(httpDowload()));//数据写入
    connect(avatorReply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(updateProgress(qint64,qint64)));
    connect(avatorReply,SIGNAL(finished()),this,SLOT(httpDowloadFinished()));//请求完成
}

