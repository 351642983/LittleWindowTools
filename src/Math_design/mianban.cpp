#include "mianban.h"
#include "ui_mianban.h"
#include <QMessageBox>
#include <QDateTime>
mianban::mianban(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mianban)
{
    ui->setupUi(this);
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(on_pushButton_clicked()));
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("182.61.38.20");                        //127.0.0.1Ҳ��һ����,���ڱ��ص�ַ
    db.setPort(3306);
    db.setUserName("rdsroot");                                 //��½MYSQL���û���
    db.setPassword("aA13902766702");                              //���Լ���½������
    db.setDatabaseName("tools");                       //��½���ݿ������
    if(db.open())
    {
        QSqlQuery query;
        query.exec(QString("select * from liuyan where 1"));
        int g_num=1;
        while(query.next()) //����ִ��һ��next������ʾ����
        {
            ui->textEdit->append((QString("--------%1¥-------\n���֣�%2(%3)\n��������:%4\nʱ�䣺%5\n\n").arg(g_num).arg(query.value(1).toString()).arg(query.value(0).toString()).arg(query.value(2).toString()).arg(query.value(3).toString())));
            g_num++;
            QTextCursor cursor =ui->textEdit->textCursor();
            cursor.movePosition(QTextCursor::End);
            ui->textEdit->setTextCursor(cursor);
        }
        if(g_num==1)
        {
            ui->textEdit->setText("��ʱû���û����Ե���Ϣ");
        }
    }
}

mianban::~mianban()
{
    delete ui;
}

void mianban::on_pushButton_clicked()
{

    if(!zhanghao.isEmpty())
    {
        if(!ui->lineEdit->text().isEmpty())
        {
            QSqlQuery query;
            QDateTime current_date_time =QDateTime::currentDateTime();
            QString current_date =current_date_time.toString("yyyy.MM.dd");
            query.exec(QString("insert into liuyan values(\"%1\",\"%2\",\"%3\",\"%4\");").arg(zhanghao.at(0)).arg(zhanghao.at(1)).arg(ui->lineEdit->text()).arg(current_date));
            ui->textEdit->clear();
            ui->lineEdit->clear();


            query.exec(QString("select * from liuyan where 1"));
            int g_num=1;
            while(query.next()) //����ִ��һ��next������ʾ����
            {
                ui->textEdit->append((QString("------------------%1¥------------------\n���֣�%2(%3)\n��������:%4\nʱ�䣺%5\n\n").arg(g_num).arg(query.value(1).toString()).arg(query.value(0).toString()).arg(query.value(2).toString()).arg(query.value(3).toString())));
                g_num++;
                QTextCursor cursor =ui->textEdit->textCursor();
                cursor.movePosition(QTextCursor::End);
                ui->textEdit->setTextCursor(cursor);
            }
            if(g_num==1)
            {
                ui->textEdit->setText("��ʱû���û����Ե���Ϣ");
            }
            QTextCursor cursor =ui->textEdit->textCursor();
            cursor.movePosition(QTextCursor::End);
            ui->textEdit->setTextCursor(cursor);

        }
        else
        {
            QMessageBox::about(this,"����","�����������ϢΪ��,����д���ٷ���");
        }

    }
    else
    {
        QMessageBox::about(this,"����","��鵽�˺�Ϊ��¼,�Ѿ��ر��������");
        close();
    }
}
