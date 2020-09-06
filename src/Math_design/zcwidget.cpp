#include "zcwidget.h"
#include "ui_zcwidget.h"

Zcwidget::Zcwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Zcwidget)
{
    ui->setupUi(this);

    ui->label_6->hide();
    ui->label_7->hide();
    QRegExp reg("[0-9]{0,15}"),reg_1("([0-9a-zA-Z)]){0,15}"),reg_2("[^ `#]{0,15}");
    QValidator *va=new QRegExpValidator(reg,ui->lineEdit_2);
    QValidator *va1=new QRegExpValidator(reg_1,ui->lineEdit_3);
    QValidator *va2=new QRegExpValidator(reg_2,ui->lineEdit);
    ui->lineEdit->setValidator(va2);
    ui->lineEdit_2->setValidator(va);
    ui->lineEdit_3->setValidator(va1);
    ui->lineEdit_4->setValidator(va1);

}

Zcwidget::~Zcwidget()
{
    delete ui;
}

void Zcwidget::on_pushButton_clicked()
{
    if(!ui->lineEdit->text().isEmpty())
    {
        if(!ui->lineEdit->text().contains(QRegExp("[ `#]")))
        {
            if(ui->lineEdit_2->text().length()>=8)
            {
                if(!ui->lineEdit_3->text().isEmpty()&&!ui->lineEdit_4->text().isEmpty())
                {
                    if(ui->lineEdit_3->text().length()>=6)
                    {
                        if(ui->lineEdit_3->text()==ui->lineEdit_4->text())
                        {
                            db = QSqlDatabase::addDatabase("QMYSQL");
                            db.setHostName("182.61.38.20");                        //127.0.0.1Ҳ��һ����,���ڱ��ص�ַ
                            db.setPort(3306);
                            db.setUserName("rdsroot");                                 //��½MYSQL���û���
                            db.setPassword("aA13902766702");                              //���Լ���½������
                            db.setDatabaseName("tools");                       //��½���ݿ������
                            if(db.open())
                            {
                                QSqlQuery query;
                                query.exec(QString("select name from zhuce where name=\"%1\";").arg(ui->lineEdit->text()));
                                query.first();
                                if(query.value(0).toString()!=ui->lineEdit->text())
                                {
                                    query.exec(QString("select zhanghao from zhuce where zhanghao=\"%1\";").arg(ui->lineEdit_2->text()));
                                    query.first();
                                    if(query.value(0).toString()!=ui->lineEdit_2->text())
                                    {
                                        ook=(QString("%1 %2 %3").arg(ui->lineEdit_2->text()).arg(ui->lineEdit->text()).arg(ui->lineEdit_3->text())).split(" ");
                                        query.exec(QString("insert into zhuce values(\"%1\",\"%2\",\"%3\");").arg(ui->lineEdit_2->text()).arg(ui->lineEdit->text()).arg(ui->lineEdit_3->text()));
                                        QMessageBox::about(NULL,"����","ע��ɹ�!");
                                        close();

                                    }
                                    else
                                    {
                                        QMessageBox::about(NULL,"����","ע����˺��Ѿ�����,�����»���ע����˺�");
                                    }
                                }
                                else
                                {
                                    QMessageBox::about(NULL,"����","ע����û������Ѿ�����,�����»���ע�������");
                                }
                            }
                            else
                            {
                                QMessageBox::about(NULL,"����","����������ʧ��,���������Ƿ���������");
                            }
                        }
                        else
                        {
                            QMessageBox::about(NULL,"����","���ε����벻���,����������");
                        }
                    }
                    else
                    {
                        QMessageBox::about(NULL,"����","�����λ�����������λ��");
                    }
                }
                else
                {
                    QMessageBox::about(NULL,"����","��һ���ߵڶ��ε����벻��Ϊ��");
                }
            }
            else
            {
                QMessageBox::about(NULL,"����","ע����˺ű�����ڻ����8λ��");
            }
        }
        else
        {
            QMessageBox::about(NULL,"����","�û����ֲ��ܰ���# `��Щ����");
        }

    }
    else
    {
        QMessageBox::about(NULL,"����","�û�������Ϊ��");
    }
}
