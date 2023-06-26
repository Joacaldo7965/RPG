#include "player.h"
#include "game.h"
#include "attack.h"
#include "demon.h"
#include <QApplication>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>

extern Game *game;

Player::Player(int numShots) {
    setPixmap(QPixmap(":/res/images/player/swmg.png"));
    nShots_ = numShots;
}

void Player::keyPressEvent(QKeyEvent *event) {
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

void Player::shoot(int dx, int dy) {
    if (nShots_ > 0) {
        Attack *attack = new Attack();
        attack->setPos(x(), y());
        attack->setDirection(dx, dy);
        scene()->addItem(attack);
        decreaseShot();
    }
}

void Player::decreaseShot() {
    nShots_--;
    game->decreaseShot(1);
}

int Player::getShots(){
    return nShots_;
}

void Player::setStartPosition(int screenCenterX, int screenCenterY) {
    int xPos = screenCenterX - pixmap().width() / 2;
    int yPos = screenCenterY - pixmap().height() / 2;
    setPos(xPos, yPos);
}

