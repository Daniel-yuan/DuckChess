#include "chessboard.h"

#include <QPainter>

ChessBoard :: ChessBoard() { }

void ChessBoard :: paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->save();

    painter->setRenderHint(QPainter :: Antialiasing);
    painter->fillPath(shape(), Qt :: black);

    painter->restore();
}

QRectF ChessBoard :: boundingRect() const {
    return QRectF(-100, -100, 100 * 2, 100 * 2);
}

QPainterPath ChessBoard :: shape() const {
    QPainterPath p;
    for (int i = -300; i <= 100; i += 50) {
        if (i != -300 && i != 100) {
            p.addRect(QRectF(i, -300, 1, 200));
            p.addRect(QRectF(i, -50 , 1, 200));
        } else {
            p.addRect(QRectF(i, -300, 1, 450));
        }
    }
    for (int i = -300; i <= 150; i += 50) {
        p.addRect(QRectF(-300, i, 400, 1));
    }
    return p;
}
