#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameBoard graphicalGameBoard;
    MainWindow w(graphicalGameBoard);
    w.show();
    return a.exec();
}
