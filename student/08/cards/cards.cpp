#include "cards.hh"
#include <iostream>

Cards::Cards(): top_(nullptr)
{}

Card_data *Cards::get_topmost()
{
   return top_;
}

void Cards::add(int id)
{
    Card_data *new_card = new Card_data;

    new_card->data = id;
    new_card->next = top_;
    top_ = new_card;
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
    Card_data *current = top_;

    uint i = 1;

    while(current)
    {
        s << i << " : " << current->data << std::endl;
        current = current->next;
        ++i;
    }
}

bool Cards::remove(int &id)
{
    if (top_ == nullptr)
    {
        return false;
    }

    Card_data *topmost = top_;
    id = topmost->data;

    if (topmost->next == nullptr)
    {
        top_ = nullptr;
    }
    else
    {
        top_ = topmost->next;
    }
    delete topmost;
    return true;
}

/*
bool Cards::bottom_to_top()
{

}

bool Cards::top_to_bottom()
{

}

void Cards::print_from_bottom_to_top(std::ostream &s)
{

}*/

Cards::~Cards()
{

}
