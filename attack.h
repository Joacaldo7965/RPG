#ifndef ATTACK_H
#define ATTACK_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Attack : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Attack();
    void setDirection(int dx, int dy);
public slots:
    void move();
private:
    int dx_;
    int dy_;
};

#endif // ATTACK_H
