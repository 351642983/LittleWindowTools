//贪吃蛇显示及其处理的汇总源文件
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QPaintDevice>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <QProcess>
#include "g_Snake.h"
#include "g_Snakemath.h"
#include "widget.h"
#include "ranks.h"
#include "option.h"
#include "handoption.h"



QStringList thenumber;

g_snake::g_snake(QWidget *parent):
    QWidget(parent),
    g_scene(new QGraphicsScene(this)),
    g_view(new QGraphicsView(g_scene, this))
{
    //隐藏Frame框架,否则会有白框框
    g_view->hide();
    g_type=0;
    timer=new QTimer;
    button[0]=new QPushButton(("开始游戏"));
    button[1]=new QPushButton(("设置"));
    button[2]=new QPushButton(("排名前10"));
    button[3]=new QPushButton(("返回选择框"));

    QVBoxLayout *mainLayout=new QVBoxLayout;
    for(int i=0;i<=3;i++)
        mainLayout->addWidget(button[i]);
    setLayout(mainLayout);
    setFixedSize(sizeHint().width(),sizeHint().height());
    setWindowFlags(Qt::Dialog|Qt::WindowCloseButtonHint);
    connect(button[0],SIGNAL(clicked()),this,SLOT(startgame()));
    connect(button[1],SIGNAL(clicked()),this,SLOT(setoption()));
    connect(button[2],SIGNAL(clicked()),this,SLOT(seerank()));
    connect(button[3],SIGNAL(clicked()),this,SLOT(postclose()));
    snake=new g_snakemath(1);
    g_scene->addItem(snake);

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
    QFile fs;
    fs.setFileName(QString("%1/option.txt").arg(theaddress));
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
    QTextStream t(&fs);
    t.setCodec(codec);
    if(!fs.exists())
    {
        fs.open(QIODevice::WriteOnly|QIODevice::Text);
        t<<"1 2 0";
        thenumber=QString("1 2 0").split(" ");
        fs.close();
    }
    else
    {

        fs.open(QIODevice::ReadOnly|QIODevice::Text);
        QString m_line=fs.readLine();
        thenumber=m_line.split(" ");
    }
    fs.close();
    snake->addBody(800/LENTH/2,600/LENTH/2);
    for(int j=1;j<=thenumber.at(1).toInt()-1;j++)
        snake->addBody(-1-j,-1);

    snake->restore_food();

    g_fps=0;
    g_knum=0;
}

g_snake::~g_snake()
{
    release_new();
}



//释放空间类型的判断，并释放出相应的内存
void g_snake::release_new()
{
    if(g_type==0)
    {
        for(int i=0;i<=3;i++)
            delete button[i];
    }
}


//矩形方阵的创立
void g_snake::create_rect()
{
    g_scene->setSceneRect(-100, -100, 200, 200);
}




//开始游戏所执行的操作
void g_snake::startgame()
{

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
    QFile fs;
    fs.setFileName(QString("%1/option.txt").arg(theaddress));
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
    QTextStream t(&fs);
    t.setCodec(codec);
    if(!fs.exists())
    {
        fs.open(QIODevice::WriteOnly|QIODevice::Text);
        t<<"6 2 0";
        thenumber=QString("6 2 0").split(" ");
        fs.close();
    }
    else
    {

        fs.open(QIODevice::ReadOnly|QIODevice::Text);
        QString m_line=fs.readLine();
        thenumber=m_line.split(" ");
    }
    fs.close();
    snake->addBody(800/LENTH/2,600/LENTH/2);
    for(int j=1;j<=thenumber.at(1).toInt()-1;j++)
        snake->addBody(-1-j,-1);

    snake->restore_food();
    //释放内存操作
    release_new();
    //设置显示模式为1,即开始游戏的显示模式
    g_type=1;

    //界面变换的操作


    g_scene->setSceneRect(0,0,800,600);
    g_view->setBackgroundBrush(QBrush((Qt::GlobalColor)5));
    //test;;

    //矩阵建立
//    g_scene->addLine(0, 0, 800, 0,QPen(Qt::black));
//    for(int i=1;i<=600/LENTH;i++)
//        g_scene->addLine(0.0, i*LENTH, 800, i*LENTH,QPen(Qt::black));
//    g_scene->addLine(0, 0, 0, 600,QPen(Qt::black));
//    for(int j=1;j<=800/LENTH;j++)
//        g_scene->addLine(j*LENTH, 0, j*LENTH,600,QPen(Qt::black));

    g_view->resize(820,620);
    g_view->show();
    setFixedSize(820,620);



    QHBoxLayout *h=new QHBoxLayout;
    QHBoxLayout *h1[3];
    h1[0]=new QHBoxLayout;
    h1[1]=new QHBoxLayout;
    h1[2]=new QHBoxLayout;
    QVBoxLayout *v1=new QVBoxLayout;
    button[4]=new QPushButton(tr("暂停"));
    button[5]=new QPushButton(tr("继续"));
    button[6]=new QPushButton(tr("返回选择框"));
    button[5]->setEnabled(false);

    words[0]=new QLabel(tr("分数："));
    words[1]=new QLabel(tr("时间："));
    words[2]=new QLabel(tr("帧数："));
    lcdnumber[0]=new QLCDNumber();
    lcdnumber[1]=new QLCDNumber();
    lcdnumber[2]=new QLCDNumber();
    lcdnumber[0]->setNumDigits(3);
    lcdnumber[1]->setNumDigits(3);
    lcdnumber[2]->setNumDigits(5);
    h->addWidget(this);
    for(int z=0;z<=2;z++)
    {
        h1[z]->addWidget(words[z]);
        h1[z]->addWidget(lcdnumber[z]);
        v1->addLayout(h1[z]);
    }

    v1->addWidget(button[4]);
    v1->addWidget(button[5]);
    v1->addWidget(button[6]);
    h->addLayout(v1);

    dieTime=QTime::currentTime();
    onetime=QTime::currentTime();

    gw=new gamewidget;
    gw->setLayout(h);
    gw->setFixedSize(820+150,640);
    gw->show();
    gw->setWindowTitle("贪吃蛇");

    connect(timer,SIGNAL(timeout()),this,SLOT(refresh()));
    connect(button[4],SIGNAL(clicked()),this,SLOT(pause()));
    connect(button[5],SIGNAL(clicked()),this,SLOT(resume()));
    connect(button[6],SIGNAL(clicked()),this,SLOT(rets()));
    timer->start(thenumber.at(2).toInt()?1000/60:0);
    gw->move((QApplication::desktop()->width() - gw->width()) / 2, (QApplication::desktop()->height() -  gw->height()) / 2);



}
void g_snake::rets()
{
    QProcess::startDetached(QCoreApplication::applicationFilePath().remove(QString("_")+QString(VERSION)), QStringList());
    exit(0);
}

