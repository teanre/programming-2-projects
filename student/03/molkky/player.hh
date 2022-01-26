#ifndef PLAYER_HH
#define PLAYER_HH
#include <iostream>
#include <string>

const int WINNING_POINTS = 50;
const int PENALTY_POINTS = 25;

class Player
{
public:
    Player();

    Player(std::string name);

    std::string get_name();

    void add_points(int points);

    bool has_won();

    int get_points();


private:

    std::string name_;
    int points_;

};




#endif // PLAYER_HH
