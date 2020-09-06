#ifndef FILELOCK_H
#define FILELOCK_H

#include <QWidget>
#include <QFile>
#include <QDataStream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextCodec>
#include <QTextStream>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QComboBox>
#include <QFileInfo>
#include <QDir>
#include <QFileDialog>
#include <QValidator>

class filelock:public QWidget
{
    Q_OBJECT
public:
    filelock(QWidget *parent=0);
    ~filelock();

private:
    QPushButton *button[3];
    QLineEdit *line[2];
    QLabel *word[3];
    QComboBox *cbox;

private slots:
    void slectfile();
//    void slectoutfile();
    void lockhandle();
    void handleclose();

};

#endif // FILELOCK_H
