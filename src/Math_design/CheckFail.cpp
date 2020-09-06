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
        //��5��7��ʼ����2 7���� 9����˵�� 11����˵�� 13�޸��б�
        //
        //QMessageBox::about(this,"11",getHtml("https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=eU0rYIgBZkZTmdWe74kNgzBW&client_secret=Tq2Msb3gW6ovzFfKCmjuUf2u3G778Y0P"));
        //QMessageBox::about(this,"11",json.at(0));
        QString temp=getHtml(htmlList.at(13)).replace("\n"," ");
        theversion=temp.split(" ");//����0 2 4��Ϊ���أ���1,3,5Ϊ��������,��7λ����

        //��ʼ���� �����ļ�
        //    QUrl  serviceUrl = QUrl("http://ozcye8ivb.bkt.clouddn.com/VERSION.txt");

        //    avatorManager = new QNetworkAccessManager(this);
        //    //get��ʽ���� ���������post
        //    avatorReply=avatorManager->get(QNetworkRequest(serviceUrl));
        //    connect(avatorReply,SIGNAL(readyRead()),this,SLOT(httpDowload()));//����д��
        //    connect(avatorReply,SIGNAL(finished()),this,SLOT(httpDowloadFinished()));//�������





            QMessageBox message(QMessageBox::NoIcon, "�޸�ȷ��", QString("���Ƿ���Ҫ�޸������ͼƬѹ������").arg(theversion.at(0)).arg(getHtml(htmlList.at(9))), QMessageBox::Yes | QMessageBox::No, NULL);
            if(message.exec() == QMessageBox::Yes)
            {
                QFileInfo fi;
                fi.setFile(QCoreApplication::applicationFilePath());
                QDir file;//�ļ���
                fileStr=QString(QCoreApplication::applicationDirPath());
                //�ж��ļ����Ƿ���� �����ڴ���
                if(!file.exists(fileStr)){
                    file.mkpath(fileStr);
                }
                QDir file1;//�ļ���
                QString fileStr1=QString(QCoreApplication::applicationDirPath()+"/"+existDir);
                //�ж��ļ����Ƿ���� �����ڴ���
                if(!file1.exists(fileStr1)){
                    file1.mkpath(fileStr1);
                }


                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                QVBoxLayout *vl=new QVBoxLayout;
                ll=new QLabel("�����У�");
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
                    ll->setText(QString("������(%1/%2)��").arg(g_thedownload[0]+1).arg(g_thedownload[1]));
                    downloadnext();
                }
                else
                {
                    QMessageBox::about(NULL,"����","�ó����Ѿ�ӵ��ѹ��ͼƬ�������������޸�");
                    QProcess::startDetached(QCoreApplication::applicationFilePath().remove(QString("_")+QString(VERSION)), QStringList());
                    exit(0);
                }
            }
            else
            {

                QMessageBox::about(NULL,"����","�ѳɹ��޸�ͼƬѹ��");
                QProcess::startDetached(QCoreApplication::applicationFilePath().remove(QString("_")+QString(VERSION)), QStringList());
                exit(0);

            }
    }
    else
    {
        QMessageBox::about(NULL,"����",QString("������δ����,����һ����������Ƿ�����,�ٽ����޸�"));
        QProcess::startDetached(QCoreApplication::applicationFilePath().remove(QString("_")+QString(VERSION)), QStringList());
        exit(0);

    }

}

CheckFail::~CheckFail()
{
}


//��Ҫ���ص��ļ�����
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
    ll->setText(QString("������(%1/%2)��").arg(g_thedownload[0]+1).arg(g_thedownload[1])+QString::number(((float)nowdata/pow(1024,changM1(nowdata))),'f',2)+QString(byty1[changM1(nowdata)])+"/"+QString::number(((float)totaldata/pow(1024,changM1(totaldata))),'f',2)+QString(byty1[changM1(totaldata)]));
}

void CheckFail::httpDowload(){
    if(avatorFile){
         avatorFile->write(avatorReply->readAll());
    }
}


//������� �ļ����سɹ�
void CheckFail::httpDowloadFinished(){
    //ˢ���ļ�
    g_thedownload[0]++;
    avatorFile->flush();
    avatorFile->close();


    if(g_thedownload[0]<g_thedownload[1])
    {
        ll->setText(QString("������(%1/%2)��").arg(g_thedownload[0]+1).arg(g_thedownload[1]));
        downloadnext();
    }
    else
    {
        QMessageBox::about(NULL,"����",QString("�޸�ѹ��ͼƬʧ�ܳɹ�,�����ٴδ򿪳��������г���"));
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
        QMessageBox::about(NULL,"����","�ļ�д��ʧ��");
        exit(1);
        close();
        delete avatorFile;
        avatorFile=0;
        return;
    }
    avatorReply=avatorManager->get(QNetworkRequest(serviceUrl));
    connect(avatorReply,SIGNAL(readyRead()),this,SLOT(httpDowload()));//����д��
    connect(avatorReply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(updateProgress(qint64,qint64)));
    connect(avatorReply,SIGNAL(finished()),this,SLOT(httpDowloadFinished()));//�������
}

