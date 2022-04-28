/*  2048
 *
 * Desc:
 * This program generates a game of 2048, a tile combining game where the goal
 * originally is to get from 2's to 2048. The board is SIZE x SIZE,
 * (original is 4 x 4) and every round the player chooses a direction to which
 * the tiles should move to. If they collide with a wall or a different value,
 * they will move as close as they can get. If they collide with a tile with
 * same value, they will merge and double the value. The tile will continue to
 * move and combine until a wall or other tile comes along.
 *
 * At first player gives a seed number (for randomizing starting
 * situation on game board) and a goal number. In this game player can choose
 * their goal, it only needs to be power of 2. To start playing player
 * clicks start button. Programme lets user know if given goal is not valid.
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
