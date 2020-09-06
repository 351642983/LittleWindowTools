#ifndef CHANGECE_H
#define CHANGECE_H

#include <QWidget>
#include <QFile>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>
#include <QTextCursor>


class changece:public QWidget
{
    Q_OBJECT
public:
    changece(QWidget *parent=0);
    ~changece();
private:
    QLineEdit *linee;
    QPushButton *button[3];
    QLabel *word;
    QTextEdit *texte;
    QString infoshow;
    void textshow();

private slots:
    void showtext();
    void selectDir();
    void handleclose();
};

#endif // CHANGECE_H
