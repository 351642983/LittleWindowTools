#include <QCoreApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextCodec>
#include <QTextStream>
#include <QTime>
#include "ranks.h"

ranks::ranks(QWidget *parent):
    QDialog(parent)
{

}
ranks::~ranks()
{
    for(int i=0;i<3;i++)
    {
        delete info[i];
        delete button[i];
        delete wlist[i];
    }
}

void ranks::showrank(int g_ty)
{
    QVBoxLayout *mainLayout=new QVBoxLayout;
    QHBoxLayout *Layout[3];
    g_type=g_ty;
    Layout[0]=new QHBoxLayout;
    Layout[1]=new QHBoxLayout;
    Layout[2]=new QHBoxLayout;
    info[0]=new QLabel("排名");
    info[1]=new QLabel("名字");
    button[0]=new QPushButton(("清空所有数据"));
    button[1]=new QPushButton(("删除选择的数据"));
    button[2]=new QPushButton(("关闭窗口"));
    if(g_ty==1)
    {
        info[2]=new QLabel("长度(格)");
    }
    else if(g_ty==2)
    {
        info[2]=new QLabel("分数");
    }
    for(int i=0;i<3;i++)
    {
        wlist[i]=new QListWidget;
        Layout[0]->addStretch();
        Layout[0]->addWidget(info[i]);
        Layout[1]->addStretch();
        Layout[1]->addWidget(wlist[i]);
        Layout[2]->addStretch();
        Layout[2]->addWidget(button[i]);
        connect(wlist[i],SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(change_allselect(QListWidgetItem*)));


    }
    mainLayout->addLayout(Layout[0]);
    mainLayout->addLayout(Layout[1]);
    mainLayout->addLayout(Layout[2]);
    setLayout(mainLayout);
    setWindowFlags(Qt::WindowCloseButtonHint);
    setFixedSize(300,400);
    setWindowTitle(tr("排行榜"));
    connect(button[0],SIGNAL(clicked()),this,SLOT(del_allline()));
    connect(button[1],SIGNAL(clicked()),this,SLOT(del_line()));
    connect(button[2],SIGNAL(clicked()),this,SLOT(close()));


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
    fs.setFileName(QString("%1/ranks_%2.txt").arg(theaddress).arg(g_ty));

    fs.open(QIODevice::ReadOnly|QIODevice::Text);
    if(!fs.exists())
    {
        fs.close();
        fs.open(QIODevice::ReadOnly|QIODevice::Text);
    }

    QString m_line;
    QStringList thenumber;
    for(int j=1;j<=10&&!fs.atEnd();j++)
    {
        m_line=fs.readLine();
        thenumber=m_line.split(" ");
        wlist[0]->addItem(QString("%1").arg(j));
        wlist[1]->addItem(thenumber.at(0));
        m_line=thenumber.at(1);
        m_line.remove("\n");
        wlist[2]->addItem(m_line);
    }
    fs.close();



}
void ranks::change_allselect(QListWidgetItem* w)
{
    for(int i=0;i<3;i++)
    {
        wlist[i]->item(w->listWidget()->currentRow())->setSelected(true);
        wlist[i]->setCurrentRow(w->listWidget()->currentRow());
    }
}

void ranks::del_allline()
{

    for(int i=0;i<3;i++)
    {
        wlist[i]->clear();
    }

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

    fs.setFileName(QString("%1/ranks_%2.txt").arg(theaddress).arg(g_type));
    fs.remove();
    fs.close();
}

