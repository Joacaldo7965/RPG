#include "count.h"
#include<QFont>

Count::Count(QGraphicsItem *parent, int count, QString countName, QFont font, Qt::GlobalColor color):
    QGraphicsTextItem(parent),
    count(count),
    countName(countName),
    font(font),
    color(color)
{
    setPlainText(countName + QString(": ") + QString::number(count));
    setDefaultTextColor(color);
    setFont(font);
}

void Count::increase(int step){
    count += step;
    setPlainText(countName + QString(": ") + QString::number(count));
}

void Count::decrease(int step){
    count -= step;
    setPlainText(countName + QString(": ") + QString::number(count));
}

int Count::getCount(){
    return count;
}

void Count::setCount(int c){
    count = c;
}
