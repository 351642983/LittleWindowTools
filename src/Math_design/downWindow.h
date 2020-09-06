#ifndef DOWNWINDOW_H
#define DOWNWINDOW_H
#include <QWidget>

class downWindow:public QWidget
{
    Q_OBJECT
public:
    downWindow(QWidget *parent=0):QWidget(parent){}
    ~downWindow(){};

};

#endif // DOWNWINDOW_H
