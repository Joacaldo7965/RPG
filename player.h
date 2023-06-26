#ifndef PLAYER_H
#define PLAYER_H
#include <QLabel>
#include <QGraphicsPixmapItem>

class Player : public QGraphicsPixmapItem {
public:
    Player(int numShots);
    void setStartPosition(int screenCenterX, int screenCenterY);
    void keyPressEvent(QKeyEvent *event);
    void shoot(int dx, int dy);
    void decreaseShot();
    void showImageOverlay(const QString& imagePath);
private:
    void verifyGameOver();
    int nShots_;
};

#endif // PLAYER_H
