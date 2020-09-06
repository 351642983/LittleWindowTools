#ifndef RANSL_H
#define RANSL_H

#include <QWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QListWidget>
#include <QCheckBox>
#include <QMessageBox>
#include <QLabel>
#include <QLCDNumber>
#include <QTextEdit>
#include <QTextCursor>
#include <QTime>
#include <QTimer>

class ransl:public QWidget
{
    Q_OBJECT
public:
    ransl(QWidget *parent=0);
    ~ransl();

private:
    QPushButton *bt[4];
    QListWidget *wt;
    QSpinBox *sb[2];
    QLabel *word[5];
    QTimer *timer;
    QLCDNumber *lcd;
    void textshow();
    QString infoshow;
    QTextEdit *texte;
    QCheckBox *cb;
    QList<int> numlist;
    bool g_start;
    int g_num;
    int random_num(int x,int y);
private slots:
    void changemode(bool);
    void refresh();
    void thebegin();
    void chouyi();
    void chouall();
    void closehandle();

};

#endif // RANSL_H
