#include <QProcess>
#include <QCoreApplication>
#include "handoption.h"
#include "filelock.h"

filelock::filelock(QWidget *parent):
    QWidget(parent)
{
    QVBoxLayout *vlay=new QVBoxLayout;
    QHBoxLayout *hlay[4];
    for(int i=0;i<4;i++)
            hlay[i]=new QHBoxLayout;
    button[0]=new QPushButton("ѡ��");
    button[1]=new QPushButton("ִ�в���");
    button[2]=new QPushButton("���ضԻ���");

    word[0]=new QLabel("ѡ��Ŀ���ļ�:");
    word[1]=new QLabel("�ļ�ִ�в���:");
    word[2]=new QLabel("���������:");

    line[0]=new QLineEdit;
    line[1]=new QLineEdit;

//    QRegExp regx("[1-9][0-9]+$");
//    QValidator *validator = new QRegExpValidator(regx,line[2] );
//    line[1]->setValidator(validator);

    cbox=new QComboBox;
    cbox->addItem("�ļ�����");
    cbox->addItem("�ļ�����");



    hlay[0]->addStretch();
    hlay[0]->addWidget(word[0]);
    hlay[0]->addWidget(line[0]);
    hlay[0]->addWidget(button[0]);


    hlay[1]->addStretch();
    hlay[1]->addWidget(word[1]);
    hlay[1]->addWidget(cbox);
    cbox->setFixedWidth(130);
    hlay[1]->addStretch();

    hlay[2]->addStretch();
    hlay[2]->addWidget(word[2]);
    hlay[2]->addWidget(line[1]);
    hlay[2]->addStretch();

    //hlay[3]->addStretch();
    hlay[3]->addWidget(button[1]);
    hlay[3]->addWidget(button[2]);
    //hlay[3]->addStretch();



    vlay->addLayout(hlay[0]);
    vlay->addLayout(hlay[2]);
    vlay->addLayout(hlay[1]);
    vlay->addLayout(hlay[3]);
    //vlay->addWidget(button[2]);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::gray);
    setAutoFillBackground(true);
    setPalette(pal);
    setLayout(vlay);
    setFixedSize(sizeHint().width(),sizeHint().height());
    setWindowTitle("�ļ�����");
    show();


    connect(button[0],SIGNAL(clicked()),this,SLOT(slectfile()));
    connect(button[1],SIGNAL(clicked()),this,SLOT(lockhandle()));
    connect(button[2],SIGNAL(clicked()),this,SLOT(handleclose()));

    QDir *temp = new QDir;
    QString theaddress="D:/g_rank";
    if(!temp->exists(theaddress))
    {
        if(!temp->mkdir(theaddress))
        {
               theaddress= "C:/g_rank";
               temp->mkdir(theaddress);
        }
    }
    delete temp;
    QFile fs;
    fs.setFileName(QString("%1/filein.saver").arg(theaddress));
    if(!fs.exists())
    {
        fs.open(QIODevice::ReadWrite|QIODevice::Text);
        fs.close();

    }
    fs.open(QIODevice::ReadOnly|QIODevice::Text);
    QString allline=QString::fromLocal8Bit(fs.readAll());

    line[0]->setText(allline);
    fs.close();




}

filelock::~filelock()
{

}
void filelock::handleclose()
{
    QProcess::startDetached(QCoreApplication::applicationFilePath().remove(QString("_")+QString(VERSION)), QStringList());
    exit(0);
}

void filelock::slectfile()
{


    QFileInfo fileinfo;
    fileinfo=QFileInfo(line[0]->text());
    QString path = QFileDialog::getOpenFileName(NULL, QString("ѡ���ļ�"), (line[0]->text().isEmpty())?line[0]->text():fileinfo.absolutePath(), QString("�����ļ�()"));
    if(path.length() == 0) {
            //QMessageBox::information(NULL, QString("ע��"), QString("��û��ѡ���κ��ļ�."));
    } else {
        line[0]->setText(path);

    }

}

int bitnum(int x)
{
    int num=0;
    float bn=x;
    while(bn>=1)
    {
        bn/=10;
        num++;
    }
    return num;
}

