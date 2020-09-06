#ifndef GAMEREFRESH_H
#define GAMEREFRESH_H

#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>

class g_snakemath;

class Gamerefresh:public QObject
{
    Q_OBJECT
public:
    Gamerefresh(QGraphicsScene &scene, QObject *parent=0);
    ~Gamerefresh();
    //void pause();
private:

    QTimer timer;
    QGraphicsScene &scene;
    g_snakemath *snake;
};


#endif // GAMEREFRESH_H
