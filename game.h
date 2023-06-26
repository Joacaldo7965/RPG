#ifndef GAME_H
#define GAME_H

#include<player.h>
#include<score.h>
#include<health.h>
#include<QGraphicsView>
#include<QWidget>
#include<QGraphicsScene>


const int WIDTH = 640;
const int HEIGHT = 640;

class Game: public QGraphicsView
{
public:
    Game(QWidget *parent=0);

    QGraphicsScene *scene;
    Player *player;
    Score *score;
    Health *health;
};

#endif // GAME_H
