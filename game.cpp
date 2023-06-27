#include "game.h"
#include "demon.h"
#include <QRandomGenerator>

Game::Game(QWidget *parent){
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, WIDTH, HEIGHT);
    setScene(scene);
    setFixedSize(WIDTH, HEIGHT);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setBackgroundBrush(QBrush(QImage(":/res/images/backgrounds/bg.jpg")));

    collisionBox = {25, 80, 640, 620};

    numDemons = 4; // Cambia este valor según la cantidad de demonios que desees
    int numShots = numDemons * 2;
    int screenCenterX = WIDTH/2;
    int screenCenterY = HEIGHT/2;

    player = new Player(numShots);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setStartPosition(screenCenterX, screenCenterY);

    scene->addItem(player);

    // Initialize demons
    for (int i = 0; i < numDemons; ++i) {
        Demon *demon = new Demon(collisionBox);
        scene->addItem(demon);
    }


    score = new Count(0, 0, QString("Score"), QFont("comic", 32));
    scene->addItem(score);

    shots = new Count(0, player->getShots(), QString("Shots"), QFont("comic", 32));
    shots->setPos(shots->x(), shots->y() + 32);
    scene->addItem(shots);

    playerHealth = new Count(0, 3, QString("Health"), QFont("comic", 32), Qt::red);
    playerHealth->setPos(playerHealth->x(), playerHealth->y() + 64);
    scene->addItem(playerHealth);

    demonCount = new Count(0, numDemons, QString("Demons"), QFont("comic", 32), Qt::darkCyan);
    demonCount->setPos(demonCount->x(), demonCount->y() + 96);
    scene->addItem(demonCount);

    show();
}

void Game::decreaseShot(int c){
    shots->decrease(c);
    checkGameOver();
}

void Game::killDemon(){
    score->increase(10);
    demonCount->decrease(1);
    checkGameOver();
}

void Game::damagePlayer(int damage){
    if(playerHealth->getCount() < damage){
        playerHealth->setCount(0);
    }else{
        playerHealth->decrease(damage);
    }
    checkGameOver();
}

void Game::checkGameOver(){
    if(!isGameOver){
        if(shots->getCount() == 0 || // FIXME: Change this with the bullets on screen
            playerHealth->getCount() == 0
            ){
            gameOver();
        }
        if(demonCount->getCount() == 0){
            gameWin();
        }
    }
}

void Game::gameOver(){
    qDebug() << "GAME OVER";
    isGameOver = 1;
}

void Game::gameWin(){
    qDebug() << "You win!!";
    isGameOver = 1;
}
