#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QGraphicsRectItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    scene_ = new QGraphicsScene(this);

    int left_margin = 10; // x coordinate
    int top_margin = 10; // y coordinate
        // The width of the graphicsView is BORDER_RIGHT added by 2,
        // since the borders take one pixel on each side
        // (1 on the left, and 1 on the right).
        // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui_->graphicsView->setGeometry(left_margin, top_margin,
                                       BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui_->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
        // the height of it is BORDER_DOWN decreased by 1,
        // because the circle is considered to be inside the sceneRect,
        // if its upper left corner is inside the sceneRect.


    int x_coord = 0;
    int y_coord = 0;
    for (int i = 0; i < 20; ++i)
    {
        for ( int j = 0; j < 20; ++j)
        {
            scene_->setSceneRect(i, j, BORDER_RIGHT - 1, BORDER_DOWN - 1);
            scene_->addRect(i, j, STEP, STEP);
            ++x_coord;
            ++y_coord;
        }

    }

}

MainWindow::~MainWindow()
{
    delete ui_;
}

