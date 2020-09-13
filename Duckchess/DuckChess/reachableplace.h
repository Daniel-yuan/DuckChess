#ifndef REACHABLEPLACE_H
#define REACHABLEPLACE_H

#include <QGraphicsItem>

class ReachablePlace : public QGraphicsItem {
public:
    ReachablePlace(qreal x, qreal y, bool Canmove);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    QPainterPath shape() const;
    QRectF boundingRect() const;
private:
    bool canmove;
};

#endif // REACHABLEPLACE_H
