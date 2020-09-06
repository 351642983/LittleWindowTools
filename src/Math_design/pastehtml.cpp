#include "pastehtml.h"
#include "ui_pastehtml.h"
#include <QStringList>
bool isNetWorkOnline()
{


    QHostInfo info = QHostInfo::fromName(QString("www.baidu.com"));
    if(info.addresses().isEmpty())
        return false;
    else return true;

}
PasteHtml::PasteHtml(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PasteHtml)
{
    ui->setupUi(this);
    ui->lineEdit->setText("http://");
    g_outLoop=false;
    ui->textEdit->setReadOnly(true);
    ui->pushButton_2->setEnabled(false);
    setWindowTitle("��ҳͼƬ��ȡ");
}

PasteHtml::~PasteHtml()
{
    delete ui;
}
//�жϴ�����
bool isDigitString(const QString& src) {
    const char *s = src.toUtf8().data();
    while(*s && *s>='0' && *s<='9')s++;
    return !bool(*s);
}
void PasteHtml::on_pushButton_clicked()
{
    if(!isNetWorkOnline())
    {
         QMessageBox::about(NULL,"����","�Բ��������豸δ�����޷�ʹ����ҳͼƬ��ȡ����");
         return;
    }
    if(ui->lineEdit_3->text().isEmpty())
    {
        QMessageBox::about(NULL,"����","ͼƬ����·������Ϊ��");
        return;
    }
    if(ui->pushButton_2->isEnabled())
        return;

    QDir *temp = new QDir;
    if(!temp->exists(ui->lineEdit_3->text()))
    {
        QMessageBox::about(NULL,"����","û���ҵ��÷��õ��ļ���λ��");
        return;
    }
    delete temp;

    ui->pushButton_2->setEnabled(true);
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
    ui->pushButton_3->setEnabled(false);
    QString title;
    QStringList sl=httpList(getHtml(ui->lineEdit->text(),title),-1,ui->lineEdit->text());
    //�������ӳ٣����������ԭ��,���������loop
    int g_floor=0,g_max=-1;
    if(isDigitString(ui->lineEdit_2->text()))
    {
        g_max=ui->lineEdit_2->text().toInt();
    }

    for(int i=0;i<sl.length();i++)
    {


        QString theHtml=sl.at(i);
        QStringList temp;
        if(!(theHtml.contains("http://www.w3.org")||theHtml.contains("http://www.cyberpolice.cn/wfjb/")||theHtml.contains(".dtd")||theHtml.contains(".js")))
        {
            temp=httpList(getHtml(theHtml,title),-1,ui->lineEdit->text());
            ++g_floor;
        }
        else continue;

        QString qsTemp;
        ui->textEdit->append(title+":"+theHtml+" ����:"+qsTemp.sprintf("%d",g_floor));


//        for(int j=0;j<temp.length();j++)
//        {
//            if(g_max!=-1)
//            {
//                if(g_floor>=g_max)
//                    continue;
//            }
//            QString stemp=temp.at(j);
//            sl.append(stemp);
//            ui->textEdit->append(title+":"+temp.at(j)+" ����:"+qsTemp.sprintf("%d",g_floor));
//            if(g_outLoop)
//            {
//                break;
//            }
//        }
//        --g_floor;
//        if(g_outLoop)
//        {
//            g_outLoop=false;
//            sl.clear();
//            break;
//        }


        //�����
        //�����ļ�֮ǰ���ڱ��ش���һ���ļ�
        g_downloadFinish=false;

        QUrl  serviceUrl = QUrl(sl.at(i));
        QFileInfo fi;
        fi.setFile(serviceUrl.path());
        QString fileName=ui->lineEdit_3->text()+"/"+fi.fileName();
        avatorFile=new QFile(fileName);
        //avatorFile->setFileName(fileStr+"/"+fileinfo.fileName());
        if(!avatorFile->open(QIODevice::WriteOnly)){
            QMessageBox::about(NULL,"����","�ļ�д��ʧ��");
            close();
            delete avatorFile;
            avatorFile=0;
            return;
        }
        avatorManager = new QNetworkAccessManager(this);
        avatorReply=avatorManager->get(QNetworkRequest(serviceUrl));
        connect(avatorReply,SIGNAL(readyRead()),this,SLOT(httpDowload()));//����д��
        //connect(avatorReply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(updateProgress(qint64,qint64)));
        connect(avatorReply,SIGNAL(finished()),this,SLOT(httpDowloadFinished()));//�������
        while(!g_downloadFinish)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        if(g_outLoop)
        {
            g_outLoop=false;
            sl.clear();
            break;
        }

    }
    ui->pushButton_2->setEnabled(false);
    ui->lineEdit_2->setReadOnly(false);
    ui->lineEdit_3->setReadOnly(false);
    ui->pushButton_3->setEnabled(true);
    ui->textEdit->append("==================��������==================");
}
//������
void PasteHtml::httpDowload(){
    if(avatorFile){
         avatorFile->write(avatorReply->readAll());
    }
}
//������� �ļ����سɹ�
void PasteHtml::httpDowloadFinished(){
    //ˢ���ļ�
    avatorFile->flush();
    avatorFile->close();

    ui->textEdit->append("�������");
    g_downloadFinish=true;
}


