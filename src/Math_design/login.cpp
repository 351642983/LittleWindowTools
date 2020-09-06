#include "login.h"
#include "ui_login.h"

Zcwidget *zc;

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);


    QRegExp reg("[0-9]{0,15}"),reg_1("([0-9a-zA-Z)]){0,15}");
    QValidator *va=new QRegExpValidator(reg,ui->lineEdit);
    QValidator *va1=new QRegExpValidator(reg_1,ui->lineEdit_2);
    ui->lineEdit->setValidator(va);
    ui->lineEdit_2->setValidator(va1);


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
    fs.setFileName(QString("%1/dfge.login").arg(theaddress));
    if(fs.exists())
    {
        fs.open(QIODevice::ReadOnly|QIODevice::Text);
        QString m_line=fs.readLine();
        thenumber=m_line.split(" ");
        fs.close();
        if(thenumber.at(2).toInt())
        {
            ui->lineEdit->setText(thenumber.at(0));
            if(thenumber.at(3).toInt())
            {
                ui->lineEdit_2->setText(thenumber.at(1));
            }
            else
            {
                ui->checkBox_2->setChecked(0);
            }
        }
        else
        {
            ui->checkBox->setChecked(0);
            ui->checkBox_2->setChecked(0);
        }
    }

    g_an=false;

    time=new QTimer;
    connect(time,SIGNAL(timeout()),this,SLOT(updateInfo()));
    connect(ui->lineEdit_2,SIGNAL(returnPressed()),this,SLOT(on_pushButton_clicked()));



}

login::~login()
{
    delete ui;
}
void login::zhuce()
{
    zc=new Zcwidget();
    zc->show();
    time->start(500);
}
void login::updateInfo()
{
    if(!zc->ook.isEmpty())
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
        fs.setFileName(QString("%1/dfge.login").arg(theaddress));
        QTextCodec *codec=QTextCodec::codecForName("UTF-8");
        QTextStream t(&fs);
        t.setCodec(codec);
        fs.open(QIODevice::WriteOnly|QIODevice::Text);
        t<<zc->ook.at(0)+" "+zc->ook.at(2)+" "+QString::number(ui->checkBox->isChecked())+" "+QString::number(ui->checkBox_2->isChecked());
        t.flush();
        fs.flush();
        fs.close();

        zhanghao=zc->ook;
        time->stop();

    }
}

void login::on_pushButton_clicked()
{

    if(ui->lineEdit->text().length()<=15&&ui->lineEdit->text().length()>=8)
    {
        if(ui->lineEdit_2->text().length()>=6)
        {
            //db = QSqlDatabase::addDatabase("QMYSQL");
            //QSqlDatabase db;
            if(QSqlDatabase::contains("qt_sql_default_connection"))
              db = QSqlDatabase::database("qt_sql_default_connection");
            else
              db = QSqlDatabase::addDatabase("QMYSQL");

            db.setHostName("182.61.38.20");                        //127.0.0.1也是一样的,属于本地地址
            db.setPort(3306);
            db.setUserName("rdsroot");                                 //登陆MYSQL的用户名
            db.setPassword("aA13902766702");                              //你自己登陆的密码
            db.setDatabaseName("tools");                       //登陆数据库的名称
            if(db.open())
            {
                QSqlQuery query;
                query.exec(QString("select * from zhuce where zhanghao=\"%1\";").arg(ui->lineEdit->text()));
                query.first();
                QMessageBox::about(NULL,query.value(0).toString(),query.value(0).toString());
                if(!query.value(0).toString().isEmpty())
                {
                    if(ui->lineEdit_2->text()==query.value(2).toString())
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
                        fs.setFileName(QString("%1/dfge.login").arg(theaddress));
                        QTextCodec *codec=QTextCodec::codecForName("UTF-8");
                        QTextStream t(&fs);
                        t.setCodec(codec);
                        fs.open(QIODevice::WriteOnly|QIODevice::Text);
                        t<<ui->lineEdit->text()+" "+ui->lineEdit_2->text()+" "+QString::number(ui->checkBox->isChecked())+" "+QString::number(ui->checkBox_2->isChecked());
                        t.flush();
                        fs.flush();
                        fs.close();
                        zhanghao=(QString("%1 %2 %3").arg(query.value(0).toString()).arg(query.value(1).toString()).arg(query.value(2).toString())).split(" ");

                        close();
                    }
                    else if(!g_an)
                    {
                        QMessageBox::about(this,"提醒","密码错误");
                    }
                }
                else if(!g_an)
                {
                    QMessageBox::about(this,"提醒","账号不存在,请检查您的账号是否正确");
                }

            }
            else
            {
                QMessageBox::about(this,"提醒","网络连接失败,请检查网络是否正常连接");
            }
        }
        else if(!g_an)
        {
            QMessageBox::about(this,"提醒","输入错误,密码位数必须大于或登录六位");
        }
    }
    else if(!g_an)
    {
        QMessageBox::about(this,"提醒","输入错误,请输入8到15位数的的用户账号");
    }
    g_an=false;

}

void login::on_pushButton_2_clicked()
{
    zhuce();
}
