#ifndef DEMON_H
#define DEMON_H

#include "game.h"
#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsPixmapItem>


class Demon : public QObject, public QGraphicsPixmapItem  {
    Q_OBJECT
public:
    Demon(Rectangle collisionBox, int minSpeed, int maxSpeed);
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
    int minSpeed;
    int maxSpeed;

    QList<QPixmap> frames;
    int currentIndex=0;

    float scale=1.0;
public:
    int width;
    int height;
};

#endif // DEMON_H
