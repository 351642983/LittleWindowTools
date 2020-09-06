#ifndef WIDGETUPDATE_H
#define WIDGETUPDATE_H

#include <QWidget>
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
#include <QProcess>
#include <QTime>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QTextCodec>
#include <QTextStream>
#include <QLabel>
#include <QSystemTrayIcon>
#include "math.h"

namespace Ui {
class Widget;
}

class WidgetUpdate : public QWidget
{
    Q_OBJECT
    
public:
    explicit WidgetUpdate(QWidget *parent = 0);
    ~WidgetUpdate();
    QString getHtml(QString);
    bool isNetWorkOnline();
    void downloadnext();
//    QProgressBar *bar;
    QString getText();


private slots:
    void httpDowload();
    void httpDowloadFinished();
//    void updateProgress(qint64 ,qint64);
    void startDownload();
    void startCheck();
    void on_pushButton_2_clicked();
    void showHide(QSystemTrayIcon::ActivationReason reason);
private:
    QNetworkReply *avatorReply;
    QNetworkAccessManager *avatorManager;
    int g_thedownload[2];
    QFileInfo fileinfo;
    QStringList theversion;
    QFile *avatorFile;//ÎÄ¼þÖ¸Õë
    QString fileStr;
    QString current_date;
    int g_timerid;
    QSystemTrayIcon *tray;
//    QLabel *ll;
    Ui::Widget *ui;
protected:
    void timerEvent(QTimerEvent *);

};

#endif // WIDGET_H
