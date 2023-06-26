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
private:
    int dx_;
    int dy_;
    int minX_;
    int maxX_;
    int minY_;
    int maxY_;
};

#endif // DEMON_H
