#ifndef CHESS_H
#define CHESS_H

#include <QGraphicsItem>

class Chess : public QGraphicsItem {
public:
    Chess(qreal x, qreal y, int ChessType);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    QRectF boundingRect() const;
private:
    QPixmap image;
};

#endif // CHESS_H
