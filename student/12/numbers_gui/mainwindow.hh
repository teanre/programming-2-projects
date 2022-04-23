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
    MainWindow(GameBoard& board, QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent* event) override;

private slots:

    void on_startButton_clicked();

    //void on_seedLine_textChanged(const QString &arg1);

   // void on_goalLine_textChanged(const QString &arg1);

    void on_resetButton_clicked();


    void on_seedSpinBox_valueChanged(int arg1);

    void on_goalSpinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui_;

    QGraphicsScene* scene_;
    GameBoard& graboard_;

    std::vector<std::vector<QLabel*>> labels_;

    int boardsize_;
    int seed_;
    int goal_;

    int amount_of_starts_;

    const int STEP = 50;
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 260;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 680;

    void createGraphicalBoard();

    void updateGraphicalBoard();

    void winColors();

    void lossColors();

    void disableLabels();

    void enableLabels();

};
#endif // MAINWINDOW_HH
