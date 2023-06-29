#include "game.h"
#include "button.h"
#include "demon.h"
#include "attack.h"
#include <QRandomGenerator>
#include<QMediaPlayer>


Game::Game(){
    setWindowTitle(gameTile);
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, WIDTH, HEIGHT);
    setScene(scene);
    setFixedSize(WIDTH, HEIGHT);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    collisionBox = {25, 80, 640, 620};
    numDemons = 4; // Cambia este valor según la cantidad de demonios que desees
}

void Game::displayMainMenu(){
    // clear the screen
    scene->clear();
    setBackgroundBrush(QBrush(QColor(255, 255, 255)));

    // Create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(gameTile);
    QFont titleFont("comic sans", 50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button
    Button* playButton = new Button(QString("Play"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(playButton);

    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void Game::start(){
    // clear the screen
    scene->clear();

    // Game start
    setBackgroundBrush(QBrush(QImage(":/res/images/backgrounds/bg.jpg")));
    isGameOver = 0;

    int numShots = numDemons * 2;
    int screenCenterX = WIDTH/2;
    int screenCenterY = HEIGHT/2;

    player = new Player(1, numShots);
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

    shots = new Count(0, player->getShots(), QString("Attacks"), QFont("comic", 32));
    shots->setPos(shots->x(), shots->y() + 32);
    scene->addItem(shots);

    playerHealth = new Count(0, player->getHealth(), QString("Health"), QFont("comic", 32), Qt::red);
    playerHealth->setPos(playerHealth->x(), playerHealth->y() + 64);
    scene->addItem(playerHealth);

    demonCount = new Count(0, numDemons, QString("Demons"), QFont("comic", 32), Qt::darkCyan);
    demonCount->setPos(demonCount->x(), demonCount->y() + 96);
    //scene->addItem(demonCount);
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
        player->takeDamage(damage);
    }
    checkGameOver();
}

void Game::checkGameOver(){
    if(!isGameOver){
        if(playerHealth->getCount() == 0){
            gameOver();
        }
        if(demonCount->getCount() == 0){
            gameWin();
        }
        if(shots->getCount() == 0 && !isAttackInScreen()){
            gameOver();
        }
    }
}

void Game::gameOver(){
    qDebug() << "GAME OVER";
    isGameOver = 1;

    // Create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem("GAME OVER");
    QFont titleFont("comic sans", 50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button
    Button* playButton = new Button(QString("Restart"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(playButton);

    // create the quit button
    Button* quitButton = new Button(QString("Back"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(displayMainMenu()));
    scene->addItem(quitButton);

}


void Game::gameWin(){
    qDebug() << "You win!!";
    isGameOver = 1;

    // Create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem("You Win!");
    QFont titleFont("comic sans", 50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button
    Button* playButton = new Button(QString("Start again"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(playButton);

    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

bool Game::isAttackInScreen(){
    foreach (QGraphicsItem* item, scene->items()) {
        Attack* attackItem = dynamic_cast<Attack*>(item);
        if (attackItem) {
            return true;
        }
    }
    return false;
}
