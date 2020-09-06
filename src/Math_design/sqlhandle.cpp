#include "sqlhandle.h"
#include "ui_sqlhandle.h"
#include <QMessageBox>
#include <QValidator>
#include <QRegExpValidator>
#include <QDir>
#include <QFile>
#include <QTextCodec>
#include <QTextStream>

sqlhandle::sqlhandle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sqlhandle)
{
    ui->setupUi(this);
    QRegExp reg("(25[0-5]|2[0-4]\\d|[0-1]\\d{2}|[1-9]?\\d)\\.(25[0-5]|2[0-4]\\d|[0-1]\\d{2}|[1-9]?\\d)\\.(25[0-5]|2[0-4]\\d|[0-1]\\d{2}|[1-9]?\\d)\\.(25[0-5]|2[0-4]\\d|[0-1]\\d{2}|[1-9]?\\d)");
    QValidator *val=new QRegExpValidator(reg,ui->lineEdit_2);
    ui->lineEdit_2->setValidator(val);
    QRegExp reg_1("\\d{0,6}");
    QValidator *val_1=new QRegExpValidator(reg_1,ui->lineEdit_3);
    ui->lineEdit_3->setValidator(val_1);
    ui->pushButton->setEnabled(0);
    ui->pushButton_2->setEnabled(1);
    ui->lineEdit_2->setTabOrder(ui->lineEdit_2,ui->lineEdit_3);
    ui->lineEdit_3->setTabOrder(ui->lineEdit_3,ui->lineEdit);
    ui->lineEdit->setTabOrder(ui->lineEdit,ui->lineEdit_4);
    ui->lineEdit_4->setTabOrder(ui->lineEdit_4,ui->lineEdit_5);
    ui->lineEdit_5->setTabOrder(ui->lineEdit_5,ui->pushButton_2);




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
    fs.setFileName(QString("%1/dfge.ksg").arg(theaddress));
    if(fs.exists())
    {
        fs.open(QIODevice::ReadOnly|QIODevice::Text);
        QString m_line=fs.readLine();
        thenumber=m_line.split(" ");
        fs.close();
        ui->lineEdit->setText(thenumber.at(0));
        ui->lineEdit_2->setText(thenumber.at(1));
        ui->lineEdit_3->setText(thenumber.at(2));
        ui->lineEdit_4->setText(thenumber.at(3));
        ui->lineEdit_5->setText(thenumber.at(4));

    }

}

sqlhandle::~sqlhandle()
{
    delete ui;
}

void sqlhandle::on_pushButton_clicked()
{
    QSqlQuery query;
    if(!ui->textEdit->toPlainText().isEmpty())
    {
        if(!query.exec(QString(ui->textEdit->toPlainText())))//���Ҹ�id�ļ�¼
        {
               QMessageBox::about(this,"����","������ִ��ʧ�ܣ���������Ƿ���ȷ");
        }
        else
        {
            QMessageBox::about(this,"����","������ִ�гɹ�");
            ui->textEdit->clear();
        }
    }
    else QMessageBox::about(this,"����","����ִ�в���Ϊ��");
}

void sqlhandle::on_pushButton_2_clicked()
{
    if(!db.isOpen())
    {
        if(ui->lineEdit_2->text().isEmpty()||ui->lineEdit_3->text().isEmpty()||ui->lineEdit_5->text().isEmpty())
        {
            QMessageBox::about(this,"����","ip��ַ���߶˿����ֲ���Ϊ��");
        }
        else
        {
            //db = QSqlDatabase::addDatabase("QMYSQL");
            if(QSqlDatabase::contains("qt_sql_default_connection"))
              db = QSqlDatabase::database("qt_sql_default_connection");
            else
              db = QSqlDatabase::addDatabase("QSQLITE");
            db.setHostName(ui->lineEdit_2->text());                        //127.0.0.1Ҳ��һ����,���ڱ��ص�ַ
            db.setPort(ui->lineEdit_3->text().toInt());
            db.setUserName(ui->lineEdit->text());                                 //��½MYSQL���û���
            db.setPassword(ui->lineEdit_4->text());                              //���Լ���½������
            db.setDatabaseName(ui->lineEdit_5->text());                       //��½���ݿ������
            if(db.open())                                                  //�����ݿ�����
            {
                ui->pushButton->setEnabled(1);
                ui->pushButton_2->setEnabled(1);
                ui->pushButton_2->setText("�Ͽ�");
                ui->lineEdit->setReadOnly(1);
                ui->lineEdit_2->setReadOnly(1);
                ui->lineEdit_3->setReadOnly(1);
                ui->lineEdit_4->setReadOnly(1);
                ui->lineEdit_5->setReadOnly(1);
                QBrush br=QBrush(Qt::gray,Qt::DiagCrossPattern); ;
                QPalette pa;
                pa.setBrush(QPalette::Text,br);
                ui->lineEdit->setPalette(pa);
                ui->lineEdit_2->setPalette(pa);
                ui->lineEdit_3->setPalette(pa);
                ui->lineEdit_4->setPalette(pa);
                ui->lineEdit_5->setPalette(pa);




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
                fs.setFileName(QString("%1/dfge.ksg").arg(theaddress));
                QTextCodec *codec=QTextCodec::codecForName("UTF-8");
                QTextStream t(&fs);
                t.setCodec(codec);
                fs.open(QIODevice::WriteOnly|QIODevice::Text);
                t<<ui->lineEdit->text()+" "+ui->lineEdit_2->text()+" "+ui->lineEdit_3->text()+" "+ui->lineEdit_4->text()+" "+ui->lineEdit_5->text();
                fs.close();

                QMessageBox::about(this,"����","���ӳɹ�");
            }
            else
            {
                QMessageBox::about(this,"����","���ݿ�����ʧ��");
            }
        }
    }
    else
    {
        db.close();
        ui->pushButton_2->setText("����");
        QBrush br=QBrush(Qt::black,Qt::DiagCrossPattern); ;
        QPalette pa;
        pa.setBrush(QPalette::Text,br);
        ui->lineEdit->setPalette(pa);
        ui->lineEdit_2->setPalette(pa);
        ui->lineEdit_3->setPalette(pa);
        ui->lineEdit_4->setPalette(pa);
        ui->lineEdit_5->setPalette(pa);
        ui->pushButton->setEnabled(0);
        ui->lineEdit->setReadOnly(0);
        ui->lineEdit_2->setReadOnly(0);
        ui->lineEdit_3->setReadOnly(0);
        ui->lineEdit_4->setReadOnly(0);
        ui->lineEdit_5->setReadOnly(0);
        QMessageBox::about(this,"����","�Ѿ��Ͽ������ݿ������");
    }
}
