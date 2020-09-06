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
    // ��ȡ��һ�����ֵ�����ĸ
    /*static */QString GetFirstLetter(const QString &src);
    // ��ȡ���к��ֵ�����ĸ
    /*static */QString GetFirstLetters(const QString &src);
    // ��ȡһ�����ֱ���ĺ���ƴ��
    /*static */QString GetPinyin(int code);
    // ��ȡ���к��ֵĺ���ƴ��
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
