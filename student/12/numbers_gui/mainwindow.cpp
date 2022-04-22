#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gameboard.hh"
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGridLayout>
#include <iostream>

const Coords DEFAULT_DIR = {0, 0};
const Coords LEFT = {0, -1};
const Coords UP = {-1, 0};
const Coords RIGHT = {0, 1};
const Coords DOWN = {1, 0};

MainWindow::MainWindow(GameBoard& board, QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
    , scene_()
    , rect_()
    , graboard_(board)
    , labels_()
    , seed_(0)
    , goal_(0)
{
    ui_->setupUi(this);

    scene_ = new QGraphicsScene(this);

    int left_margin = 20; // x coordinate
    int top_margin = 20; // y coordinate

    ui_->graphicsView->setGeometry(left_margin, top_margin,
                                       SIZE*STEP + 2, SIZE*STEP + 2);
    ui_->graphicsView->setScene(scene_);

    scene_->setSceneRect(0, 0, SIZE*STEP - 1, SIZE*STEP - 1);

    createGraphicalBoard();

}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{

    Coords dir = DEFAULT_DIR;
    // moving to left
    if(event->key() == Qt::Key_A)
    {
        dir = LEFT;
    }
    if (event->key() == Qt::Key_W)
    {
        dir = UP;
    }
    if (event->key() == Qt::Key_D)
    {
        dir = RIGHT;
    }
    if (event->key() == Qt::Key_S)
    {
        dir = DOWN;
    }

    if (dir != DEFAULT_DIR)
    {
        if (graboard_.move(dir, goal_))
        {
            QString text = "You reached the goal value of ";
            QString goalqs = QString::number(goal_);
            text += goalqs;
            text += "!";
            ui_->textBrowser->setText(text);
        }
        else if (graboard_.is_full())
        {
            QString text = "Can't add new tile, you lost!";
            ui_->textBrowser->setText(text);
        }
        graboard_.new_value(false);
    }
    updateGraphicalBoard();
}


void MainWindow::createGraphicalBoard()
{

    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);

    std::vector<QGraphicsRectItem*> rects;
    std::vector<QLabel*> helper;

    for (int row = 0; row < SIZE; ++row)
    {
        for (int column = 0; column < SIZE; ++column)
        {
            QLabel* label = new QLabel("*", this);
            if (column == 0)
            {
                scene_->addRect(column, row+(row*STEP), STEP, STEP, blackPen, whiteBrush);
                label->setGeometry(column, row+(row*STEP), STEP, STEP);
                label->setAlignment(Qt::AlignCenter);
            }
            else if (column >0)
            {
                scene_->addRect(column+(column*STEP), row+(row*STEP), STEP, STEP, blackPen, whiteBrush);
                label->setGeometry(column+(column*STEP), row+(row*STEP), STEP, STEP);
                label->setAlignment(Qt::AlignCenter);
            }
            else
            {
               scene_->addRect(column+(column*STEP), row, STEP, STEP, blackPen, whiteBrush);
               label->setGeometry(column+(column*STEP), row, STEP, STEP);
               label->setAlignment(Qt::AlignCenter);
            }

            helper.push_back(label);
        }
        labels_.push_back(helper);
        helper.clear();
    }
}

void MainWindow::updateGraphicalBoard()
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            Coords coords;
            coords.first = j;
            coords.second = i;
            int nr = graboard_.get_item(coords)->get_value();
            QString s = QString::number(nr);
            labels_.at(j).at(i)->setText(s);
        }
    }
}

void MainWindow::on_startButton_clicked()
{
    graboard_.init_empty();
    //kaivaa seedin
    graboard_.fill(seed_);
    updateGraphicalBoard();
}


void MainWindow::on_seedLine_textChanged(const QString &arg1)
{
    seed_ = arg1.toInt();
}


void MainWindow::on_goalLine_textChanged(const QString &arg1)
{
    goal_ = arg1.toInt();
    std::cout << "goali on" << goal_ << std::endl;
}

