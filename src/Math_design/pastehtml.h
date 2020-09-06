#ifndef PASTEHTML_H
#define PASTEHTML_H

#include <QWidget>
#include <QNetworkAccessManager>
//#include <QNetworkConfigurationManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHostInfo>
#include <QMessageBox>
#include <QEventLoop>
#include <QFile>
#include <QProgressBar>
#include <QFileInfo>
#include <QFileDialog>
namespace Ui {
class PasteHtml;
}

class PasteHtml : public QWidget
{
    Q_OBJECT
    
public:
    explicit PasteHtml(QWidget *parent = 0);
    ~PasteHtml();
    QStringList httpList(QString,int,QString);
    bool isNetWorkOnline();
    QString getHtml(QString,QString &);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();



private:
    Ui::PasteHtml *ui;
    bool g_outLoop;


    //尝试加入下载功能（步骤一）
    QFile *avatorFile;//文件指针
    QNetworkReply *avatorReply;
    QNetworkAccessManager *avatorManager;
    QProgressBar *bar;
    bool g_downloadFinish;
private slots:
    void httpDowload();
    void httpDowloadFinished();
    void on_pushButton_3_clicked();
};

#endif // PASTEHTML_H
