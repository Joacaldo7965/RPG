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

    int numDemons = 10; // Cambia este valor según la cantidad de demonios que desees
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

    score = new Score();
    scene->addItem(score);

    show();
}
