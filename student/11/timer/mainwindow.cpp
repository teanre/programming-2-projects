#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //qtimeri
    timer = new QTimer(parent);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateLcd);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startTimer);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopTimer);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::resetTimer);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startTimer()
{
    timer->start(1000);
}

void MainWindow::stopTimer()
{
    timer->stop();
    updateLcd();
}

void MainWindow::resetTimer()
{
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);
    time = 0;
    startTimer();
}

void MainWindow::updateLcd()
{
    ui->lcdNumberMin->display(time/60);
    ui->lcdNumberSec->display(time%60);
}

