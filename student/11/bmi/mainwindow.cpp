#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QIntValidator* ival = new QIntValidator(1, 999, this);
    ui->heightLineEdit->setValidator(ival);
    ui->weightLineEdit->setValidator(ival);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_weightLineEdit_editingFinished()
{
    weigth_ = ui->weightLineEdit->text();
}


void MainWindow::on_heightLineEdit_editingFinished()
{
    heigth_ = ui->heightLineEdit->text();
}


void MainWindow::on_countButton_clicked()
{
    calculateBMI(weigth_, heigth_);
}

void MainWindow::calculateBMI(QString weight, QString height)
{
    float bmi = weight.toFloat() / ( (height.toFloat()/100) * (height.toFloat()/100) );
    QString bmiAsString = QString::number(bmi);

    if (bmi < 18.5 )
    {
        ui->resultLabel->setText(bmiAsString);
        ui->infoTextBrowser->setText("You are underweight.");
    }
    else if (bmi > 25)
    {
        ui->resultLabel->setText(bmiAsString);
        ui->infoTextBrowser->setText("You are overweight.");
    }
    else
    {
        ui->resultLabel->setText(bmiAsString);
        ui->infoTextBrowser->setText("Your weight is normal.");
    }
}

