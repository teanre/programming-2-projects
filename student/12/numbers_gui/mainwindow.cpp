/*
 * Program author
 * Name: Terhi Rees
 * Student number: 150250878
 * UserID: rctere
 * E-Mail: terhi.rees@tuni.fi
 *
 */

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gameboard.hh"
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGridLayout>
#include <QLCDNumber>
#include <QDebug>

MainWindow::MainWindow(GameBoard& board, QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
    , scene_()
    , timer_()
    , graphicalboard_(board)
    , labels_()
    , seed_(0)
    , goal_(2048)
    , amount_of_starts_(0)
    , time_(0)
{
    ui_->setupUi(this);

    timer_ = new QTimer(this);

    connect(timer_, &QTimer::timeout, this, &MainWindow::updateLcd);

    this->setStyleSheet("QMainWindow {background-color: lightGrey}");

    scene_ = new QGraphicsScene(this);

    ui_->graphicsView->setGeometry(LEFT_MARGIN, TOP_MARGIN,
                                   SIZE * STEP + 2, SIZE * STEP + 2);

    ui_->graphicsView->setScene(scene_);

    scene_->setSceneRect(0, 0, SIZE * STEP - 1, SIZE * STEP - 1);

    ui_->timerLcd->setStyleSheet("QLCDNumber {background-color: white}");

    createGraphicalBoard();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    Coords dir = DEFAULT_DIR;

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
        if (graphicalboard_.move(dir, goal_))
        {
            QString goalqs = QString::number(goal_);
            QString text = "You reached the goal value of " + goalqs + "!";
            ui_->textBrowser->setText(text);
            winColorChange();
            //disableLabels();
            stopTimer();
        }
        else if (graphicalboard_.is_full())
        {
            QString text = "Can't add new tile, you lost!";
            ui_->textBrowser->setText(text);
            lossColorChange();
            disableLabels();
            stopTimer();
            return;
        }
        graphicalboard_.new_value(false);
    }
    updateGraphicalBoard();
}


void MainWindow::createGraphicalBoard()
{
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);

    std::vector<QLabel*> helper;

    for (int row = 0; row < SIZE; ++row)
    {
        for (int column = 0; column < SIZE; ++column)
        {
            QLabel* label = new QLabel("", this);
            if (column == 0)
            {
                scene_->addRect(column,
                                row + (row * STEP),
                                STEP, STEP,
                                blackPen, whiteBrush);
                label->setGeometry(LEFT_MARGIN + column,
                                   TOP_MARGIN + row + (row * STEP),
                                   STEP, STEP);
                label->setAlignment(Qt::AlignCenter);
            }
            else if (column > 0)
            {
                scene_->addRect(column + (column * STEP),
                                row + (row*STEP),
                                STEP, STEP,
                                blackPen, whiteBrush);
                label->setGeometry(LEFT_MARGIN + column + (column * STEP),
                                   TOP_MARGIN + row + (row * STEP),
                                   STEP, STEP);
                label->setAlignment(Qt::AlignCenter);
            }
            else
            {
               scene_->addRect(column + (column * STEP),
                               row,
                               STEP, STEP,
                               blackPen, whiteBrush);
               label->setGeometry(LEFT_MARGIN + TOP_MARGIN
                                  + column + (column * STEP),
                                  row, STEP, STEP);
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
            int nr = graphicalboard_.get_item(coords)->get_value();
            QString s = QString::number(nr);
            labels_.at(j).at(i)->setText(s);

            // change tile colour according to the value
            if (nr >= 0 && nr <= 2048)
            {
                QString text = "QLabel {background-color: " + COLORS.at(nr) +"}";
                labels_.at(j).at(i)->setStyleSheet(text);
            }
        }
    }
}

bool MainWindow::goalIsValid(int n)
{
    if ( n == 0 )
    {
        ui_->textBrowser->
            setText("Goal is not valid, try again! Must be a power of two.");
        return false;
    }
    while( n != 1 )
    {
        n = n/2;

        if( n % 2 != 0 && n != 1 )
        {
            ui_->textBrowser->
               setText("Goal is not valid, try again! Must be a power of two.");
            return false;
        }
    }
    return true;
}

void MainWindow::winColorChange()
{
    this->setStyleSheet("QMainWindow {background-color: rgb(124, 252, 0)}");
}

void MainWindow::lossColorChange()
{
    this->setStyleSheet("QMainWindow {background-color: rgb(255, 69, 0)}");
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
    if ( goalIsValid(goal_) )
    {
        amount_of_starts_++;
        startTimer();
         // Resetting the game is enough, no need to initialize gameboard again
        if (amount_of_starts_ > 1)
        {
            on_resetButton_clicked();
            resetTimer();
        }
        else
        {
            graphicalboard_.init_empty();
            graphicalboard_.fill(seed_);
            updateGraphicalBoard();
        }
    }
}

void MainWindow::on_resetButton_clicked()
{
    if ( goalIsValid(goal_) )
    {
        enableLabels();
        resetTimer();
        this->setStyleSheet("QMainWindow {background-color: lightGrey;}");       
        graphicalboard_.reset();
        updateGraphicalBoard();
        ui_->textBrowser->setText("");
    }
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
    time_++;
    ui_->timerLcd->display(time_);
}
