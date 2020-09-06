/********************************************************************************
** Form generated from reading UI file 'sqlhandle.ui'
**
** Created: Thu Aug 22 10:52:39 2019
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SQLHANDLE_H
#define UI_SQLHANDLE_H

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

class Ui_sqlhandle
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton_2;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lineEdit_5;

    void setupUi(QWidget *sqlhandle)
    {
        if (sqlhandle->objectName().isEmpty())
            sqlhandle->setObjectName(QString::fromUtf8("sqlhandle"));
        sqlhandle->resize(518, 408);
        sqlhandle->setMinimumSize(QSize(518, 408));
        sqlhandle->setMaximumSize(QSize(518, 408));
        label = new QLabel(sqlhandle);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 80, 54, 12));
        lineEdit = new QLineEdit(sqlhandle);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(100, 80, 151, 20));
        label_2 = new QLabel(sqlhandle);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 40, 54, 20));
        lineEdit_2 = new QLineEdit(sqlhandle);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(100, 40, 151, 20));
        label_3 = new QLabel(sqlhandle);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(260, 40, 54, 16));
        lineEdit_3 = new QLineEdit(sqlhandle);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(300, 40, 141, 20));
        textEdit = new QTextEdit(sqlhandle);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(70, 170, 421, 181));
        pushButton = new QPushButton(sqlhandle);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(150, 370, 201, 23));
        label_4 = new QLabel(sqlhandle);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(260, 80, 54, 12));
        lineEdit_4 = new QLineEdit(sqlhandle);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(300, 80, 141, 20));
        lineEdit_4->setEchoMode(QLineEdit::Password);
        pushButton_2 = new QPushButton(sqlhandle);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(300, 120, 141, 23));
        label_5 = new QLabel(sqlhandle);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 170, 54, 12));
        label_6 = new QLabel(sqlhandle);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(40, 120, 54, 12));
        lineEdit_5 = new QLineEdit(sqlhandle);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(100, 120, 151, 20));

        retranslateUi(sqlhandle);

        QMetaObject::connectSlotsByName(sqlhandle);
    } // setupUi

    void retranslateUi(QWidget *sqlhandle)
    {
        sqlhandle->setWindowTitle(QApplication::translate("sqlhandle", "SQL\350\277\234\347\250\213\350\277\236\346\216\245", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("sqlhandle", "\347\224\250\346\210\267\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("sqlhandle", "IP\345\234\260\345\235\200\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("sqlhandle", "\347\253\257\345\217\243\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("sqlhandle", "\346\211\247\350\241\214\345\221\275\344\273\244", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("sqlhandle", "\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("sqlhandle", "\350\277\236\346\216\245", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("sqlhandle", "\345\221\275\344\273\244\357\274\232", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("sqlhandle", "\345\272\223\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class sqlhandle: public Ui_sqlhandle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SQLHANDLE_H
