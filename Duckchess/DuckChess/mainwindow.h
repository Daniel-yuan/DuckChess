#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsScene;
class QGraphicsView;
class GameController;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void adjustViewSize();

private :
    void InitScene();
    void InitSceneBackground();

    QGraphicsScene *scene;
    QGraphicsView *view;
    GameController *game;

};
#endif // MAINWINDOW_H
