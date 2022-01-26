#include "player.hh"


Player::Player(std::string name):
    name_(name), points_(0)
{
}

std::string Player::get_name()
{
    return name_;
}

void Player::add_points(int points)
{
    points_ += points;
    if (points_ > WINNING_POINTS){
        points_ = PENALTY_POINTS;
        std::cout << name_ << " gets penalty points!" << std::endl;
    }
}


bool Player::has_won()
{
    if (points_ == WINNING_POINTS){
        return true;
    } else {
        return false;
    }
}

int Player::get_points()
{
    return points_;
}
