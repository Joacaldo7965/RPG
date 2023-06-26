#include "demon.h"
#include "attack.h"
#include "player.h"
#include "game.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <QRandomGenerator>
#include <typeinfo>

extern Game *game;

Demon::Demon()
    : dx_(QRandomGenerator::global()->bounded(-10, 15)),
      dy_(QRandomGenerator::global()->bounded(-10, 15)),
      scale(1.6)
{
    width = (int) (64 * scale);
    height = (int) (59 * scale);

    setPixmap(QPixmap(":/res/images/demon/demon_tile000.png").scaled(width, height));
    frames.append(QPixmap(":/res/images/demon/demon_tile000.png").scaled(width, height));
    frames.append(QPixmap(":/res/images/demon/demon_tile001.png").scaled(width, height));
    frames.append(QPixmap(":/res/images/demon/demon_tile002.png").scaled(width, height));
    frames.append(QPixmap(":/res/images/demon/demon_tile003.png").scaled(width, height));
    frames.append(QPixmap(":/res/images/demon/demon_tile004.png").scaled(width, height));
    frames.append(QPixmap(":/res/images/demon/demon_tile005.png").scaled(width, height));
    frames.append(QPixmap(":/res/images/demon/demon_tile006.png").scaled(width, height));

    setTransformOriginPoint(boundingRect().width()/2, boundingRect().height()/2);

    QTimer *animTimer = new QTimer(this);
    connect(animTimer, SIGNAL(timeout()), this, SLOT(animate()));
    animTimer->start(100);

    // Periodic movement
    QTimer *moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    moveTimer->start(100);

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
            //game->score->increase(10);
            game->killDemon();

            scene()->removeItem(item);
            scene()->removeItem(this);
            delete item;
            delete this;
            return;
        } else if (typeid(*item) == typeid(Player)) {
            //qDebug() << item;
            game->damagePlayer(1); // TODO: Get damage from item. ie: Enemy damage
            return;
        }
    }
}

void Demon::animate(){
    currentIndex = (currentIndex + 1) % frames.size();
    setPixmap(frames[currentIndex]);
}