int power(int x,int y)
{
    int b=1;
    for(int i=1;i<=y;i++)
        b*=x;
    return b;

}

int bitvalue(int x,int y)
{
    if(y==1)
        return (x%10);
    else if(y>1) return ((x%power(10,y))-(x%power(10,y-1)))/power(10,y-1);
    return 0;
}


void filelock::lockhandle()
{
    if(!line[0]->text().isEmpty())
    {

            if(!line[1]->text().isEmpty())
            {
                QMessageBox message(QMessageBox::NoIcon, "ע��", QString("���Ƿ���Ҫ��ѡ����ļ���%1������%2�ļ�").arg(line[1]->text()).arg(!cbox->currentIndex()?"����":"����"), QMessageBox::Yes | QMessageBox::No, NULL);
                if(message.exec() == QMessageBox::Yes)
                {

                    QFileInfo fileinfo;
                    fileinfo=QFileInfo(line[0]->text());

                    QDir *temp = new QDir;
                    QString theaddress="D:/g_rank";
                    if(!temp->exists(theaddress))
                    {
                        if(!temp->mkdir(theaddress))
                        {
                            theaddress= "C:/g_rank";
                            temp->mkdir(theaddress);
                        }
                    }
                    delete temp;
                    QFile fs;
                    fs.setFileName(QString("%1/filein.saver").arg(theaddress));
                    fs.open(QIODevice::WriteOnly|QIODevice::Text);
                    if(!fs.exists())
                    {
                        fs.close();
                    }
                    QTextCodec *code=QTextCodec::codecForLocale();
                    fs.open(QIODevice::WriteOnly|QIODevice::Text);
                    QTextStream t(&fs);
                    t.setCodec(code);
                    t<<line[0]->text();

                    if(cbox->currentIndex()==0)
                    {
                        QFile file(line[0]->text());
                        file.open(QIODevice::ReadWrite);

                        //�����㷨
                        QByteArray num,end;
                        num=file.readAll();
                        int i;
                        for(i=0;i<num.count();i++)
                            num[i]=(num[i]^(line[1]->text().at(i%(line[1]->text().size())).unicode()))-1;
                        qsrand(line[1]->text().toInt());
                        int rn=qrand();
                        for(i=0;i<num.count();i++)
                            num[i]=((num[i])^(bitvalue(rn,(i+1)%bitnum(rn)+1)))-1;





                        file.close();
                        QFile infoFile(line[0]->text());
                        if(!infoFile.open(QIODevice::WriteOnly)){
                            return;
                        }


                        infoFile.write(num);
                        infoFile.close();



                        QMessageBox::about(NULL,"����","�ļ����ܲ���ִ�����");
                    }
                    else if(cbox->currentIndex()==1)
                    {

                        QFile file(line[0]->text());
                        file.open(QIODevice::ReadWrite);

                        //�����㷨
                        QByteArray num,end;
                        num=file.readAll();

                        int i;
                        qsrand(line[1]->text().toInt());
                        int rn=qrand();
                        for(i=0;i<num.count();i++)
                            num[i]=((num[i]+1)^(bitvalue(rn,(i+1)%bitnum(rn)+1)));
                        for(i=0;i<num.count();i++)
                            num[i]=(num[i]+1)^(line[1]->text().at(i%(line[1]->text().size())).unicode());


                        file.close();
                        QFile infoFile(line[0]->text());
                        if(!infoFile.open(QIODevice::WriteOnly)){
                            return;
                        }

                        //while(!infoFile.atEnd())
                        infoFile.write(num);
                        infoFile.close();


                        QMessageBox::about(NULL,"����","�ļ����ܲ���ִ�����");
                    }
                    fs.close();
                }
                else
                {
                    QMessageBox::about(NULL,"����","��ȡ�����ļ�ִ�еĲ���");
                }

            }
            else
            {
                QMessageBox::about(NULL,"����","�����������ڽ���ת������");
            }


    }
    else
    {
        QMessageBox::about(NULL,"����","��ѡ��Ҫ������ļ�");
    }
}
