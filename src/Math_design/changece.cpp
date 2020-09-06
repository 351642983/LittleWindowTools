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
    word=new QLabel("选择你需要统计信息的文件夹：");
    button[0]=new QPushButton("选择");
    button[1]=new QPushButton("进行统计");
    button[2]=new QPushButton("返回对话框");
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

    setWindowTitle("简单文件信息统计工具");
    setFixedSize(500,600);
    setWindowFlags(Qt::WindowCloseButtonHint);
    connect(button[0],SIGNAL(clicked()),this,SLOT(selectDir()));
    connect(button[1],SIGNAL(clicked()),this,SLOT(showtext()));
    connect(button[2],SIGNAL(clicked()),this,SLOT(handleclose()));

    infoshow+="输出如下:";
    textshow();

}
changece::~changece()
{

}

void changece::selectDir()
{
    QString dir = QFileDialog::getExistingDirectory(this, QString("放置文件夹选择"),
                                                    linee->text(),
                                            QFileDialog::ShowDirsOnly
                                            | QFileDialog::DontResolveSymlinks);
    if(dir.length() == 0) {
            //QMessageBox::information(NULL, QString("注意"), QString("你没有选择任何文件夹."));
    } else {
            linee->setText(dir);
            infoshow+="你选择了"+dir+"作为你想统计文件类型的目录";
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
        QMessageBox::information(NULL, QString("注意"), QString("请选择一个目录来执行操作."));
        infoshow+="操作错误：没有选择想要统计文件的文件目录";
        textshow();
    }
    else{
        QDir *dir=new QDir(linee->text());
        QList<QFileInfo> *fileinfo=new QList<QFileInfo>(dir->entryInfoList());
        int countnum=fileinfo->count();
        infoshow+=QString("扫描信息如下：\n该目录下总共有%1").arg(countnum-2)+"个文件";
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
        infoshow+=QString("该文件夹中共有%1种类型的文件，文件的类型如下：\n").arg(sl.count()-1);
        for(int z=0;z<sl.count();z++)
        {
            if(z!=0)
                infoshow+=sl.at(z)+QString("类型的文件有%1").arg(thenum.at(z))+"个文件\n";
        }
        infoshow+="\n该文件夹信息统计结束";
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


