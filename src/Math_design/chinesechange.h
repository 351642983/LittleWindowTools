#ifndef CHINESECHANGE_H
#define CHINESECHANGE_H
#include "widget.h"
#include <QCheckBox>
#include <QLineEdit>
class chinesechange:
        public QWidget
{
    Q_OBJECT
public:
    chinesechange(QWidget *parent=0);
    ~chinesechange();
    /*static */bool In(wchar_t start, wchar_t end, wchar_t code);

    /*static */char Convert(int n);
    // 获取第一个汉字的首字母
    /*static */QString GetFirstLetter(const QString &src);
    // 获取所有汉字的首字母
    /*static */QString GetFirstLetters(const QString &src);
    // 获取一个汉字编码的汉语拼音
    /*static */QString GetPinyin(int code);
    // 获取所有汉字的汉语拼音
    /*static */QString GetPinyins(const QString& text);


private:
    QPushButton *fanghui;
    QLineEdit *lineselect;
    QPushButton *queren;
    QPushButton *pbxuanzhe;
    QLabel *lxuanzhe;
    QTextEdit *textedit;
    QPushButton *pbzhuanhuan;
    QCheckBox *shouzimu;
    QCheckBox *shouzimudaxie;
    QCheckBox *quanbudaxie;
    QCheckBox *kongge;
    QLabel *lquanbudaxie;
    QLabel *lkongge;
    QLabel *lshouzimu;
    QLabel *lshouzimudaxie;
    QLabel *wenbenshuru;
    QTextEdit *texteditshow;
    QPushButton *yinchang;
    bool g_yinchang;
    QString changetype(QString);
private slots:
    void yinchangshow();
    void zhuanhuanshow();
    void querenshow();
    void fanghuishow();
    void xuanzheshow();

};

#endif // CHINESECHANGE_H
