#ifndef DDIALOG_H
#define DDIALOG_H


class Ddialog:public QDialog
{
    Q_OBJECT

public:
    explicit Ddialog(QWidget *parent = 0);
    ~Ddialog();

};

#endif // DDIALOG_H
