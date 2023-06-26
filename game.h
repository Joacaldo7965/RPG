#ifndef GAME_H
#define GAME_H

#include<player.h>
#include<count.h>
#include<QGraphicsView>
#include<QWidget>
#include<QGraphicsScene>


const int WIDTH = 640;
const int HEIGHT = 640;

class Game: public QGraphicsView
{
public:
    Game(QWidget *parent=0);
    void killDemon();
    void damagePlayer(int damage);
    void decreaseShot(int c);
    void checkGameOver();
    void gameOver();
    void gameWin();
public:
    QGraphicsScene *scene;
    Player *player;
    Count *score;
    Count *shots;
    Count *playerHealth;
    Count *demonCount;
    int isGameOver=0;
private:
    int numDemons;
};

#endif // GAME_H
