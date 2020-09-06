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

            db.setHostName("182.61.38.20");                        //127.0.0.1Ҳ��һ����,���ڱ��ص�ַ
            db.setPort(3306);
            db.setUserName("rdsroot");                                 //��½MYSQL���û���
            db.setPassword("aA13902766702");                              //���Լ���½������
            db.setDatabaseName("tools");                       //��½���ݿ������
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
                        QMessageBox::about(this,"����","�������");
                    }
                }
                else if(!g_an)
                {
                    QMessageBox::about(this,"����","�˺Ų�����,���������˺��Ƿ���ȷ");
                }

            }
            else
            {
                QMessageBox::about(this,"����","��������ʧ��,���������Ƿ���������");
            }
        }
        else if(!g_an)
        {
            QMessageBox::about(this,"����","�������,����λ��������ڻ��¼��λ");
        }
    }
    else if(!g_an)
    {
        QMessageBox::about(this,"����","�������,������8��15λ���ĵ��û��˺�");
    }
    g_an=false;

}

void login::on_pushButton_2_clicked()
{
    zhuce();
}
