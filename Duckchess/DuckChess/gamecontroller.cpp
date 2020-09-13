#include "gamecontroller.h"
#include "chessboard.h"
#include "chess.h"
#include "reachableplace.h"

#include <QGraphicsScene>
#include <QTimer>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QApplication>

bool GameController :: Capt(int x, int y, int nx, int ny) {
  int sx = abs(nx - x), sy = abs(ny - y);
  return (sx + sy == 1);
}
bool GameController :: Guar(int x, int y, int nx, int ny) {
  int sx = abs(nx - x), sy = abs(ny - y);
  return (sx == 1) && (sy == 1);
}
bool GameController :: Elep(int x, int y, int nx, int ny) {
  int sx = 0, sy = 0;
  if (nx == x + 2 && ny == y + 2) sx = +1, sy = +1;
  if (nx == x - 2 && ny == y + 2) sx = -1, sy = +1;
  if (nx == x + 2 && ny == y - 2) sx = +1, sy = -1;
  if (nx == x - 2 && ny == y - 2) sx = -1, sy = -1;
  return !Board[x + sx][y + sy] && (sx * sy != 0);
}
bool GameController :: Hors(int x, int y, int nx, int ny) {
  int sx = 3, sy = 3;
  if (nx == x + 2) sx = +1;
  if (nx == x - 2) sx = -1;
  if (nx == x + 1) sx = +0;
  if (nx == x - 1) sx = -0;
  if (ny == y + 2) sy = +1;
  if (ny == y - 2) sy = -1;
  if (ny == y + 1) sy = +0;
  if (ny == y - 1) sy = -0;
  return !Board[x + sx][y + sy] && (abs(sx + sy) == 1);
}
bool GameController :: Cars(int x, int y, int nx, int ny) {
  if (x == nx && y == ny) return 0;
  if (x != nx && y != ny) return 0;
  int sx = 0, sy = 0;
  if (x == nx) sy = ny > y ? 1 : -1;
  if (y == ny) sx = nx > x ? 1 : -1;
  for (int i = x + sx, j = y + sy; (i != nx) || (j != ny); i += sx, j += sy)
    if (Board[i][j]) return 0;
  return 1;
}
bool GameController :: Duck(int x, int y, int nx, int ny) {
  int sx = 0, sy = 0;
  if (nx == x + 3) sx = +2;
  if (nx == x - 3) sx = -2;
  if (nx == x + 2) sx = +1;
  if (nx == x - 2) sx = -1;
  if (ny == y + 3) sy = +2;
  if (ny == y - 3) sy = -2;
  if (ny == y + 2) sy = +1;
  if (ny == y - 2) sy = -1;
  return !Board[x + sx][y + sy] && !Board[x + sx / 2][y + sy / 2] && ((sx + sy + 8) % 2 == 1);
}
bool GameController :: Sold(int x, int y, int nx, int ny) {
  int sx = abs(nx - x), sy = abs(ny - y);
  return (sx <= 1) && (sy <= 1);
}

bool GameController :: Canmove(int x, int y, int nx, int ny, int Camp) {
  if (Board[nx][ny] && Board[nx][ny] / 10 == Camp) return 0;
  if (Board[x][y] % 10 == 1) return Capt(x, y, nx, ny);
  if (Board[x][y] % 10 == 2) return Guar(x, y, nx, ny);
  if (Board[x][y] % 10 == 3) return Elep(x, y, nx, ny);
  if (Board[x][y] % 10 == 4) return Hors(x, y, nx, ny);
  if (Board[x][y] % 10 == 5) return Cars(x, y, nx, ny);
  if (Board[x][y] % 10 == 6) return Duck(x, y, nx, ny);
  if (Board[x][y] % 10 == 7) return Sold(x, y, nx, ny);
  return 0;
}

void GameController :: Init() {
    memset(Board, 0, sizeof(Board));
    memset(Reach, 0, sizeof(Reach));
//    for (int i = 0; i < 3; ++i)
//        for (int j = 0; j < 9; ++j)
//            Board[i][j] = 04;
    Board[3][0] = Board[3][2] = Board[3][4] = Board[3][6] = Board[3][8] = 07;
    Board[2][0] = Board[2][8] = 06;
    Board[0][0] = Board[0][8] = 05;
    Board[0][1] = Board[0][7] = 04;
    Board[0][2] = Board[0][6] = 03;
    Board[0][3] = Board[0][5] = 02;
    Board[0][4] = 01;

//    for (int i = 7; i < 10; ++i)
//        for (int j = 0; j < 9; ++j)
//            Board[i][j] = 14;

    Board[6][0] = Board[6][2] = Board[6][4] = Board[6][6] = Board[6][8] = 17;
    Board[7][0] = Board[7][8] = 16;
    Board[9][0] = Board[9][8] = 15;
    Board[9][1] = Board[9][7] = 14;
    Board[9][2] = Board[9][6] = 13;
    Board[9][3] = Board[9][5] = 12;
    Board[9][4] = 11;
}

void GameController :: GameStart() {
    Pressed = false;
    Nowperson = 0;
    Init();
    ScreenPrint();
    while (CurrentTop->Pre != nullptr) {
        Moves *Pre = CurrentTop->Pre;
        delete CurrentTop;
        CurrentTop = Pre;
    }
}

