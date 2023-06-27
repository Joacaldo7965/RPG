#ifndef DEMON_H
#define DEMON_H

#include "game.h"
#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsPixmapItem>

const int MAX_SPEED = 15;
const int MIN_SPEED = -15;

class Demon : public QObject, public QGraphicsPixmapItem  {
    Q_OBJECT
public:
    Demon(Rectangle collisionBox);
private:
    void initPosition(Rectangle collisionBox);
    void initAnimation();
    void initMovement();
    int isFacingRight();
public slots:
    void move();
    void animate();
private:
    int dx_;
    int dy_;

    QList<QPixmap> frames;
    int currentIndex=0;

    float scale=1.0;
public:
    int width;
    int height;
};

#endif // DEMON_H
