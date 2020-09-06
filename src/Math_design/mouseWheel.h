#ifndef MOUSEWHEEL_H
#define MOUSEWHEEL_H
#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QTextEdit>
#include <QSpinBox>
#include "windows.h"
#include "w32api.h"
#include "winable.h"
class mouseWheel : public QWidget
{
    Q_OBJECT

public:
    mouseWheel(QWidget *parent = 0);
    ~mouseWheel();
private:
    QPushButton *pb_hotkey;
    int findKey(QString);
    QLabel *jiange;
    QPushButton *returnMain;

private slots:
    void changeinfo();
    void window_return();
protected:
    void closeEvent(QCloseEvent *);
};

#endif // MOUSEWHEEL_H
