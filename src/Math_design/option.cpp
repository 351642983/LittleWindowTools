
#include "option.h"

option::option(QWidget *parent)
    :QDialog(parent)
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
    delete temp;
    QFile fs;
    QStringList thenumber;
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

    QVBoxLayout *mainlayout=new QVBoxLayout;
    QHBoxLayout *hlayout[4];
    for(int i=0;i<4;i++)
        hlayout[i]=new QHBoxLayout;
    lb[0]=new QLabel(("请设置你想要的速度："));
    lb[1]=new QLabel(("设置开始蛇的长度："));
    lb[2]=new QLabel(("限制60FPS："));
    sb[0]=new QSpinBox;
    sb[0]->setRange(6,30);
    sb[0]->setValue(thenumber.at(0).toInt());
    g_speed=thenumber.at(0).toInt();
    sb[1]=new QSpinBox;
    sb[1]->setRange(2,600/50);
    sb[1]->setValue(thenumber.at(1).toInt());
    cb=new QCheckBox;
    cb->setChecked(thenumber.at(2).toInt());
    g_lock=thenumber.at(1).toInt();
    hlayout[0]->addWidget(lb[0]);
    hlayout[0]->addWidget(sb[0]);
    mainlayout->addLayout(hlayout[0]);
    hlayout[1]->addWidget(lb[1]);
    hlayout[1]->addWidget(sb[1]);
    hlayout[2]->addWidget(lb[2]);
    hlayout[2]->addWidget(cb);
    bt[0]=new QPushButton(("确认"));
    bt[1]=new QPushButton(("取消"));
    bt[2]=new QPushButton(("应用"));
    hlayout[3]->addWidget(bt[0]);
    hlayout[3]->addWidget(bt[1]);
    hlayout[3]->addWidget(bt[2]);
    mainlayout->addLayout(hlayout[1]);
    mainlayout->addLayout(hlayout[2]);
    mainlayout->addLayout(hlayout[3]);
    setLayout(mainlayout);
    setFixedSize(sizeHint().width(),sizeHint().height());
    setWindowFlags(Qt::WindowCloseButtonHint);
    setWindowTitle(tr("设置"));

    connect(bt[0],SIGNAL(clicked()),this,SLOT(writeyc()));
    connect(bt[1],SIGNAL(clicked()),this,SLOT(close()));
    connect(bt[2],SIGNAL(clicked()),this,SLOT(writey()));


}

option::~option()
{
    delete bt[0];
    delete bt[1];
    delete bt[2];
    delete lb[0];
    delete lb[1];
    delete lb[2];
    delete sb[0];
    delete sb[1];
    delete cb;

}

void option::writey()
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
    delete temp;
    QFile fs;
    fs.setFileName(QString("%1/option.txt").arg(theaddress));
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
    QTextStream t(&fs);
    t.setCodec(codec);
    if(!fs.exists())
    {
        fs.open(QIODevice::WriteOnly|QIODevice::Text);
        fs.close();
    }

    fs.open(QIODevice::WriteOnly|QIODevice::Text);
    t<<sb[0]->value()<<" "<<sb[1]->value()<<" "<<cb->isChecked();
    fs.close();
    g_speed=sb[0]->value();
    g_lock=sb[1]->value();

}

void option::writeyc()
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
    delete temp;
    QFile fs;
    fs.setFileName(QString("%1/option.txt").arg(theaddress));
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
    QTextStream t(&fs);
    t.setCodec(codec);
    if(!fs.exists())
    {
        fs.open(QIODevice::WriteOnly|QIODevice::Text);
        fs.close();
    }

    fs.open(QIODevice::WriteOnly|QIODevice::Text);
    t<<sb[0]->value()<<" "<<sb[1]->value()<<" "<<cb->isChecked();
    fs.close();
    g_speed=sb[0]->value();
    g_lock=sb[1]->value();
    close();
}
