#include "attack.h"
#include "qgraphicsscene.h"
#include <QTimer>

Attack::Attack() : dx_(0), dy_(0) {
    setPixmap(QPixmap(":/res/images/effects/fire.png"));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(100);
}

void Attack::setDirection(int dx, int dy) {
    dx_ = dx;
    dy_ = dy;
}

void Attack::move() {
    setPos(x() + dx_, y() + dy_);
    if (pos().y()+ 20<0 || pos().y()+ 20>640 || pos().x()+ 20<0 || pos().x()+ 20>640){
        scene()->removeItem(this);
        delete this;
    }
}
