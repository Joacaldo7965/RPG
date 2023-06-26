#ifndef COUNT_H
#define COUNT_H

#include <QGraphicsTextItem>
#include <QFont>

class Count: public QGraphicsTextItem{
public:
    Count(QGraphicsItem *parent=0, int count=0, QString countName=QString("Count"), QFont font=QFont("comic", 16), Qt::GlobalColor color=Qt::white);
    void increase(int step);
    void decrease(int step);
    int getCount();
    void setCount(int c);
private:
    int count;
    QString countName;
    QFont font;
    Qt::GlobalColor color;
};

#endif // COUNT_H
