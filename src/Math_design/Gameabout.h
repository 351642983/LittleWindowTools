//建立关于的对画框类头文件,显示关于本人的信息还有石家庄铁道大学等信息
#ifndef GAMEABOUT_H
#define GAMEABOUT_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>
//定义Label要显示的行数
#define LINE_NUM 3

class Gameabout:public QDialog
{
    Q_OBJECT
public:
    Gameabout();
    ~Gameabout();
    QStringList httpList(QString html,int max);
private:
    QString getHtml(QString url);



};

#endif // GAMEABOUT_H
