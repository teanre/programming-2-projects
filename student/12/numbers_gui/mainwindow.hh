/*
* Program author
* Name: Terhi Rees
* Student number: 150250878
* UserID: rctere
* E-Mail: terhi.rees@tuni.fi
*/

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH
#include "gameboard.hh"
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(GameBoard& board, QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent* event) override;

private slots:

    void on_startButton_clicked();

    void on_resetButton_clicked();

    void on_seedSpinBox_valueChanged(int arg1);

    void on_goalSpinBox_valueChanged(int arg1);

    void startTimer();
    void stopTimer();
    void resetTimer();
    void updateLcd();


private:
    Ui::MainWindow *ui_;

    QGraphicsScene* scene_;

    QTimer* timer_;

    GameBoard& graphicalboard_;

    // Holds information of the labels, which will show the value of tiles on ui
    std::vector<std::vector<QLabel*>> labels_;

    int seed_;
    int goal_;

    // How many times game has been started
    int amount_of_starts_;
    int time_;

    const int STEP = 50;
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 260;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 680;

    // Creates the user interface of gameboard.
    void createGraphicalBoard();

    // Updates the interface (after a move). Color of a tile changes according
    // to it's value. There are different colors for first 11 possible values,
    // until tile would reach 2048, after that tiles will be white.
    void updateGraphicalBoard();

    // Checks if the given goal number is valid, a power of 2.
    // Returns false if not.
    bool goalIsValid(const int n);

    // Changes the user interface to green when game won
    void winColorChange();

    // Changes the user interface to red when game lost
    void lossColorChange();

    // Disables the labels (that show the value, numbers on gameboard tiles)
    void disableLabels();

    // Enables the labels again.
    void enableLabels();

};
#endif // MAINWINDOW_HH
