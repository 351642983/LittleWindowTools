/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created: Thu Aug 22 10:52:39 2019
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCalendarWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QCalendarWidget *calendarWidget;
    QLabel *label_2;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(400, 300);
        Form->setMinimumSize(QSize(400, 300));
        Form->setMaximumSize(QSize(400, 300));
        pushButton = new QPushButton(Form);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(70, 210, 261, 23));
        pushButton_2 = new QPushButton(Form);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(70, 250, 261, 23));
        label = new QLabel(Form);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(260, 20, 54, 12));
        calendarWidget = new QCalendarWidget(Form);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        calendarWidget->setGeometry(QRect(10, 10, 241, 171));
        label_2 = new QLabel(Form);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(280, 50, 91, 91));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(20);
        label_2->setFont(font);
        label_2->setScaledContents(false);
        label_2->setWordWrap(false);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Form", "\346\265\213\350\257\225\344\273\212\345\244\251\347\232\204\345\220\211\345\207\266", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Form", "\345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Form", "\344\273\212\346\227\245\350\277\220\345\212\277\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Form", "\345\260\232\346\234\252\346\265\213", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
