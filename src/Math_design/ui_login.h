/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created: Thu Aug 22 10:52:39 2019
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;

    void setupUi(QWidget *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QString::fromUtf8("login"));
        login->resize(310, 182);
        login->setMinimumSize(QSize(310, 182));
        login->setMaximumSize(QSize(310, 182));
        label = new QLabel(login);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 30, 54, 12));
        label_2 = new QLabel(login);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 70, 54, 12));
        pushButton = new QPushButton(login);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 140, 75, 23));
        pushButton_2 = new QPushButton(login);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(170, 140, 75, 23));
        lineEdit = new QLineEdit(login);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(100, 30, 151, 20));
        lineEdit_2 = new QLineEdit(login);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(100, 70, 151, 20));
        lineEdit_2->setEchoMode(QLineEdit::Password);
        checkBox = new QCheckBox(login);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(70, 110, 71, 16));
        checkBox->setAcceptDrops(false);
        checkBox->setChecked(true);
        checkBox_2 = new QCheckBox(login);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(160, 110, 71, 16));
        checkBox_2->setChecked(true);

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QWidget *login)
    {
        login->setWindowTitle(QApplication::translate("login", "\347\224\250\346\210\267\347\231\273\345\275\225", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("login", "\347\224\250\346\210\267\350\264\246\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("login", "\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("login", "\347\231\273\345\275\225", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("login", "\346\263\250\345\206\214", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("login", "\350\256\260\344\275\217\350\264\246\345\217\267", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("login", "\350\256\260\344\275\217\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
