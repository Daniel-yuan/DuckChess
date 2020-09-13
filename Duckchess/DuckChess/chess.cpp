#include "chess.h"

#include <QPainter>

Chess :: Chess(qreal x, qreal y, int ChessType) {
    setPos(x, y);
    switch (ChessType) {
    case 1: image.load(":/Images/RedCaptain.png"); break;
    case 2: image.load(":/Images/RedGuard.png"); break;
    case 3: image.load(":/Images/RedElephant.png"); break;
    case 4: image.load(":/Images/RedHorse.png"); break;
    case 5: image.load(":/Images/RedCar.png"); break;
    case 6: image.load(":/Images/RedDuck.png"); break;
    case 7: image.load(":/Images/RedSoldier.png"); break;
    case 11: image.load(":/Images/BlueCaptain.png"); break;
    case 12: image.load(":/Images/BlueGuard.png"); break;
    case 13: image.load(":/Images/BlueElephant.png"); break;
    case 14: image.load(":/Images/BlueHorse.png"); break;
    case 15: image.load(":/Images/BlueCar.png"); break;
    case 16: image.load(":/Images/BlueDuck.png"); break;
    case 17: image.load(":/Images/BlueSoldier.png"); break;
    }
}

void Chess :: paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->save();

    painter->setRenderHint(QPainter :: Antialiasing);
    painter->drawPixmap(0, 0, 40, 40, image);

    painter->restore();
}

QRectF Chess :: boundingRect() const {
    return QRectF(-100, -100, 100 * 2, 100 * 2);
}
