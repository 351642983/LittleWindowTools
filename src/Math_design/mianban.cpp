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
    db.setHostName("182.61.38.20");                        //127.0.0.1也是一样的,属于本地地址
    db.setPort(3306);
    db.setUserName("rdsroot");                                 //登陆MYSQL的用户名
    db.setPassword("aA13902766702");                              //你自己登陆的密码
    db.setDatabaseName("tools");                       //登陆数据库的名称
    if(db.open())
    {
        QSqlQuery query;
        query.exec(QString("select * from liuyan where 1"));
        int g_num=1;
        while(query.next()) //至少执行一遍next才能显示东西
        {
            ui->textEdit->append((QString("--------%1楼-------\n名字：%2(%3)\n留言内容:%4\n时间：%5\n\n").arg(g_num).arg(query.value(1).toString()).arg(query.value(0).toString()).arg(query.value(2).toString()).arg(query.value(3).toString())));
            g_num++;
            QTextCursor cursor =ui->textEdit->textCursor();
            cursor.movePosition(QTextCursor::End);
            ui->textEdit->setTextCursor(cursor);
        }
        if(g_num==1)
        {
            ui->textEdit->setText("暂时没有用户留言的信息");
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
            while(query.next()) //至少执行一遍next才能显示东西
            {
                ui->textEdit->append((QString("------------------%1楼------------------\n名字：%2(%3)\n留言内容:%4\n时间：%5\n\n").arg(g_num).arg(query.value(1).toString()).arg(query.value(0).toString()).arg(query.value(2).toString()).arg(query.value(3).toString())));
                g_num++;
                QTextCursor cursor =ui->textEdit->textCursor();
                cursor.movePosition(QTextCursor::End);
                ui->textEdit->setTextCursor(cursor);
            }
            if(g_num==1)
            {
                ui->textEdit->setText("暂时没有用户留言的信息");
            }
            QTextCursor cursor =ui->textEdit->textCursor();
            cursor.movePosition(QTextCursor::End);
            ui->textEdit->setTextCursor(cursor);

        }
        else
        {
            QMessageBox::about(this,"提醒","发表的留言信息为空,请填写后再发表");
        }

    }
    else
    {
        QMessageBox::about(this,"提醒","检查到账号为登录,已经关闭留言面板");
        close();
    }
}
