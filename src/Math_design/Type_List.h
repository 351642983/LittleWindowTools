#ifndef TYPE_LIST_H
#define TYPE_LIST_H

#include <QButton>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // TYPE_LIST_H
