#include "score.h"
#include<QFont>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    score = 0;
    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::white);
    setFont(QFont("comic", 32));
}

void Score::increase(int step){
    score+= step;
    setPlainText(QString("Score: ") + QString::number(score));
}

int Score::getScore(){
    return score;
}
