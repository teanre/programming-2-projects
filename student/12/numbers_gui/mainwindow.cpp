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
    , graboard_(board)
    , labels_()
    , boardsize_(4)
    , seed_(0)
    , goal_(2048)
    , amount_of_starts_(0)
{
    ui_->setupUi(this);

    scene_ = new QGraphicsScene(this);

    int left_margin = 20; // x coordinate
    int top_margin = 20; // y coordinate

    ui_->graphicsView->setGeometry(left_margin, top_margin,
                                       boardsize_*STEP + 2, boardsize_*STEP + 2);
    ui_->graphicsView->setScene(scene_);

    scene_->setSceneRect(0, 0, boardsize_*STEP - 1, boardsize_*STEP - 1);

    ui_->seedLabel->setStyleSheet("QLabel: {background-color: green}");

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
            winColors();
            disableLabels();
        }
        else if (graboard_.is_full())
        {
            QString text = "Can't add new tile, you lost!";
            ui_->textBrowser->setText(text);
            disableLabels();
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

    for (int row = 0; row < boardsize_; ++row)
    {
        for (int column = 0; column < boardsize_; ++column)
        {
            QLabel* label = new QLabel("*", this);
            if (column == 0)
            {
                scene_->addRect(column, row+(row*STEP), STEP, STEP, blackPen, whiteBrush);
                label->setGeometry(column, row+(row*STEP), STEP*1.75, STEP*1.75);
                label->setAlignment(Qt::AlignCenter);
            }
            else if (column >0)
            {
                scene_->addRect(column+(column*STEP), row+(row*STEP), STEP, STEP, blackPen, whiteBrush);
                label->setGeometry(column+(column*STEP), row+(row*STEP), STEP*1.75, STEP*1.75);
                label->setAlignment(Qt::AlignCenter);
            }
            else
            {
               scene_->addRect(column+(column*STEP), row, STEP, STEP, blackPen, whiteBrush);
               label->setGeometry(column+(column*STEP), row, STEP*1.75, STEP*1.75);
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
    for (int i = 0; i < boardsize_; ++i)
    {
        for (int j = 0; j < boardsize_; ++j)
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

void MainWindow::winColors()
{
   ui_->graphicsView->setStyleSheet("QWidget: {background-color: green}");
}

void MainWindow::lossColors()
{

}

void MainWindow::disableLabels()
{
    for (auto& vec : labels_)
    {
        for (auto label : vec)
        {
            label->setEnabled(false);
        }
    }
}

void MainWindow::enableLabels()
{
    for (auto& vec : labels_)
    {
        for (auto label : vec)
        {
            label->setEnabled(true);
        }
    }
}

void MainWindow::on_startButton_clicked()
{
    amount_of_starts_++;
    boardsize_ = ui_->sizeSpinBox->value();
    graboard_.set_size(boardsize_);

    if (boardsize_ != 4)
    {
        createGraphicalBoard();
    }

    // Just resetting the game is enough, no need to initialize gameboard again
    if (amount_of_starts_ > 1)
    {
        on_resetButton_clicked();
    }
    else
    {
        graboard_.init_empty();
        graboard_.fill(seed_);
        updateGraphicalBoard();
    }
}


/*void MainWindow::on_seedLine_textChanged(const QString &arg1)
{
    seed_ = arg1.toInt();
}


void MainWindow::on_goalLine_textChanged(const QString &arg1)
{
    goal_ = arg1.toInt();
}*/


void MainWindow::on_resetButton_clicked()
{
    enableLabels();
    graboard_.reset();
    updateGraphicalBoard();
}



void MainWindow::on_seedSpinBox_valueChanged(int arg1)
{
    seed_ = arg1;
}


void MainWindow::on_goalSpinBox_valueChanged(int arg1)
{
    goal_ = arg1;
}

