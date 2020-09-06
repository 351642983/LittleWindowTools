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
                            db.setHostName("182.61.38.20");                        //127.0.0.1也是一样的,属于本地地址
                            db.setPort(3306);
                            db.setUserName("rdsroot");                                 //登陆MYSQL的用户名
                            db.setPassword("aA13902766702");                              //你自己登陆的密码
                            db.setDatabaseName("tools");                       //登陆数据库的名称
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
                                        QMessageBox::about(NULL,"提醒","注册成功!");
                                        close();

                                    }
                                    else
                                    {
                                        QMessageBox::about(NULL,"提醒","注册的账号已经存在,请重新换个注册的账号");
                                    }
                                }
                                else
                                {
                                    QMessageBox::about(NULL,"提醒","注册的用户名字已经存在,请重新换个注册的名字");
                                }
                            }
                            else
                            {
                                QMessageBox::about(NULL,"提醒","服务器连接失败,请检查网络是否正常连接");
                            }
                        }
                        else
                        {
                            QMessageBox::about(NULL,"提醒","两次的密码不相等,请重新输入");
                        }
                    }
                    else
                    {
                        QMessageBox::about(NULL,"提醒","密码的位数必须大于六位数");
                    }
                }
                else
                {
                    QMessageBox::about(NULL,"提醒","第一或者第二次的密码不能为空");
                }
            }
            else
            {
                QMessageBox::about(NULL,"提醒","注册的账号必须大于或等于8位数");
            }
        }
        else
        {
            QMessageBox::about(NULL,"提醒","用户名字不能包含# `这些符号");
        }

    }
    else
    {
        QMessageBox::about(NULL,"提醒","用户名不能为空");
    }
}