void GameController :: GameOver() {
    if (QMessageBox :: Yes == QMessageBox :: question(PARENT, tr("Game Over"), Nowperson ? tr("Blue Win! Play again?") : tr("Red Win! Play again?"))) {
        GameStart();
        return void();
    }
    else {
        exit(0);
    }
}

void GameController :: GiveUp() {
    if (QMessageBox :: Yes == QMessageBox :: question(PARENT, tr("Give up"), tr("Are you sure"))) {
        Nowperson ^= 1;
        GameOver();
    }
}

void GameController :: RegretChess() {
    if (QMessageBox :: Yes == QMessageBox :: question(PARENT, tr("Regret chess"), tr("Are you sure"))) {
        Nowperson ^= 1;
        if (CurrentTop->Pre != nullptr) {
            Board[CurrentTop->x1][CurrentTop->y1] = CurrentTop->chess1;
            Board[CurrentTop->x2][CurrentTop->y2] = CurrentTop->chess2;
            CurrentTop = CurrentTop->Pre;
        }
        ScreenPrint();
    }
}

void GameController :: ScreenPrint() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 9; ++j) {
            scene.removeItem(chess[i][j]);
            delete chess[i][j];
            chess[i][j] = new Chess(j * 50 - 300 - 20, i * 50 - 300 - 20, Board[i][j]);
            scene.addItem(chess[i][j]);
            scene.removeItem(place[i][j]);
            delete(place[i][j]);
            place[i][j] = new ReachablePlace(j * 50 - 300, i * 50 - 300, Reach[i][j]);
            scene.addItem(place[i][j]);
        }
    }
    scene.removeItem(chessboard);
    chessboard = new ChessBoard();
    scene.addItem(chessboard);
}

void GameController :: ScreenInit() {
    QPushButton *giveup = new QPushButton();
    giveup->setText(tr("Give up"));
    giveup->move(120, -300);
    giveup->resize(100, 30);
    scene.addWidget(giveup);
    QObject :: connect(giveup, SIGNAL(clicked()), this, SLOT(GiveUp()));

    QPushButton *regretchess = new QPushButton();
    regretchess->setText(tr("Regret chess"));
    regretchess->move(120, 100);
    regretchess->resize(100, 30);
    scene.addWidget(regretchess);
    QObject :: connect(regretchess, SIGNAL(clicked()), this, SLOT(RegretChess()));

    chessboard = new ChessBoard();
    scene.addItem(chessboard);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 9; ++j) {
            chess[i][j] = new Chess(j * 50 - 300 - 20, i * 50 - 300 - 20, Board[i][j]);
            scene.addItem(chess[i][j]);
            place[i][j] = new ReachablePlace(j * 50 - 300, i * 50 - 300, Reach[i][j]);
            scene.addItem(place[i][j]);
        }
    }
}

GameController :: GameController(QGraphicsScene &scene, QWidget *parent) :
    QObject(parent),
    scene(scene) {
    timer.start(100);
    PARENT = parent;
    scene.installEventFilter(this);

    ScreenInit();
    CurrentTop = new Moves;

    GameStart();

    resume();
}

GameController :: ~GameController() {

}

void GameController :: pause() {
    disconnect(&timer, SIGNAL(timeout()),
               &scene,  SLOT(advance()));
}
void GameController :: resume() {
    connect(&timer, SIGNAL(timeout()),
            &scene,  SLOT(advance()));
}

void GameController :: MousePressed(QGraphicsSceneMouseEvent *event) {
    int x = event->scenePos().x();
    int y = event->scenePos().y();
    int mindis = 1e9, posx, posy;
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 9; ++j) {
            int dis = abs(j * 50 - 300 - x) + abs(i * 50 - 300 - y);
            if (dis < mindis)
                mindis = dis, posx = i, posy = j;
        }
    if (Pressed) {
        Pressed = 0;
        if (Reach[posx][posy] && (posx != Readyx || posy != Readyy)) {
            if (Board[posx][posy] % 10 == 1) {
                GameOver();
            }
            Moves *tmp = new Moves;
            tmp->Pre = CurrentTop;
            tmp->x1 = Readyx, tmp->y1 = Readyy, tmp->chess1 = Board[Readyx][Readyy];
            tmp->x2 = posx,   tmp->y2 = posy,   tmp->chess2 = Board[posx][posy];
            CurrentTop = tmp;
            Board[posx][posy] = Board[Readyx][Readyy];
            Board[Readyx][Readyy] = 0;
            Nowperson ^= 1;
        }
        memset(Reach, 0, sizeof(Reach));
        ScreenPrint();
    }
    else {
        if (Board[posx][posy] != 0 && Board[posx][posy] / 10 == Nowperson) {
            if (mindis <= 50) {
                Pressed = 1;
                memset(Reach, 0, sizeof(Reach));
                for (int i = 0; i < 10; ++i)
                    for (int j = 0; j < 9; ++j)
                        if ((posx == i && posy == j) || Canmove(posx, posy, i, j, Nowperson))
                            Reach[i][j] = 1;
                Readyx = posx, Readyy = posy;
                ScreenPrint();
            }
        }
    }
}

bool GameController :: eventFilter(QObject *object, QEvent *event) {
    if (event->type() == QEvent :: GraphicsSceneMousePress) {
        MousePressed((QGraphicsSceneMouseEvent *)event);
        return true;
    }
    else {
        return QObject :: eventFilter(object, event);
    }
}
