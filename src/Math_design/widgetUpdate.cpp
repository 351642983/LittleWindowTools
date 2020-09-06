#include "widgetUpdate.h"
#include "ui_widget.h"




WidgetUpdate::WidgetUpdate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //ui->textEdit->append(getText());
    tray=new QSystemTrayIcon;
    avatorManager=0;
    avatorFile=0;
    avatorReply=0;
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(startCheck()));
    tray->setToolTip(QString("ÿ�ո���"));
    tray->setIcon(QApplication::style()->standardIcon(QStyle::SP_FileDialogDetailedView));
    //tray->setContextMenu(menu);
    connect(tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(showHide(QSystemTrayIcon::ActivationReason)));

    //emit startDownload();
}

void WidgetUpdate::showHide(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
//        case QSystemmainwindow->trayIcon::Trigger:
//            showMessage("����");
//        break;
        case QSystemTrayIcon::DoubleClick:
            show();
            activateWindow();
            tray->hide();
        break;
//        case QSystemTrayIcon::MiddleClick:
//            showMessage("���õ���������껹�ǹ�����갡");
//        break;
        default:
        ;
    }
}
WidgetUpdate::~WidgetUpdate()
{
    delete ui;
}
void WidgetUpdate::startCheck()
{

    if(ui->pushButton->text()=="����")
    {
        ui->pushButton->setText("ֹͣ����");
        g_timerid=startTimer(1000);
    }
    else
    {
        ui->pushButton->setText("����");
        killTimer(g_timerid);
    }

}

void WidgetUpdate::timerEvent(QTimerEvent *e)
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    current_date =current_date_time.toString("yyyy.MM.dd");
    QStringList ltemp=getText().split("\n");
    if(current_date!=ltemp.at(0))
    {

        QString temp=ltemp.at(0);
        ltemp.replace(0,temp.left(10));
        //emit startDownload();
        ui->textEdit->append("��������");
        ui->textEdit->append(current_date);
        QFile *a=new QFile(QCoreApplication::applicationDirPath()+"/QInfo.txt");
        if(a->open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate))
        {
            //ui->textEdit->append("�򿪳ɹ�");
            QTextStream in(a);

            ltemp.replace(0,current_date);
            for(int i=0;i<ltemp.length();i++)
            {
                in<<ltemp.at(i);
                if(i!=ltemp.length()-1)
                    in<<"\n";
            }
            a->flush();
        }
        a->close();
        emit startDownload();
    }
}

const char *bytyTemp[4]=
{
    "B",
    "KB",
    "MB",
    "GB"
};
QString WidgetUpdate::getText()
{
    QFile *a=new QFile(QCoreApplication::applicationDirPath()+"/QInfo.txt");
    if(a->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString b= a->readAll();
        a->close();
        delete a;
        return b;
    }
    else
    {
        ui->textEdit->append("�����ļ���ʧ��");
    }
    a->close();
    delete a;
    return NULL;
}

void WidgetUpdate::startDownload()
{
    if(isNetWorkOnline())
    {
        theversion=getText().split("\n");


        //��ʼ���� �����ļ�
        //    QUrl  serviceUrl = QUrl("http://ozcye8ivb.bkt.clouddn.com/VERSION.txt");
        //    avatorManager = new QNetworkAccessManager(this);
        //    //get��ʽ���� ���������post
        //    avatorReply=avatorManager->get(QNetworkRequest(serviceUrl));
        //    connect(avatorReply,SIGNAL(readyRead()),this,SLOT(httpDowload()));//����д��
        //    connect(avatorReply,SIGNAL(finished()),this,SLOT(httpDowloadFinished()));//�������




        QFileInfo fi;
        fi.setFile(QCoreApplication::applicationFilePath());
        QDir file;//�ļ���
        fileStr=QString(QCoreApplication::applicationDirPath());
        //�ж��ļ����Ƿ���� �����ڴ���
        if(!file.exists(fileStr)){
            file.mkpath(fileStr);
        }


        QTime dieTime = QTime::currentTime().addMSecs(100);
        while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        //rename(QCoreApplication::applicationFilePath().toStdString().c_str(),QString(fileStr+QString("/%1_%2.exe").arg(fi.completeBaseName()).arg(VERSION)).toStdString().c_str());
//        QVBoxLayout *vl=new QVBoxLayout;

        g_thedownload[1]=theversion.count()-1;
        g_thedownload[0]=0;
//        ll=new QLabel(QString("������(%1/%2)��").arg(g_thedownload[0]+1).arg(g_thedownload[1]));

//      QDialog *dg=new QDialog();
//        bar=new QProgressBar;
//        vl->addWidgetUpdate(ll);
//        vl->addWidgetUpdate(bar);
//        dg->setLayout(vl);
//        dg->setFixedSize(sizeHint().width()+200,sizeHint().height());
//        dg->show();
//        bar->setValue(0);
        if(avatorManager)
            delete avatorManager;
        avatorManager = new QNetworkAccessManager(this);
        //QMessageBox::about(NULL,"����",fileStr+"/"+fileinfo.fileName());
        downloadnext();



        //avatorFile=0;   //���罫ָ������Ϊ0�Ļ�������ֱ���

    }
    else
    {
        ui->textEdit->append("����:������δ����,����һ����������Ƿ�����,�ٽ��м�����\n");
        QProcess::startDetached(QCoreApplication::applicationFilePath(), QStringList());
        exit(0);

    }

}
bool WidgetUpdate::isNetWorkOnline()
{


    QHostInfo info = QHostInfo::fromName(QString("www.baidu.com"));
    if(info.addresses().isEmpty())
        return false;
    else return true;

}

