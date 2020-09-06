#include "form.h"
#include "ui_form.h"
#include <QDir>
#include <QFile>
#include <QTextCodec>
#include <QTextStream>
const char *str[]=
{
    "´óÐ×",
    "Ð×",
    "°ëÐ×",
    "Ò»°ã",
    "Ð¡¼ª",
    "ÖÐ¼ª",
    "´ó¼ª"
};
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
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
    fs.setFileName(QString("%1/lucker.saver").arg(theaddress));
    if(!fs.exists())
    {
        fs.open(QIODevice::ReadWrite|QIODevice::Text);
        fs.close();

    }

    fs.open(QIODevice::ReadOnly|QIODevice::Text);
    QString read=QString::fromUtf8(fs.readLine());
    fs.close();

    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd");
    QStringList lists=read.split(" ");
    if(!lists.isEmpty())
    {
        if(lists.at(0)!=current_date)
        {
            //QMessageBox::about(NULL,read,QCoreApplication::applicationFilePath().replace("/","\\").toStdString().c_str());
            ui->pushButton->setEnabled(1);


        }
        else
        {
            ui->pushButton->setEnabled(0);
            ui->label_2->setText(str[lists.at(1).toInt()]);
        }
    }
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    int z=random_num(1,(int)(sizeof(str)/sizeof(str[0])))-1;
    ui->label_2->setText(str[z]);
    ui->pushButton->setEnabled(0);

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
    fs.setFileName(QString("%1/lucker.saver").arg(theaddress));
    if(!fs.exists())
    {
        fs.open(QIODevice::ReadWrite|QIODevice::Text);
        fs.close();

    }
    QTextCodec *code=QTextCodec::codecForName("UTF-8");
    fs.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream t(&fs);
    t.setCodec(code);
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd");
    t<<current_date<<" "<<z;
    fs.close();

}
int Form::random_num(int x,int y)
{
    static bool g_i=false;
    if(!g_i)
    {
        qsrand(QTime(0,0,0,0).msecsTo( QTime::currentTime()));
        g_i=true;
    }

    return (qrand()%(y-x+1)+x);
}

void Form::on_pushButton_2_clicked()
{
    close();
}
