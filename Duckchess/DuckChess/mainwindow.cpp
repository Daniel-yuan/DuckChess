#include "mainwindow.h"
#include "gamecontroller.h"
#include <QGraphicsView>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view (new QGraphicsView (scene, this)),
      game (new GameController (*scene, this)) {
    setCentralWidget(view);
    resize(600, 600);

    QIcon icon;
    icon.addFile(":/Images/duck.jpg");
    this->setWindowIcon(icon);

    InitScene();
    InitSceneBackground();

    //QTimer::singleShot(0, this, SLOT(adjustViewSize()));
}

MainWindow::~MainWindow() { }

void MainWindow::adjustViewSize() {
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}


void MainWindow :: InitScene() {
    scene->setSceneRect(-150, -150, 150, 150);
}

void MainWindow :: InitSceneBackground() {
//    QPixmap bg(10, 10);
//  //  QPainter p(&bg);
//  //  p.setBrush(QBrush(Qt::gray));
//  //  p.drawRect(0, 0, 10, 10);
//    for (int i = -10; i <= 10; i += 2) {
//        ;
//    }
//    view->setBackgroundBrush(QBrush(bg));
}
