#ifndef PLAYER_H
#define PLAYER_H
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>

class Player : public QGraphicsPixmapItem {
public:
    Player(int health, int numShots);
    void setStartPosition(int screenCenterX, int screenCenterY);
    void keyPressEvent(QKeyEvent *event);
    void shoot(int dx, int dy);
    void decreaseShot();
    void takeDamage(int dmg);
    void showImageOverlay(const QString& imagePath);
    bool isAlive();
    int getShots();
    int getHealth();
private:
    void move(int dx, int dy);
    void verifyGameOver();
    int nShots_;
    int health=1;
    int isFacingRight=1;
    int speed=20;
    QMediaPlayer *media;
};

#endif // PLAYER_H
