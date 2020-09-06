/********************************************************************************
** Form generated from reading UI file 'zcwidget.ui'
**
** Created: Thu Aug 22 10:52:39 2019
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZCWIDGET_H
#define UI_ZCWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Zcwidget
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *pushButton;
    QLabel *label_8;

    void setupUi(QWidget *Zcwidget)
    {
        if (Zcwidget->objectName().isEmpty())
            Zcwidget->setObjectName(QString::fromUtf8("Zcwidget"));
        Zcwidget->resize(373, 243);
        Zcwidget->setMinimumSize(QSize(373, 243));
        Zcwidget->setMaximumSize(QSize(400, 243));
        label = new QLabel(Zcwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(53, 30, 51, 20));
        label_2 = new QLabel(Zcwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 60, 54, 12));
        label_3 = new QLabel(Zcwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 90, 54, 12));
        label_4 = new QLabel(Zcwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 120, 54, 12));
        lineEdit = new QLineEdit(Zcwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(110, 30, 181, 20));
        lineEdit_2 = new QLineEdit(Zcwidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(110, 60, 181, 20));
        label_5 = new QLabel(Zcwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(50, 160, 241, 16));
        lineEdit_3 = new QLineEdit(Zcwidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(110, 90, 181, 20));
        lineEdit_3->setEchoMode(QLineEdit::Password);
        lineEdit_4 = new QLineEdit(Zcwidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(110, 120, 181, 20));
        lineEdit_4->setEchoMode(QLineEdit::Password);
        label_6 = new QLabel(Zcwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(300, 30, 71, 16));
        label_7 = new QLabel(Zcwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(300, 60, 71, 16));
        pushButton = new QPushButton(Zcwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(150, 200, 75, 23));
        label_8 = new QLabel(Zcwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(50, 180, 191, 16));

        retranslateUi(Zcwidget);

        QMetaObject::connectSlotsByName(Zcwidget);
    } // setupUi

    void retranslateUi(QWidget *Zcwidget)
    {
        Zcwidget->setWindowTitle(QApplication::translate("Zcwidget", "\346\263\250\345\206\214\350\264\246\345\217\267", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Zcwidget", "\347\224\250\346\210\267\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Zcwidget", "\346\263\250\345\206\214\350\264\246\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Zcwidget", "\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Zcwidget", "\351\207\215\345\244\215\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Zcwidget", "\345\257\206\347\240\201\345\217\252\350\203\275\345\241\253\345\206\2316-15\344\270\252\346\225\260\345\255\227\345\222\214\345\255\227\346\257\215\347\232\204\347\273\204\345\220\210", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Zcwidget", "*\347\224\250\346\210\267\345\220\215\345\255\230\345\234\250", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Zcwidget", "*\350\264\246\345\217\267\345\255\230\345\234\250", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Zcwidget", "\346\263\250\345\206\214", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Zcwidget", "\346\263\250\345\206\214\347\232\204\350\264\246\345\217\267\350\264\246\345\217\267\345\217\252\350\203\275\346\230\257\347\272\257\346\225\260\345\255\227\347\273\204\345\220\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Zcwidget: public Ui_Zcwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZCWIDGET_H
