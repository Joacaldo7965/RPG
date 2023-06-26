#ifndef DEMON_H
#define DEMON_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsPixmapItem>
class Player;

class Demon : public QObject, public QGraphicsPixmapItem  {
    Q_OBJECT
public:
    Demon();
    void setMovementRange(int minX, int maxX, int minY, int maxY);
public slots:
    void move();
    void animate();
private:
    int dx_;
    int dy_;
    int minX_;
    int maxX_;
    int minY_;
    int maxY_;
    QList<QPixmap> frames;
    int currentIndex=0;
    float scale=1.0;
public:
    int width;
    int height;
};

#endif // DEMON_H