void g_snake::refresh()
{
 //用以设置蛇走的速度

    g_fps++;

    if( QTime::currentTime() > onetime )
    {
        setFocus();
        onetime = QTime::currentTime().addMSecs(1000);

        lcdnumber[2]->display(g_fps);
        lcdnumber[1]->display(g_knum++);
        g_fps=0;
    }
    if( QTime::currentTime() > dieTime )
    {
        dieTime = QTime::currentTime().addMSecs(1000/thenumber.at(0).toInt());

        if(!snake->isoutgame())
        {
            snake->nextCarry();
            if(snake->eatFoodCheck())
            {
                snake->restore_food();
                snake->addBody(-1,-1);

                lcdnumber[0]->display(snake->g_eatnum);
            }

        }
        else
        {
            timer->stop();
            disconnect(timer,SIGNAL(timeout()),this,SLOT(refresh()));
            bool isOK;
            QString text = QInputDialog::getText(NULL, "游戏结束",
                                                 QString("你的最后得分是:%1\n请输入你的名字").arg(snake->g_eatnum),
                                                 QLineEdit::Normal,
                                                 "",
                                                 &isOK);
            Widget *ws=new Widget;
            ws->hide();
            close();
            gw->close();
            if(isOK)
            {
                text.remove(" ");
                ranks *s=new ranks;
                s->showrank(1);
                s->insertrank(text.toLatin1().data(),snake->g_eatnum,1);
                delete s;
                ranks *s1=new ranks;
                s1->showrank(1);
                s1->show();
            }
            else
            {
                QMessageBox::about(NULL, "排行榜", "已选择取消对该数据的上传  ");
            }


        }
    }




}
void g_snake::lcdrefresh()
{

}
void g_snake::keyPressEvent(QKeyEvent *event)
{


    if(event->key()==Qt::Key_W)
    {
        if(snake->currentDirt!=UPMOVE&&snake->currentDirt!=DOWNMOVE)
        {
            snake->currentDirt=UPMOVE;
        }
    }
    else if(event->key()==Qt::Key_D)
    {
        if(snake->currentDirt!=RIGHTMOVE&&snake->currentDirt!=LEFTMOVE)
        {
            snake->currentDirt=RIGHTMOVE;

        }
    }
    else if(event->key()== Qt::Key_S)
    {
        if(snake->currentDirt!=UPMOVE&&snake->currentDirt!=DOWNMOVE)
        {
            snake->currentDirt=(DOWNMOVE);
        }
    }
    else if(event->key()== Qt::Key_A)
    {
        if(snake->currentDirt!=RIGHTMOVE&&snake->currentDirt!=LEFTMOVE&&snake->currentDirt!=NOMOVE)
        {
            snake->currentDirt=(LEFTMOVE);
        }
    }

}

void g_snake::pause()
{
    button[4]->setEnabled(false);
    button[5]->setEnabled(true);
    disconnect(timer,SIGNAL(timeout()),this,SLOT(refresh()));
    setFocus();
}
void g_snake::resume()
{
    button[5]->setEnabled(false);
    button[4]->setEnabled(true);
    connect(timer,SIGNAL(timeout()),this,SLOT(refresh()));
    setFocus();
}

//按下设置按钮所执行的操作
void g_snake::setoption()
{

    option *op=new option;
    op->show();
    //timer.start(op->cb->isChecked()?1000/60:0);
}

//查看前10所执行的操作
void g_snake::seerank()
{
    ranks *a=new ranks;
    a->showrank(1);
    a->show();

}

//退出游戏所执行的操作
void g_snake::postclose()
{
    //新建窗口以返回选择框
    QProcess::startDetached(QCoreApplication::applicationFilePath().remove(QString("_")+QString(VERSION)), QStringList());
    exit(0);
}
