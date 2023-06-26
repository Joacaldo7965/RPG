#ifndef CHARACTER_H
#define CHARACTER_H
#include <QLabel>
#include <QGraphicsPixmapItem>

class Personaje : public QGraphicsPixmapItem {
public:
    Personaje(int numShots);
    void setStartPosition(int screenCenterX, int screenCenterY);
    void keyPressEvent(QKeyEvent *event);
    void shoot(int dx, int dy);
    void restarDisparo();
    void showImageOverlay(const QString& imagePath);
private:
    void verificarFinJuego();
    int numDisparos_;
};

#endif // CHARACTER_H
