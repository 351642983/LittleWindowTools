#include "YYSTask.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QApplication>

YYSTask::YYSTask(QWidget *parent):
    QWidget(parent)
{
    l1=new QLabel("搜索内容(可输入拼音或拼音缩写)：");
    le=new QLineEdit();
    pb=new QPushButton("搜索");
    QVBoxLayout *mainLayout=new QVBoxLayout();
    QHBoxLayout *hLayout1=new QHBoxLayout();
    hLayout1->addWidget(l1);
    hLayout1->addWidget(le);
    hLayout1->addWidget(pb);
    mainLayout->addLayout(hLayout1);

    QHBoxLayout *hLayout2=new QHBoxLayout();
    l2=new QLabel("搜索结果");
    l3=new QLabel("地点分布");
    hLayout2->addWidget(l2);
    hLayout2->addStretch();
    hLayout2->addWidget(l3);
    hLayout2->addStretch();
    mainLayout->addLayout(hLayout2);
    QHBoxLayout *hLayout3=new QHBoxLayout();
    searchResult=new QListWidget();
    te=new QTextEdit();
    hLayout3->addWidget(searchResult);
    hLayout3->addWidget(te);
    mainLayout->addLayout(hLayout3);
    setLayout(mainLayout);
    setFixedSize(sizeHint().width(),sizeHint().height()+200);
    setWindowTitle("阴阳师任务查询");
    show();
    transform=new chinesechange();
    //QMessageBox::about(NULL,"测试",tranform->GetPinyins("开心")/*->GetFirstLetters("开心")*/);
    connect(le,SIGNAL(textChanged(QString)),this,SLOT(changeListInfo(QString)));
    connect(le,SIGNAL(returnPressed()),this,SLOT(selectListWidgetItem()));
    connect(searchResult,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(selectItem(QListWidgetItem*)));
    connect(pb,SIGNAL(clicked()),this,SLOT(selectListWidgetItem()));
    //getListInfo();//测试信息显示
    te->setReadOnly(true);
    info=getListInfo();
    foreach(QString it,info)
    {
        QString itClone=it;
        itClone.remove("\n");
        if(itClone.contains("@"))
        {
            itClone.remove("@");
            searchResult->addItem(itClone);
        }
    }
    //QMessageBox::about(NULL,"测试",transform->GetFirstLetter("开心")/*->GetFirstLetters("开心")*/);


}
void YYSTask::selectItem(QListWidgetItem *item)
{
    showTheInfo(searchResult->currentRow());
}

void YYSTask::showTheInfo(int num)
{
    if(searchResult->count()==0)
        return;
    te->clear();
    int count=0;
    searchResult->item(num)->setSelected(true);
    searchResult->setCurrentRow(num);
    int pt=searchPosition(searchResult->currentItem()->text());
    foreach(QString it,info)
    {
        QString itClone=it;
        if(itClone.contains("@"))
        {
            count++;

        }
        else if(count-1==pt)
        {
            te->append(itClone);
        }
    }
}
int YYSTask::searchPosition(QString it)
{
    int num=0;
    foreach(QString init,info)
    {
        if(init.contains("@"))
        {
            QString itClone=init.remove("@").remove("\n");
            if(itClone==it)
                return num;
            num++;
        }

    }
    return 0;
}

void YYSTask::selectListWidgetItem()
{
    if(searchResult->count()==0)
    {
        QMessageBox::about(NULL,"提醒","查无此妖怪");
    }
    else
    {
        showTheInfo(0);
    }
}

void YYSTask::changeListInfo(QString textinfo)
{
    if(textinfo.isNull())
        return;
    searchResult->clear();
    foreach(QString it,info)
    {
        QString itClone=it;
        itClone.remove("\n");
        if(itClone.contains("@"))
        {
            itClone.remove("@");
            if(transform->GetFirstLetters(itClone).contains(transform->GetFirstLetters(textinfo))||transform->GetPinyins(itClone).contains(transform->GetPinyins(textinfo)))
            {
                searchResult->addItem(itClone);
            }
        }
    }
    showTheInfo(0);
}
QList<QString> YYSTask::getListInfo()
{
    QList<QString> listInfo;

    QString theaddress=QApplication::applicationDirPath();
//    QDir *temp = new QDir;
//    if(!temp->exists(theaddress))
//    {
//        if(!temp->mkdir(theaddress))
//        {
//               theaddress= "C:/g_rank";
//               temp->mkdir(theaddress);
//        }
//    }
//    delete temp;
    QFile fs;
    fs.setFileName(QString("%1/YYSTask.txt").arg(theaddress));
    if(!fs.exists())
    {
        fs.open(QIODevice::ReadWrite|QIODevice::Text);
        fs.close();
    }
    fs.open(QIODevice::ReadOnly|QIODevice::Text);
    QString read;
    while(!fs.atEnd())
    {
        read=fs.readLine();
        //QMessageBox::about(NULL,"测试",read/*->GetFirstLetters("开心")*/);
        listInfo<<read;
    }
    fs.close();
    return listInfo;
}

YYSTask::~YYSTask()
{

}

