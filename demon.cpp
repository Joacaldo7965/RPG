#include "demon.h"
#include "qapplication.h"
#include "qgraphicsscene.h"
#include "attack.h"
#include "character.h"
#include <QPixmap>
#include <QTimer>
#include <QRandomGenerator>
#include <typeinfo>

Demon::Demon() : dx_(0), dy_(0) {
    setPixmap(QPixmap(":/images/demon.png"));
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
    if (dx_ == 0 && dy_ == 0) {
        dx_ = QRandomGenerator::global()->bounded(-10, 15);
        dy_ = QRandomGenerator::global()->bounded(-10, 15);
    }
    int newX = x() + dx_;
    int newY = y() + dy_;
    if (newX < minX_ || newX > maxX_ || newY < minY_ || newY > maxY_) {
        dx_ = -dx_;
        dy_ = -dy_;
    } else {
        setPos(newX, newY);
    }
    QList<QGraphicsItem*> collidingItemsList = collidingItems();
    for (QGraphicsItem* item : collidingItemsList) {
        if (typeid(*item) == typeid(Attack)) {
            scene()->removeItem(item);
            scene()->removeItem(this);
            delete item;
            delete this;
            return;
        }
    }

    QList<QGraphicsItem*> playerCollidingItemsList = collidingItems(Qt::IntersectsItemShape);
    for (QGraphicsItem* item : playerCollidingItemsList) {
        if (typeid(*item) == typeid(Personaje)) {
            QApplication::quit();
            return;
        }
    }
}
