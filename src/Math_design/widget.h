//����Ϸ�㷨���ܵĴ���ͷ�ļ�,���Ը���ִ�м���ҳ���չʾ
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QTextEdit>
#include <QMenuBar>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QKeyEvent>
#include "BarWidget.h"
//������Ϸ���͵���Ŀ


class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    //���ڴ���ѡ�����Ϸģʽ�ı���
    int type;
    QLabel *Ll;
//    QLabel *tixin;
    //����һ������,���ڿ�ʼ����ʱѡ���ĳһ���͵���Ϸ��Ϸ
    QListWidget *Lw;
    QPushButton *B_select;
    QPushButton *B_about;
    QTextEdit *textedit;
    //����һ�������ڽ���,������ʾ���ණ��
    BarWidget *mainwindow;
    //QMenuBar *bar;
    void del_kongjian(int);
    QSystemTrayIcon *tray;
//    QPushButton *dl;
    QStringList thelist;
    QTimer *starttime;
//protected:
//    void keyPressEvent(QKeyEvent *);



private slots:
    void showSay();
    void showType();
    void showabout();
    void startgame();
    void textshow(QListWidgetItem*);
    void showHide(QSystemTrayIcon::ActivationReason);
    void closePro();
    void denglu();
    void checkzhanghao();
    void relate();  //���Ӵ��ںͽ������ܣ�����
    void checkFail();



};

#endif // WIDGET_H
