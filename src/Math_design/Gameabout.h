//�������ڵĶԻ�����ͷ�ļ�,��ʾ���ڱ��˵���Ϣ����ʯ��ׯ������ѧ����Ϣ
#ifndef GAMEABOUT_H
#define GAMEABOUT_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>
//����LabelҪ��ʾ������
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
