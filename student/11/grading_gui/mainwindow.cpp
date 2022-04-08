#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gradecounter.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spinBoxN_valueChanged(int arg1)
{
    n_points_ = arg1;
}


void MainWindow::on_spinBoxG_valueChanged(int arg1)
{
    g_points_ = arg1;
}


void MainWindow::on_spinBoxP_valueChanged(int arg1)
{
    p_points_ = arg1;
}


void MainWindow::on_spinBoxE_valueChanged(int arg1)
{
    exam_grade_ = arg1;
}



void MainWindow::on_countPushButton_clicked()
{
    QString text = "Total grade: ";
    int total_grade = 0;
    total_grade = count_final_grade(n_points_, g_points_, p_points_, exam_grade_);
    QString grade_as_text = "";
    grade_as_text = QString::number(total_grade);
    text.append(grade_as_text);
    ui->textBrowser->setText(text);

}

