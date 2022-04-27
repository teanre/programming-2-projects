/*  2048-game
 *
 *  2048 is a game where player's goal is to move the tiles untial goal number
 *  is reached. At first player gives a seed number (for randomizing starting
 *  situation on game board) and a goal number. Original goal is 2048 but user
 *  can choose their own goal, it only needs to be power of 2. To start player
 *  clicks start button. Programme lets user know if given goal is not valid.
 *
 *  Gameboard has tiles with value 2 at start in random places. When two tiles
 *  with the same number touch, they merge into one tile, adding up their values.
 *
 *  Player moves the tiles with keyboard buttons:
 *  a - left
 *  d - right
 *  w - up
 *  s - down
 *
 * After a move a new tile with value 2 appears on the gameboard.
 * Player wins if they reach the goal number. That is notified by text and green
 * interface color. Player loses if the board fills up and no new moves are
 * possible. In that situation interface turns red and text notification will
 * appear as well.
 *
 * It is possible to restart the game by pressing reset-button.
 *
 *
 * Program author
 * Name: Terhi Rees
 * Student number: 150250878
 * UserID: rctere
 * E-Mail: terhi.rees@tuni.fi
 *
 */

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
