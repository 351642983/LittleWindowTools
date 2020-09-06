#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Gamerefresh.h"
#include "g_Snakemath.h"

Gamerefresh::Gamerefresh(QGraphicsScene &scene, QObject *parent) :
    QObject(parent),
    scene(scene),
    snake(new g_snakemath(*this))
{
//    timer.start(1000/33);

//    Food *a1 = new Food(0, -50);
//    scene->addItem(a1);

//    scene->addItem(snake);

//    scene->installEventFilter(this);

//    pause();
}

//void Gamerefresh::pause()
//{
//    disconnect(&timer, SIGNAL(timeout()),
//               scene,  SLOT(advance()));
//}
//void Gamerefresh::resume()
//{
//    connect(&timer, SIGNAL(timeout()),
//            &scene, SLOT(advance()));
//}
Gamerefresh::~Gamerefresh()
{

}
