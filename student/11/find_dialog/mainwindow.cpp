#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <iostream>

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



bool MainWindow::openFile(const QString &filename, QStringList &content)
{
    QString text = "";
    QFile file(filename);
    if ( not file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        text = "File not found";
        ui->textBrowser->setText(text);
        return false;
    }
    else
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
           QString line = in.readLine();
           content = line.split(" ");
        }
    }
    return true;
}

void MainWindow::searchForWord(const QString &word, const QStringList &content)
{
    QString text = "";

        //jos sana löytyy: Word found
        if (ui->matchCheckBox->isChecked() && content.contains(word) )
        {
            text = "Word found";
            ui->textBrowser->setText(text);
        }
        else if (!ui->matchCheckBox->isChecked() && content.contains(word, Qt::CaseInsensitive))
        {
            text = "Word found";
            ui->textBrowser->setText(text);
        }
        //jos sanaa ei löydy: Word not found
        else
        {
            text = "Word not found";
            ui->textBrowser->setText(text);
        }
}


void MainWindow::on_fileLineEdit_textChanged(const QString &arg1)
{
    filename_ = arg1;
}

void MainWindow::on_keyLineEdit_textChanged(const QString &arg1)
{
    word_ = arg1;
}


void MainWindow::on_findPushButton_clicked()
{
    QStringList content;
    if (openFile(filename_, content) )
    {
        if (word_.isEmpty())
        {
            QString text = "File found";
            ui->textBrowser->setText(text);
        }
        else
        {
            searchForWord(word_, content);
        }
    }
}




