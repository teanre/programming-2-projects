#include "cards.hh"
#include <iostream>

// TODO: Implement the methods here

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

/*bool Cards::remove(int &id)
{

}

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
