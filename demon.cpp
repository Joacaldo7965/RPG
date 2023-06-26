#include "demon.h"
#include "attack.h"
#include "player.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <QRandomGenerator>
#include <typeinfo>

Demon::Demon()
    : dx_(QRandomGenerator::global()->bounded(-10, 15)),
      dy_(QRandomGenerator::global()->bounded(-10, 15))
{
    setPixmap(QPixmap(":/res/images/demon/demon.png"));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(100);

}

void Demon::setMovementRange(int minX, int maxX, int minY, int maxY) {
    minX_ = minX;
    maxX_ = maxX;
    minY_ = minY;
    maxY_ = maxY;
}

void Demon::move() {
    // Movement
    int newX = x() + dx_;
    int newY = y() + dy_;
    if (newX < minX_ || newX > maxX_){
        dx_ = -dx_;
    }
    if(newY < minY_ || newY > maxY_) {
        dy_ = -dy_;
    }
    setPos(newX, newY);

    // Collisions
    QList<QGraphicsItem*> collidingItemsList = collidingItems();

    for (QGraphicsItem* item : collidingItemsList) {
        if (typeid(*item) == typeid(Attack)) {
            scene()->removeItem(item);
            scene()->removeItem(this);
            delete item;
            delete this;
            return;
        } else if (typeid(*item) == typeid(Player)) {
            QApplication::quit();
            return;
        }
    }
}
