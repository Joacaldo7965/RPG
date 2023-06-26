#include "character.h"
#include <QKeyEvent>
#include "attack.h"
#include "demon.h"
#include "qapplication.h"
#include <QGraphicsScene>
#include <QDebug>

Personaje::Personaje(int numShots) {
    setPixmap(QPixmap(":/images/swmg.png"));
    numDisparos_ = numShots;
}

void Personaje::keyPressEvent(QKeyEvent *event) {
    int dx = 0;
    int dy = 0;

    if (event->key() == Qt::Key_A && pos().x()-20>0) {
        dx = -20;
    } else if (event->key() == Qt::Key_D && pos().x()+48<620) {
        dx = 20;
    } else if (event->key() == Qt::Key_W && pos().y()-100>0) {
        dy = -20;
    } else if (event->key() == Qt::Key_S && pos().y()+80<620) {
        dy = 20;
    } else if (event->key() == Qt::Key_Up) {
        shoot(0, -20);
    } else if (event->key() == Qt::Key_Left) {
        shoot(-20, 0);
    } else if (event->key() == Qt::Key_Down) {
        shoot(0, 20);
    } else if (event->key() == Qt::Key_Right) {
        shoot(20, 0);
    }
    setPos(x() + dx, y() + dy);
}

void Personaje::shoot(int dx, int dy) {
    if (numDisparos_ > 0) {
        Attack *attack = new Attack();
        attack->setPos(x(), y());
        attack->setDirection(dx, dy);
        scene()->addItem(attack);
        restarDisparo();
    }
}
void Personaje::verificarFinJuego() {
    if (numDisparos_ == 0) {
        QList<QGraphicsItem*> demons = scene()->items();
        for (QGraphicsItem* item : demons) {
            if (typeid(*item) == typeid(Demon)) {
                QApplication::quit();
                return; // Aún hay demonios, no se cierra el juego
            }
        }
    }
}
void Personaje::restarDisparo() {
    numDisparos_--;
    verificarFinJuego(); // Verificar si se debe cerrar el juego
}

void Personaje::setStartPosition(int screenCenterX, int screenCenterY) {
    int xPos = screenCenterX - pixmap().width() / 2;
    int yPos = screenCenterY - pixmap().height() / 2;
    setPos(xPos, yPos);
}

