#ifndef SUSWIDGET_H
#define SUSWIDGET_H

#include <QtGui/QWidget>
#include <QDateTime>
#include <QtGui/QLineEdit>
#include <QtCore/QTextCodec>
#include <QtGui/QApplication>
#include <QDesktopWidget>

#ifndef    REMAIN_TIME
#define   REMAIN_TIME            0
#endif

#ifndef    TO_SHUTDOWN
#define   TO_SHUTDOWN         1
#endif

#ifndef    SHUTDOWN_ERROR
#define   SHUTDOWN_ERROR  2
#endif

class SusWidget : public QWidget
{
    Q_OBJECT

public:
    SusWidget(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~SusWidget();

private:
    QLineEdit  *timeEdit;

public slots:
    void SetRemainTime(const QTime &time, int type);
};

#endif // SUSWIDGET_H
