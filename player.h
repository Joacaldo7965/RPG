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
    int getShots();
private:
    void move(int dx, int dy);
    void verifyGameOver();
    int nShots_;
    int isFacingRight=1;
    int speed=20;
};

#endif // PLAYER_H
