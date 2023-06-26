#include <QApplication>
#include <QGraphicsScene>
#include "character.h"
#include "qgraphicsview.h"
#include "demon.h"
#include <QRandomGenerator>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 640, 640);
    scene->setBackgroundBrush(QBrush(QImage(":/images/bg.jpg")));
    int numDemons = 10; // Cambia este valor según la cantidad de demonios que desees
    int numShots = numDemons * 2;
    Personaje *player = new Personaje(numShots);
    scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    int screenCenterX = 320;
    int screenCenterY = 320;
    player->setStartPosition(screenCenterX, screenCenterY);
    for (int i = 0; i < std::min(numDemons, numShots / 2); ++i) {
        int radius = 200;
        int x, y;
        do {
            x = QRandomGenerator::global()->bounded(0, 640);
            y = QRandomGenerator::global()->bounded(0, 640);
        } while (qAbs(x - screenCenterX) <= radius && qAbs(y - screenCenterY) <= radius);
        Demon *demon = new Demon();
        demon->setPos(x, y);
        demon->setMovementRange(0, 640, 0, 640);
        scene->addItem(demon);
    }
    QGraphicsView *view = new QGraphicsView(scene);
    view->setFixedSize(640, 640);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();
    return a.exec();
}