QString WidgetUpdate::getHtml(QString url)
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


int changMTemp(qint64 x)
{
    int g_m=0;
    float type=(float)x;
    while((type/=1024)>1)
    {
        g_m++;
    }
    return g_m;

}



//void WidgetUpdate::updateProgress(qint64 nowdata, qint64 totaldata)
//{
//    bar->setMaximum(totaldata);
//    bar->setValue(nowdata);
//    ll->setText(QString("������(%1/%2)��").arg(g_thedownload[0]+1).arg(g_thedownload[1])+QString::number(((float)nowdata/pow(1024,changMTemp(nowdata))),'f',2)+QString(bytyTemp[changMTemp(nowdata)])+"/"+QString::number(((float)totaldata/pow(1024,changMTemp(totaldata))),'f',2)+QString(bytyTemp[changMTemp(totaldata)]));
//}

void WidgetUpdate::httpDowload(){
    if(avatorFile){
        avatorFile->write(avatorReply->readAll());
    }
}


//������� �ļ����سɹ�
void WidgetUpdate::httpDowloadFinished(){
    //ˢ���ļ�
    g_thedownload[0]++;
    avatorFile->waitForBytesWritten(5 * 1000); //�ȴ��ļ�д�����
    if(0 == avatorFile->size())
        //�˴�����ʧ�ܣ����ٽ����������ز���
        ui->textEdit->append(fileinfo.fileName()+"����ʧ��");
    else
        ui->textEdit->append(fileinfo.fileName()+"���سɹ�");
    avatorFile->flush();
    avatorFile->close();

//    if(g_thedownload[0]==1)
//    {
//        QFileInfo fi;
//        fi.setFile(QCoreApplication::applicationFilePath());
//        QDir file;//�ļ���

//        //�ж��ļ����Ƿ���� �����ڴ���
//        if(!file.exists(fileStr)){
//            file.mkpath(fileStr);
//        }
//        QFile *fs=new QFile(fileStr+"/Mg_RAndOms.TRY");
//        //QMessageBox::about(NULL,"����",fileStr+"/Mg_RAndOms.TRY");

//        QTextCodec *code=QTextCodec::codecForName("UTF-8");
//        fs->open(QIODevice::ReadWrite|QIODevice::Text);
//        QTextStream in(fs);
//        in.setCodec(code);
//        //in<<QString(fileStr+QString("/%1_%2.exe").arg(fi.completeBaseName()).arg(VERSION));
//        fs->close();
//    }
    if(g_thedownload[0]<g_thedownload[1])
    {
        ui->textEdit->append(QString("���ؽ���(%1/%2)��").arg(g_thedownload[0]+1).arg(g_thedownload[1]));
        downloadnext();
    }
    else
    {
        delete avatorFile;
        //delete avatorReply;
        ui->textEdit->append("����:�ļ��������");
//        delete avatorFile;
//        delete avatorManager;
       // QMessageBox::about(NULL,"����",QString("�Ѿ����µ����°汾 %1,�����ڴδ򿪳���").arg(QString(theversion.at(0))));
        //QProcess::startDetached(QCoreApplication::applicationFilePath().remove(QString("_")+QString(VERSION)), QStringList());
//        QTime dieTime = QTime::currentTime().addMSecs(100);
//        while( QTime::currentTime() < dieTime )
//            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//        QFileInfo fi;
//        fi.setFile(QCoreApplication::applicationFilePath());
//        QString fileName=fileStr+QString("/%1_%2.exe").arg(fi.completeBaseName()).arg(theversion.at(0));
//        QProcess::startDetached(fileName, QStringList());
//        exit(1);
//        hide();
//        emit tclose();


    }

}
void WidgetUpdate::downloadnext()
{
    QUrl  serviceUrl = QUrl(theversion.at(g_thedownload[0]+1));
    fileinfo.setFile(serviceUrl.path());
    if(g_thedownload[0]==0)
        avatorFile=new QFile(fileStr+"/"+fileinfo.fileName());
    avatorFile->setFileName(fileStr+"/"+fileinfo.fileName());
    ui->textEdit->append(fileinfo.fileName()+"������");
    if(!avatorFile->open(QIODevice::WriteOnly)){
        ui->textEdit->append("����:�ļ�д��ʧ��");
        //close();
        delete avatorFile;
        avatorFile=0;
        return;
    }
    avatorReply=avatorManager->get(QNetworkRequest(serviceUrl));
    connect(avatorReply,SIGNAL(readyRead()),this,SLOT(httpDowload()));//����д��
    //connect(avatorReply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(updateProgress(qint64,qint64)));
    connect(avatorReply,SIGNAL(finished()),this,SLOT(httpDowloadFinished()));//�������
}

void WidgetUpdate::on_pushButton_2_clicked()
{
    tray->show();
    tray->showMessage("ÿ�ո���","�Ѿ����ص�����");
    hide();
}