void ranks::del_line()
{

    bool g_throught=false;
    int g_num=wlist[0]->currentRow();
    for(int i=0;i<3;i++)
    {

        if(g_num!=0&&wlist[i]->count()!=1)
        {
            for(int j=0;j<3;j++)
            {
                wlist[j]->takeItem(g_num);

                wlist[j]->item(0)->setSelected(true);
                wlist[j]->setCurrentRow(0);
                //阻塞操作使用,检查运行步骤
                QTime dieTime = QTime::currentTime().addMSecs(50);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                if(!g_throught)
                    g_throught=true;
            }
            break;
        }
        else if(wlist[2]->count()==1)
        {
            wlist[i]->clear();
            g_throught=true;
        }

    }
    if(!g_throught)
    {
        for(int z=0;z<3;z++)
        {

            wlist[z]->takeItem(0);
            wlist[z]->item(0)->setSelected(true);
            wlist[z]->setCurrentRow(0);
        }
    }
    if(wlist[2]->count()!=0)
    {
        wlist[0]->clear();
        for(int g_i=1;g_i<=wlist[1]->count();g_i++)
            wlist[0]->addItem(QString("%1").arg(g_i));
        wlist[0]->item(0)->setSelected(true);
        wlist[0]->setCurrentRow(0);
    }



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

    fs.setFileName(QString("%1/ranks_%2.txt").arg(theaddress).arg(g_type));
    QTextCodec *code=QTextCodec::codecForName("UTF-8");
    fs.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream t(&fs);
    t.setCodec(code);
    for(int j=1;j<=wlist[0]->count();j++)
        t<<wlist[1]->item(j-1)->text()<<" "<<wlist[2]->item(j-1)->text()<<"\n";
    fs.close();
}

int ranks::insertrank(const char *name,int score,int type)
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

    QFile fs,v_fs;
    QString m_line,m_allinfo;
    QStringList thenumber;
    bool g_al=false;
    int linenum=0;

    fs.setFileName(QString("%1/ranks_%2.txt").arg(theaddress).arg(type));
    v_fs.setFileName(QString("%1/_%2.txt").arg(theaddress).arg(type));
    QTextCodec *code=QTextCodec::codecForName("UTF-8");
    fs.open(QIODevice::ReadOnly|QIODevice::Text);
    v_fs.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream t(&fs);
    QTextStream t1(&v_fs);
    t.setCodec(code);
    t1.setCodec(code);




    do
    {
        m_line=fs.readLine();
        linenum++;

        if(fs.atEnd())
        {
            if(!g_al)
            {
                g_al=true;
                if(linenum==1)
                {
                    if(m_line.contains("\n"))
                    {
                        thenumber=m_line.split(" ");
                        if(score>=thenumber.at(1).toInt())
                        {
                            m_allinfo+=QString("%1 %2\n").arg(name).arg(score);
                            m_allinfo+=m_line;
                            linenum++;
                        }
                        else
                        {
                            m_allinfo=m_line;
                            m_allinfo+=QString("%1 %2\n").arg(name).arg(score);
                        }
                    }
                    else m_allinfo=QString("%1 %2\n").arg(name).arg(score);

                }

                else
                {
                    m_allinfo+=m_line;
                    if(linenum<10)
                    {
                        m_allinfo+=QString("%1 %2\n").arg(name).arg(score);
                        linenum++;
                    }
                }
            }
            else
            {
                m_allinfo+=m_line;
            }
        }
        else if(!g_al)
        {
            thenumber=m_line.split(" ");
            if(score>=thenumber.at(1).toInt())
            {
                g_al=true;
                m_allinfo+=QString("%1 %2\n").arg(name).arg(score);
                m_allinfo+=m_line;
                linenum++;
            }
            else
            {
                m_allinfo+=m_line;
            }
        }
        else
        {
            m_allinfo+=m_line;
        }

    }while((!fs.atEnd()&&linenum<10));

    t1<<m_allinfo;
    fs.close();
    v_fs.close();
    QFile(QString("%1/ranks_%2.txt").arg(theaddress).arg(type)).remove();
    QFile::copy(QString("%1/_%2.txt").arg(theaddress).arg(type),QString("%1/ranks_%2.txt").arg(theaddress).arg(type));
    QFile(QString("%1/_%2.txt").arg(theaddress).arg(type)).remove();
    return 0;

}
