#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGraphicsItem>

class ChessBoard : public QGraphicsItem {
public:
    ChessBoard();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    QPainterPath shape() const;
    QRectF boundingRect() const;
};

#endif // CHESSBOARD_H
