/********************************************************************************
** Form generated from reading UI file 'mianban.ui'
**
** Created: Thu Aug 22 10:52:39 2019
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MIANBAN_H
#define UI_MIANBAN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mianban
{
public:
    QGroupBox *groupBox;
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QLineEdit *lineEdit;

    void setupUi(QWidget *mianban)
    {
        if (mianban->objectName().isEmpty())
            mianban->setObjectName(QString::fromUtf8("mianban"));
        mianban->resize(405, 574);
        mianban->setMinimumSize(QSize(405, 574));
        mianban->setMaximumSize(QSize(405, 574));
        groupBox = new QGroupBox(mianban);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 30, 341, 491));
        groupBox->setLayoutDirection(Qt::LeftToRight);
        groupBox->setAlignment(Qt::AlignCenter);
        textEdit = new QTextEdit(groupBox);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 30, 321, 451));
        textEdit->setStyleSheet(QString::fromUtf8("background-color:rgba(0,0,0,0);border:1px groove gray;border-radius:5px;padding:2px 4px;"));
        textEdit->setReadOnly(true);
        pushButton = new QPushButton(mianban);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(300, 540, 75, 23));
        lineEdit = new QLineEdit(mianban);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(40, 540, 251, 20));

        retranslateUi(mianban);

        QMetaObject::connectSlotsByName(mianban);
    } // setupUi

    void retranslateUi(QWidget *mianban)
    {
        mianban->setWindowTitle(QApplication::translate("mianban", "\347\225\231\350\250\200", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("mianban", "\347\225\231\350\250\200\351\235\242\346\235\277", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("mianban", "\345\217\221\350\241\250", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mianban: public Ui_mianban {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MIANBAN_H
