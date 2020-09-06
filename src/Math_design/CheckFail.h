#ifndef CHECKFAIL_H
#define CHECKFAIL_H

#include <QNetworkAccessManager>
//#include <QNetworkConfigurationManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QCoreApplication>
#include <QHostInfo>
#include <QMessageBox>
#include <QEventLoop>
#include <QFile>
#include <QDir>
#include <QProgressBar>
#include <QList>
#include "handoption.h"

class CheckFail :public QWidget
{
    Q_OBJECT
public:
    CheckFail(QWidget *parent=0);
    ~CheckFail();
    QString getHtml(QString);
    bool isNetWorkOnline();
    void downloadnext();
    QStringList httpList(QString,int);


    QString fileStr;
    QLabel *ll;
    QFile *avatorFile;//ÎÄ¼þÖ¸Õë
    QNetworkReply *avatorReply;
    QNetworkAccessManager *avatorManager;
    QProgressBar *bar;
    int g_thedownload[2];
    QFileInfo fileinfo;
    QStringList theversion;
    QList<int> DownloadAnalyze(QStringList);
    QList<int> analyzeList;
private:
    char *existDir;


private slots:
    void httpDowload();
    void httpDowloadFinished();
    void updateProgress(qint64 ,qint64);


};
#endif // CHECKFAIL_H
