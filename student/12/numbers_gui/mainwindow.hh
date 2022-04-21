#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH
#include "gameboard.hh"
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPushButton>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_seedNumberBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui_;

    QGraphicsScene* scene_;
    QGraphicsRectItem* rect_;
    GameBoard graboard_;
    std::vector< std::vector< std::shared_ptr<NumberTile> > > board_;
    std::vector<std::vector<QLabel*>> labels_;
    QList<QPushButton*> board;
    const int STEP = 100;
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 260;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 680;

    void createGraphicalBoard();

    //void createButtonBoard();

};
#endif // MAINWINDOW_HH
