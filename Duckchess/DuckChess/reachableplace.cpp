#include "reachableplace.h"

#include <QPainter>

ReachablePlace :: ReachablePlace(qreal x, qreal y, bool Canmove) {
    canmove = Canmove;
    setPos(x, y);
}

QRectF ReachablePlace :: boundingRect() const {
    return QRectF(-100, -100, 100 * 2, 100 * 2);
}

void ReachablePlace :: paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->save();

    if (canmove) {
        painter->setRenderHint(QPainter :: Antialiasing);
        painter->fillPath(shape(), Qt :: gray);
    }

    painter->restore();
}

QPainterPath ReachablePlace :: shape() const {
    QPainterPath p;
    p.addEllipse(QPointF(0, 0), 6, 6);
    return p;
}
