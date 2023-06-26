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

    numDemons = 10; // Cambia este valor según la cantidad de demonios que desees
    int numShots = numDemons * 2;
    int screenCenterX = WIDTH/2;
    int screenCenterY = HEIGHT/2;

    player = new Player(numShots);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setStartPosition(screenCenterX, screenCenterY);

    scene->addItem(player);

    for (int i = 0; i < std::min(numDemons, numShots / 2); ++i) {
        int radius = 200;
        int x, y;
        do {
            x = QRandomGenerator::global()->bounded(0, WIDTH);
            y = QRandomGenerator::global()->bounded(0, HEIGHT);
        } while (qAbs(x - screenCenterX) <= radius && qAbs(y - screenCenterY) <= radius);

        Demon *demon = new Demon();
        demon->setPos(x, y);
        demon->setMovementRange(0, WIDTH, 0, HEIGHT);
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
    if(playerHealth->getCount() - damage <= 0){
        playerHealth->setCount(0);
    }else{
        playerHealth->decrease(damage);
    }
    checkGameOver();
}

void Game::checkGameOver(){
    if(!isGameOver){
        if(shots->getCount() == 0 ||
            playerHealth->getCount() == 0
            ){
            gameOver();
        }if(demonCount->getCount() == 0){
            gameWin();
        }else{
            qDebug() << "Game Not Over";
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
