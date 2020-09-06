#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCoreApplication>
#include <QProcess>

#include "changece.h"

changece::changece(QWidget *parent):
    QWidget(parent)
{
    QVBoxLayout *mainlayout=new QVBoxLayout;
    QHBoxLayout *vlayout[2];
    vlayout[0]=new QHBoxLayout;
    vlayout[1]=new QHBoxLayout;
    word=new QLabel("ѡ������Ҫͳ����Ϣ���ļ��У�");
    button[0]=new QPushButton("ѡ��");
    button[1]=new QPushButton("����ͳ��");
    button[2]=new QPushButton("���ضԻ���");
    linee=new QLineEdit;
    texte=new QTextEdit;
    texte->setReadOnly(true);
    vlayout[0]->addWidget(word);
    vlayout[0]->addStretch();
    mainlayout->addLayout(vlayout[0]);
    vlayout[1]->addWidget(linee);
    vlayout[1]->addWidget(button[0]);
    mainlayout->addLayout(vlayout[1]);
    mainlayout->addWidget(texte);
    mainlayout->addWidget(button[1]);
    mainlayout->addWidget(button[2]);

    setLayout(mainlayout);

    setWindowTitle("���ļ���Ϣͳ�ƹ���");
    setFixedSize(500,600);
    setWindowFlags(Qt::WindowCloseButtonHint);
    connect(button[0],SIGNAL(clicked()),this,SLOT(selectDir()));
    connect(button[1],SIGNAL(clicked()),this,SLOT(showtext()));
    connect(button[2],SIGNAL(clicked()),this,SLOT(handleclose()));

    infoshow+="�������:";
    textshow();

}
changece::~changece()
{

}

void changece::selectDir()
{
    QString dir = QFileDialog::getExistingDirectory(this, QString("�����ļ���ѡ��"),
                                                    linee->text(),
                                            QFileDialog::ShowDirsOnly
                                            | QFileDialog::DontResolveSymlinks);
    if(dir.length() == 0) {
            //QMessageBox::information(NULL, QString("ע��"), QString("��û��ѡ���κ��ļ���."));
    } else {
            linee->setText(dir);
            infoshow+="��ѡ����"+dir+"��Ϊ����ͳ���ļ����͵�Ŀ¼";
            textshow();

    }
}

void changece::handleclose()
{
    QProcess::startDetached(QCoreApplication::applicationFilePath(), QStringList());
    exit(0);
}

void changece::showtext()
{
    if(linee->text().length()==0)
    {
        QMessageBox::information(NULL, QString("ע��"), QString("��ѡ��һ��Ŀ¼��ִ�в���."));
        infoshow+="��������û��ѡ����Ҫͳ���ļ����ļ�Ŀ¼";
        textshow();
    }
    else{
        QDir *dir=new QDir(linee->text());
        QList<QFileInfo> *fileinfo=new QList<QFileInfo>(dir->entryInfoList());
        int countnum=fileinfo->count();
        infoshow+=QString("ɨ����Ϣ���£�\n��Ŀ¼���ܹ���%1").arg(countnum-2)+"���ļ�";
        textshow();
        QStringList sl;
        QList<int> thenum;
        bool g_throughdown=false;
        for(int i=0;i<countnum;i++)
        {
            g_throughdown=false;
            if(sl.count()!=0)
            {
                for(int j=0;j<sl.count();j++)
                {
                    if(fileinfo->at(i).suffix()==sl.at(j))
                    {
                        g_throughdown=true;
                        thenum.replace(j,thenum.at(j)+1);
                        break;
                    }
                }
                if(!g_throughdown)
                {
                    sl<<fileinfo->at(i).suffix();
                    thenum<<1;
                }
            }
            else
            {
                sl<<fileinfo->at(i).suffix();
                thenum<<1;
            }
        }
        infoshow+=QString("���ļ����й���%1�����͵��ļ����ļ����������£�\n").arg(sl.count()-1);
        for(int z=0;z<sl.count();z++)
        {
            if(z!=0)
                infoshow+=sl.at(z)+QString("���͵��ļ���%1").arg(thenum.at(z))+"���ļ�\n";
        }
        infoshow+="\n���ļ�����Ϣͳ�ƽ���";
        textshow();


    }
}


void changece::textshow()
{
    infoshow+="\n\n";
    texte->setText(infoshow);
    QTextCursor cursor =texte->textCursor();
    cursor.movePosition(QTextCursor::End);
    texte->setTextCursor(cursor);

}


