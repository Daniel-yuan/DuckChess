#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>

class QGraphicsScene;
class QTimer;
class QGraphicsSceneMouseEvent;

class ChessBoard;
class Chess;
class ReachablePlace;

struct Moves {
    int x1, y1, chess1;
    int x2, y2, chess2;
    Moves *Pre;
    Moves () { Pre = nullptr; }
};

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(QGraphicsScene &scene, QWidget *parent = nullptr);
    ~GameController();
public slots:
    void pause();
    void resume();
    void GiveUp();
    void RegretChess();
protected:
    bool eventFilter(QObject *object, QEvent *event);
private:
    void Init();
    void ScreenPrint();
    void ScreenInit();
    void MousePressed(QGraphicsSceneMouseEvent *event);
    bool Canmove(int x, int y, int nx, int ny, int Camp);
    bool Capt(int x, int y, int nx, int ny);
    bool Guar(int x, int y, int nx, int ny);
    bool Elep(int x, int y, int nx, int ny);
    bool Hors(int x, int y, int nx, int ny);
    bool Cars(int x, int y, int nx, int ny);
    bool Duck(int x, int y, int nx, int ny);
    bool Sold(int x, int y, int nx, int ny); 
    void GameOver();
    void GameStart();

    QGraphicsScene &scene;
    QTimer timer;
    bool Pressed;
    int Nowperson;
    int Board[15][15];
    int Reach[15][15];
    int Readyx, Readyy;
    QWidget *PARENT;
    bool ShouldRefresh;
    Chess *chess[15][15];
    ReachablePlace *place[15][15];
    ChessBoard *chessboard;
    Moves *CurrentTop;
};

#endif // GAMECONTROLLER_H
