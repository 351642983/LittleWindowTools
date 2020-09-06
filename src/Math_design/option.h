#ifndef OPTION_H
#define OPTION_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextCodec>
#include <QTextStream>
#include <QSpinBox>
#include <QCheckBox>
#include <QLabel>
#include <QFile>
#include <QDir>

class option:public QDialog
{
    Q_OBJECT
public:
    option(QWidget *parent=0);
    ~option();
    int g_speed;
    bool g_lock;
    QSpinBox *sb[2];
    QCheckBox *cb;

private:
    QLabel *lb[3];
    QPushButton *bt[3];


private slots:
    void writeyc();
    void writey();

};

#endif // OPTION_H
