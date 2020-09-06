#ifndef DAYPASS_H
#define DAYPASS_H
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QProcess>
#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class daypass:public QWidget
{
    Q_OBJECT
public:
    daypass(QWidget *parent=0);
    ~daypass();
private:
    QString getHtml(QString url);
    QTextEdit *textedit;
    bool isNetWorkOnline();

};

#endif // DAYPASS_H
