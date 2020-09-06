#ifndef BARWIDGET_H
#define BARWIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QCloseEvent>
class BarWidget:public QWidget
{
    Q_OBJECT
public:
    BarWidget(QWidget *parent=0);
    ~BarWidget();

    bool g_tixin;
    QSystemTrayIcon *tray;
public slots:
signals:
    void pressA(); //alt+q–≈∫≈

protected:
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent *);

};

#endif // BARWIDGET_H
