/********************************************************************************
** Form generated from reading UI file 'pastehtml.ui'
**
** Created: Thu Aug 22 10:52:39 2019
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASTEHTML_H
#define UI_PASTEHTML_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PasteHtml
{
public:
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_3;

    void setupUi(QWidget *PasteHtml)
    {
        if (PasteHtml->objectName().isEmpty())
            PasteHtml->setObjectName(QString::fromUtf8("PasteHtml"));
        PasteHtml->resize(720, 580);
        PasteHtml->setMinimumSize(QSize(720, 580));
        PasteHtml->setMaximumSize(QSize(720, 580));
        textEdit = new QTextEdit(PasteHtml);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 90, 691, 411));
        pushButton = new QPushButton(PasteHtml);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(200, 550, 75, 23));
        lineEdit = new QLineEdit(PasteHtml);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(180, 30, 521, 20));
        pushButton_2 = new QPushButton(PasteHtml);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(390, 550, 75, 23));
        label = new QLabel(PasteHtml);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 171, 20));
        label_2 = new QLabel(PasteHtml);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 70, 91, 16));
        label_3 = new QLabel(PasteHtml);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(493, 60, 81, 21));
        lineEdit_2 = new QLineEdit(PasteHtml);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(560, 60, 141, 20));
        label_4 = new QLabel(PasteHtml);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(380, 60, 111, 21));
        label_5 = new QLabel(PasteHtml);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 520, 131, 16));
        lineEdit_3 = new QLineEdit(PasteHtml);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(150, 520, 441, 20));
        pushButton_3 = new QPushButton(PasteHtml);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(610, 520, 75, 23));

        retranslateUi(PasteHtml);

        QMetaObject::connectSlotsByName(PasteHtml);
    } // setupUi

    void retranslateUi(QWidget *PasteHtml)
    {
        PasteHtml->setWindowTitle(QApplication::translate("PasteHtml", "Form", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("PasteHtml", "\345\274\200\345\247\213\347\210\254\345\217\226", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("PasteHtml", "\345\201\234\346\255\242\347\210\254\345\217\226", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PasteHtml", "\347\210\254\345\217\226\345\274\200\345\247\213\345\234\260\345\235\200(\344\270\215\346\224\257\346\214\201https)\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PasteHtml", "\347\275\221\351\241\265\345\233\276\347\211\207\345\210\227\350\241\250\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("PasteHtml", "\347\210\254\345\217\226\345\261\202\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        lineEdit_2->setText(QApplication::translate("PasteHtml", "-1", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("PasteHtml", "\357\274\210\350\257\245\345\212\237\350\203\275\345\267\262\347\273\217\345\274\203\347\224\250\357\274\211", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("PasteHtml", "\346\214\207\345\256\232\347\210\254\345\217\226\345\233\276\347\211\207\346\224\276\347\275\256\347\233\256\345\275\225\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("PasteHtml", "\351\200\211\346\213\251\346\226\207\344\273\266\345\244\271", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PasteHtml: public Ui_PasteHtml {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASTEHTML_H
