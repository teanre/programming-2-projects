#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gameboard.hh"
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGridLayout>
#include <QLCDNumber>
#include <QDebug>
#include <iostream>

int LEFT_MARGIN = 50; // x coordinate
int TOP_MARGIN = 50; // y coordinate

const Coords DEFAULT_DIR = {0, 0};
const Coords LEFT = {0, -1};
const Coords UP = {-1, 0};
const Coords RIGHT = {0, 1};
const Coords DOWN = {1, 0};

MainWindow::MainWindow(GameBoard& board, QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
    , scene_()
    , timer_()
    , graboard_(board)
    , labels_()
    , seed_(0)
    , goal_(2048)
    , amount_of_starts_(0)
    , time_(0)
{
    ui_->setupUi(this);

    timer_ = new QTimer(this);

    connect(timer_, &QTimer::timeout, this, &MainWindow::updateLcd);
    connect(ui_->startButton, &QPushButton::clicked, this, &MainWindow::startTimer);
    //connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopTimer);
    connect(ui_->resetButton, &QPushButton::clicked, this, &MainWindow::resetTimer);

    this->setStyleSheet("QMainWindow {background-color: lightGrey;}");

    scene_ = new QGraphicsScene(this);

    ui_->graphicsView->setGeometry(LEFT_MARGIN, TOP_MARGIN,
                                   SIZE * STEP + 2, SIZE * STEP + 2);


    ui_->graphicsView->setScene(scene_);

    scene_->setSceneRect(0, 0, SIZE * STEP - 1, SIZE * STEP - 1);

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
            event->ignore();
            stopTimer();
            return;
        }
        else if (graboard_.is_full())
        {
            QString text = "Can't add new tile, you lost!";
            ui_->textBrowser->setText(text);
            lossColors();
            disableLabels();
            stopTimer();
            return;
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
                scene_->addRect(column, row +(row * STEP), STEP, STEP, blackPen, whiteBrush);
                label->setGeometry(LEFT_MARGIN + column, TOP_MARGIN + row + (row * STEP), STEP, STEP);
                label->setAlignment(Qt::AlignCenter);
            }
            else if (column > 0)
            {
                scene_->addRect(column+(column*STEP), row+(row*STEP), STEP, STEP, blackPen, whiteBrush);
                label->setGeometry(LEFT_MARGIN + column + (column * STEP), TOP_MARGIN + row + (row * STEP), STEP, STEP);
                label->setAlignment(Qt::AlignCenter);
            }
            else
            {
               scene_->addRect(column+(column*STEP), row, STEP, STEP, blackPen, whiteBrush);
               label->setGeometry(LEFT_MARGIN + TOP_MARGIN + column + (column * STEP), row, STEP, STEP);
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

void MainWindow::winColors()
{
    this->setStyleSheet("QMainWindow {background-color: green;}");
}

void MainWindow::lossColors()
{
    this->setStyleSheet("QMainWindow {background-color: red;}");
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

void MainWindow::deleteLabels()
{
    for (auto& vec : labels_)
    {
        for(auto& label: vec)
        {
            delete label;
        }
    }
}

void MainWindow::on_startButton_clicked()
{
    amount_of_starts_++;

    // Just resetting the game is enough, no need to initialize gameboard again
    if (amount_of_starts_ > 1)
    {
        on_resetButton_clicked();
        resetTimer();
    }
    else
    {
        graboard_.init_empty();
        graboard_.fill(seed_);
        updateGraphicalBoard();
    }
}

void MainWindow::on_resetButton_clicked()
{
    this->setStyleSheet("QMainWindow {background-color: lightGrey;}");
    enableLabels();
    graboard_.reset();
    updateGraphicalBoard();
    ui_->textBrowser->setText("");
}

void MainWindow::on_seedSpinBox_valueChanged(int arg1)
{
    seed_ = arg1;
}


void MainWindow::on_goalSpinBox_valueChanged(int arg1)
{
    goal_ = arg1;
}

void MainWindow::startTimer()
{
    timer_->start(1000);
}

void MainWindow::stopTimer()
{
    timer_->stop();
    updateLcd();
}

void MainWindow::resetTimer()
{
    ui_->timerLcd->display(0);
    time_ = 0;
    startTimer();
}

void MainWindow::updateLcd()
{
    qDebug() << "aika o:" << time_ ;
    time_++;
    ui_->timerLcd->display(time_);
}