QStringList PasteHtml::httpList(QString html,int max,QString pointHtml)
{
    QRegExp rx("((src|href)=\"((/)|(http://)))(.+)((\\.jpg)|(\\.gif)|(\\.jpeg)|(\\.png))['\")\f\n\r\t\v <]");
    QString str =html;
    QStringList list;
    int pos = 0;
    int i=0;

    rx.setMinimal(true); //�������ƥ��
    while ((pos = rx.indexIn(str, pos)) != -1) {
        QString it= rx.cap(0).remove("\'").remove("\"").remove(")").remove(" ").remove("<").remove("\n");
        for(int f=it.length()-1;f>=0;f--)
        {
            if(it.at(f)=='='||it.at(f)=='(')
            {
                it=it.right(it.length()-f);
                break;
            }
        }
        it.remove("=").remove("(");
        if(!it.contains("http://"))
        {
            if(it.length()>4)
            {
                if(it.contains(".com")){
                    it=("http://")+it;
                }
                else
                {
                    it=pointHtml+it;
                }
            }
            else continue;
        }
        if(!list.contains(it))
            list<<it;


          pos += rx.matchedLength();
          if(max!=-1)
          {
              if(++i>=max)
                  break;
          }
    }



    return list;
      // list: ["12", "14", "99", "231", "7"]
}

bool PasteHtml::isNetWorkOnline()
{


    QHostInfo info = QHostInfo::fromName(QString("www.baidu.com"));
    if(info.addresses().isEmpty())
        return false;
    else return true;

}

QString PasteHtml::getHtml(QString url,QString &title)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    QByteArray responseData;
    QEventLoop eventLoop;
    connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    responseData = reply->readAll();

    QRegExp rx("<title>.*</title>");
    int pos = 0;
    rx.setMinimal(true); //�������ƥ��
    if((pos = rx.indexIn(QString::fromUtf8(responseData), pos)) != -1) {
        title=rx.cap(0).remove("<title>").remove("</title>");

          pos += rx.matchedLength();
    }
    return QString::fromUtf8(responseData);
}

void PasteHtml::on_pushButton_2_clicked()
{
    g_outLoop=!g_outLoop;
    ui->textEdit->append("ֹͣ��ȡ");
    ui->pushButton_2->setEnabled(false);
    ui->lineEdit_2->setReadOnly(false);
}

void PasteHtml::on_pushButton_3_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, QString::fromUtf8("�ļ���"),
                                                    ui->lineEdit_3->text(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
            if(dir.length() == 0) {
                    //ʵ�ֵ����Ĺ���QMessageBox::information(NULL, QString::fromUtf8("ע��"), QString::fromUtf8("��û��ѡ���κ��ļ���."));
            } else {
        //д��UTF-8���֣�����
                    ui->lineEdit_3->setText(dir);
            }
}
