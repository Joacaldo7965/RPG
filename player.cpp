#include "player.h"
#include "game.h"
#include "attack.h"
#include "demon.h"
#include <QApplication>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>

extern Game *game;

Player::Player(int healthPoints, int numShots) {
    setPixmap(QPixmap(":/res/images/player/swmg.png"));
    setTransformOriginPoint(boundingRect().width()/2, boundingRect().height()/2);
    nShots_ = numShots;
    health = healthPoints;
    isFacingRight = 1;
    //media = new QMediaPlayer();
    //media->setSource(QUrl("qrc:/res/sounds/shadow.mp3"));
}

void Player::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_A) {
        move(-1, 0);
    } else if (event->key() == Qt::Key_D) {
        move(1, 0);
    } else if (event->key() == Qt::Key_W) {
        move(0, -1);
    } else if (event->key() == Qt::Key_S) {
        move(0, 1);
    } else if (event->key() == Qt::Key_Up) {
        shoot(0, -20);
    } else if (event->key() == Qt::Key_Left) {
        shoot(-20, 0);
    } else if (event->key() == Qt::Key_Down) {
        shoot(0, 20);
    } else if (event->key() == Qt::Key_Right) {
        shoot(20, 0);
    } else if (event->key() == Qt::Key_M){
        //qDebug() << "---\n" << media->isPlaying();
        //qDebug() << "Playing music!";
        //media->play();
        //qDebug() << media->isPlaying();
    }
}

void Player::takeDamage(int dmg){
    health -= dmg;
}

void Player::addShots(int s){
    nShots_+= s;
}

void Player::setShots(int s)
{
    nShots_ = s;
}

bool Player::isAlive(){
    return health > 0;
}

void Player::move(int dx, int dy){
    if(!isAlive())
        return;
    if(dx == 0 && dy == 0)
        return;
    int nextX = x() + dx*speed;
    int nextY = y() + dy*speed;

    // Handle Sprite change of direction
    if(isFacingRight && dx < 0){
        setPixmap(QPixmap(":/res/images/player/swmg.png").transformed(QTransform().scale(-1, 1)));
        isFacingRight = 0;
    }else if(!isFacingRight && dx > 0){
        setPixmap(QPixmap(":/res/images/player/swmg.png"));
        isFacingRight = 1;
    }

    // Checks for walls
    // Top wall
    if(nextY <= game->collisionBox.y1){
        return;
    }
    // Right wall
    if(nextX + boundingRect().width() >= game->collisionBox.x2){
        return;
    }
    // Bottom wall
    if(nextY + boundingRect().height() > game->collisionBox.y2){
        return;
    }
    // Left wall
    if(nextX < game->collisionBox.x1){
        return;
    }

    setPos(nextX, nextY);
}

void Player::shoot(int dx, int dy) {
    if(!isAlive())
        return;
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

int Player::getHealth(){
    return health;
}

void Player::setStartPosition(int screenCenterX, int screenCenterY) {
    int xPos = screenCenterX - pixmap().width() / 2;
    int yPos = screenCenterY - pixmap().height() / 2;
    setPos(xPos, yPos);
}

