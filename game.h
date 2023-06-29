#ifndef GAME_H
#define GAME_H

#include<player.h>
#include<count.h>
#include<QGraphicsView>
#include<QGraphicsScene>

const QString gameTile = QString("InformaticQuest;");

const int WIDTH = 640;
const int HEIGHT = 640;

struct Rectangle {
    int x1;
    int y1;
    int x2;
    int y2;
};

struct RoundConfig{
    int round;
    int nDemons;
    int minDemonSpeed;
    int maxDemonSpeed;
};

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game();
    void killDemon();
    void damagePlayer(int damage);
    void decreaseShot(int c);
    void checkGameOver();
    void gameOver();
    void gameWin();
    bool isAttackInScreen();
private slots:
    void start();
    void initNextRound();
    void initRound();
public slots:
    void displayMainMenu();
public:
    QGraphicsScene *scene;
    Player *player;
    Count *score;
    Count *shots;
    Count *playerHealth;
    int demonCount;
    int winRound;
    Count *roundCount;
    int isGameOver=0;
    RoundConfig roundConfig;
    Rectangle collisionBox={20, 80, 620, 620};
};

#endif // GAME_H
