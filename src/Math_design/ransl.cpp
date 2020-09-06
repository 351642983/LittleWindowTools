#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCoreApplication>
#include <QProcess>
#include "ransl.h"
#include "handoption.h"
ransl::ransl(QWidget *parent):
    QWidget(parent)
{
    QHBoxLayout *mainlayout=new QHBoxLayout;
    QHBoxLayout *hlayout[4];
    hlayout[0]=new QHBoxLayout;
    hlayout[1]=new QHBoxLayout;
    hlayout[2]=new QHBoxLayout;
    hlayout[3]=new QHBoxLayout;

    QVBoxLayout *vlayout=new QVBoxLayout;
    QVBoxLayout *vlayout_1=new QVBoxLayout;


    bt[0]=new QPushButton("开始抽数进程");
    bt[1]=new QPushButton("抽取一个");
    bt[2]=new QPushButton("抽取全部");
    //bt[3]=new QPushButton("返回选择框");
    //bt[0]->setEnabled(0);
    bt[2]->setEnabled(0);
    bt[1]->setEnabled(0);
    wt=new QListWidget;
    cb=new QCheckBox;
    word[0]=new QLabel("抽取的数值框:");
    word[1]=new QLabel("显示框:");
    word[2]=new QLabel("设置不出现重复抽的数");
    word[3]=new QLabel("设置抽取数值的范围");
    word[4]=new QLabel("到");
    texte=new QTextEdit;
    lcd=new QLCDNumber;
    sb[0]=new QSpinBox;
    sb[1]=new QSpinBox;
    sb[0]->setRange(0,99999);
    sb[1]->setRange(0,99999);
    sb[0]->setValue(0);
    sb[1]->setValue(10);
    vlayout_1->addWidget(word[0],0,Qt::AlignLeft);
    //hlayout[0]->addWidget(word[0],1,Qt::AlignLeft);
    vlayout_1->addWidget(wt);
    hlayout[0]->addLayout(vlayout_1);
    mainlayout->addLayout(hlayout[0]);
    vlayout->addWidget(word[1],0,Qt::AlignLeft);
    vlayout->addWidget(lcd);
    hlayout[1]->addWidget(cb,0,Qt::AlignLeft);
    hlayout[1]->addWidget(word[2],2,Qt::AlignLeft);
    vlayout->addLayout(hlayout[1]);
    vlayout->addWidget(bt[0]);
    hlayout[2]->addWidget(bt[1]);
    hlayout[2]->addWidget(bt[2]);
    vlayout->addLayout(hlayout[2]);
    //vlayout->addWidget(bt[3]);
    //vlayout->addWidget(word[3],1,Qt::AlignLeft);
    hlayout[3]->addWidget(word[3],0,Qt::AlignLeft);
    hlayout[3]->addWidget(sb[0]);
    hlayout[3]->addWidget(word[4],0,Qt::AlignLeft);
    hlayout[3]->addWidget(sb[1],1,Qt::AlignLeft);
    vlayout->addLayout(hlayout[3]);
    mainlayout->addLayout(vlayout);
    mainlayout->addWidget(texte);
    setLayout(mainlayout);
    texte->setReadOnly(true);

    setFixedSize(800,400);
    setWindowTitle("随机数抽取器");
    setWindowFlags(Qt::WindowCloseButtonHint);
    timer=new QTimer;
    timer->start(10);

    connect(cb,SIGNAL(clicked(bool)),this,SLOT(changemode(bool)));
    connect(bt[0],SIGNAL(clicked()),this,SLOT(thebegin()));
    connect(bt[1],SIGNAL(clicked()),this,SLOT(chouyi()));
    connect(bt[2],SIGNAL(clicked()),this,SLOT(chouall()));
    //connect(bt[3],SIGNAL(clicked()),this,SLOT(closehandle()));
    connect(timer,SIGNAL(timeout()),this,SLOT(refresh()));
    infoshow+="输出信息如下:";
    textshow();
    g_start=false;
    g_num=0;

}
ransl::~ransl()
{

}
void ransl::closehandle()
{
    QProcess::startDetached(QCoreApplication::applicationFilePath().remove(QString("_")+QString(VERSION)), QStringList());
    exit(0);
}
void ransl::changemode(bool g_mode)
{

    {
        if(g_mode)
        {
            if(g_start)
                bt[2]->setEnabled(1);
            infoshow+="设置为不抽取重复数字的模式";
            textshow();
        }
        else
        {
            //bt[0]->setEnabled(0);
            bt[2]->setEnabled(0);
            infoshow+="设置为可抽取重复数字的模式";
            textshow();
        }
    }
}
void ransl::chouall()
{
    if(g_start)
    {
        infoshow+="抽的所有数的结果如下: ";
        while(numlist.length()!=0&&g_start)
        {
//            QTime dieTime = QTime::currentTime().addMSecs(1);
//            while( QTime::currentTime() < dieTime )
//                QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
            g_num=random_num(0,numlist.length()-1);
            wt->addItem(QString("%1").arg(numlist.at(g_num)));
            infoshow+=QString("%1 ").arg(numlist.at(g_num));
            if(cb->isChecked())
                numlist.removeAt(g_num);

        }
        //textshow();
    }
}
void ransl::chouyi()
{
    if(g_start)
    {

        if(numlist.length()!=0)
        {
            infoshow+="抽一次随机数的结果: ";
            wt->addItem(QString("%1").arg(numlist.at(g_num)));
            infoshow+=QString("%1 ").arg(numlist.at(g_num));
            if(cb->isChecked())
                numlist.removeAt(g_num);
            textshow();
        }
        else
        {
            g_start=!g_start;
            infoshow+="已结束抽数进程 原因：数组中的数已经全部被抽取完";
            textshow();
            bt[0]->setText("开始抽数进程");
            //bt[0]->setEnabled(1);
            bt[2]->setEnabled(0);
            bt[1]->setEnabled(0);
            lcd->display(sb[0]->value());
        }
    }
}
void ransl::refresh()
{
    if(g_start)
    {
        if(numlist.count()!=0)
        {
            if(sb[0]->value()<sb[1]->value())
            {

                g_num=random_num(0,numlist.length()-1);
                lcd->display(numlist.at(g_num));

            }
            else
            {
                g_start=!g_start;
                infoshow+="\n已结束抽数进程 原因：抽数过程中操作错误";
                textshow();
                bt[0]->setText("开始抽数进程");
                //bt[0]->setEnabled(1);
                bt[2]->setEnabled(0);
                bt[1]->setEnabled(0);

            }
        }
        else
        {
            g_start=!g_start;
            infoshow+="\n已结束抽数进程 原因：数组中的数已经全部被抽取完";
            textshow();
            bt[0]->setText("开始抽数进程");
            //bt[0]->setEnabled(1);
            bt[2]->setEnabled(0);
            bt[1]->setEnabled(0);
            lcd->display(sb[0]->value());

        }
    }
}
void ransl::thebegin()
{
    if(sb[0]->value()<sb[1]->value())
    {
        if(!g_start)
        {
            g_start=!g_start;
            numlist.clear();
            wt->clear();
            infoshow+="开始抽数进程，并清空所有之前抽的数的集合";
            textshow();
            bt[0]->setText("结束进程");
            bt[1]->setEnabled(1);
            if(cb->isChecked())
                bt[2]->setEnabled(1);
            for(int i=sb[0]->value();i<=sb[1]->value();i++)
            {
                numlist<<i;
            }

            textshow();
        }
        else
        {
            g_start=!g_start;
            infoshow+="\n已结束抽数进程";
            textshow();
            bt[0]->setText("开始抽数进程");
            //bt[0]->setEnabled(1);
            bt[2]->setEnabled(0);
            bt[1]->setEnabled(0);
            lcd->display(sb[0]->value());

        }

    }
    else
    {
        infoshow+="数值范围设置错误，无法开始进程";
        textshow();


    }
}
//bigger
int ransl::random_num(int x,int y)
{
    static bool g_i=false;
    static QTime tlast=QTime::currentTime();
    if(!g_i)
    {
        qsrand((uint)QTime(0,0,0,0).msecsTo(tlast));
        g_i=true;
    }
    else if(QTime(0,0,0,0).msecsTo(tlast)!=QTime(0,0,0,0).msecsTo(QTime::currentTime()))
    {
        tlast=QTime::currentTime();
        qsrand((uint)QTime(0,0,0,0).msecsTo(tlast));
    }
    return ((qrand()*qrand())%(y-x+1)+x);
}

void ransl::textshow()
{
    infoshow+="\n";
    texte->setText(infoshow);
    QTextCursor cursor =texte->textCursor();
    cursor.movePosition(QTextCursor::End);
    texte->setTextCursor(cursor);
}
