#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gameboard.hh"
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGridLayout>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
    , scene_()
    , rect_()
    , graboard_()
    , board_()
    , labels_()
    , board()
{
    ui_->setupUi(this);

    scene_ = new QGraphicsScene(this);
    //QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget;

    //QGraphicsProxyWidget *proxy = scene.addWidget(tabWidget);
    int left_margin = 10; // x coordinate
    int top_margin = 10; // y coordinate
        // The width of the graphicsView is BORDER_RIGHT added by 2,
        // since the borders take one pixel on each side
        // (1 on the left, and 1 on the right).
        // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui_->graphicsView->setGeometry(left_margin, top_margin,
                                       SIZE*STEP + 2, SIZE*STEP + 2);
    ui_->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 an

    scene_->setSceneRect(0, 0, SIZE*STEP - 1, SIZE*STEP - 1);

    createGraphicalBoard();

}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::createGraphicalBoard()
{

    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);

    std::vector<QGraphicsRectItem*> rects;
    //to change text content, can be reached by coordinates?
    std::vector<QLabel*> helper;


    for (int row = 0; row < SIZE; ++row)
    {
        for (int column = 0; column < SIZE; ++column)
        {

            QGraphicsRectItem* rect = new QGraphicsRectItem;
            QLabel* label = new QLabel("*", this);
            if (column == 0)
            {
                rect = scene_->addRect(column, row+(row*STEP), STEP, STEP, blackPen, whiteBrush);
                label->setGeometry(column, row+(row*STEP), STEP, STEP);
                label->setAlignment(Qt::AlignCenter);
            }
            else if (column >0)
            {
                rect = scene_->addRect(column+(column*STEP), row+(row*STEP), STEP, STEP, blackPen, whiteBrush);
                label->setGeometry(column+(column*STEP), row+(row*STEP), STEP, STEP);
                label->setAlignment(Qt::AlignCenter);
            }
            else
            {
               rect = scene_->addRect(column+(column*STEP), row, STEP, STEP, blackPen, whiteBrush);
               label->setGeometry(column+(column*STEP), row, STEP, STEP);
               label->setAlignment(Qt::AlignCenter);
            }

            helper.push_back(label);

            rects.push_back(rect);

            std::cout << "nyt on tehty näin monta rectii: " << rects.size() << std::endl;
            std::cout << "labels pituus:" << labels_.size();

        }
        labels_.push_back(helper);
           helper.clear();
    }

    labels_.at(2).at(2)->setText("HAHA");
}

/*void MainWindow::createButtonBoard()
{
    QGridLayout* grid = new QGridLayout;

    for (int row = 0; row < SIZE; ++row)
    {
        for (int column = 0; column < SIZE; ++column)
        {
            QPushButton* button = new QPushButton;
            button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            button->setText("LA");
            grid->addWidget(button, row, column);
            board.append(button);
        }
    }
    setLayout(grid);
}*/




void MainWindow::on_seedNumberBox_valueChanged(int arg1)
{
    //tää heittää gameboardille seedin ja täyttää
    graboard_.fill(arg1);
}

