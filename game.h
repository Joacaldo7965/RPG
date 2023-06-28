#ifndef GAME_H
#define GAME_H

#include<player.h>
#include<count.h>
#include<QGraphicsView>
#include<QWidget>
#include<QGraphicsScene>


const int WIDTH = 640;
const int HEIGHT = 640;

struct Rectangle {
    int x1;
    int y1;
    int x2;
    int y2;
};

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
private:

public:
    QGraphicsScene *scene;
    Player *player;
    Count *score;
    Count *shots;
    Count *playerHealth;
    Count *demonCount;
    int isGameOver=0;
    Rectangle collisionBox={20, 80, 620, 620};
private:
    int numDemons;
};

#endif // GAME_H
