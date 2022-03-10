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


bool Cards::bottom_to_top()
{
    if (top_ == nullptr || top_->next == nullptr)
    {
        return false;
    }

    Card_data *last = top_;
    Card_data *second_last = top_;

    while(last->next != nullptr)
    {
        second_last = last;
        last = last->next;
    }

    second_last->next = nullptr;
    last->next = top_;
    top_ = last;

    return true;
}


bool Cards::top_to_bottom()
{
    if (top_ == nullptr || top_->next == nullptr)
    {
        return false;
    }

    Card_data *original_topmost = top_;
    Card_data *last = top_;

    // second card becomes the first one
    top_ = top_->next;

    while(last->next != nullptr)
    {
        //ekasta vika
        last = last->next;
    }

    last->next = original_topmost;
    original_topmost->next = nullptr;
    return true;
}


void Cards::print_from_bottom_to_top(std::ostream &s)
{
    recursive_print(top_, s);
}



Cards::~Cards()
{
    while (top_ != nullptr)
    {
        Card_data *card_to_delete = top_;
        top_ = card_to_delete->next;
        delete card_to_delete;
    }
}

int Cards::recursive_print(Card_data *top, std::ostream &s)
{
    int i = 1;

    if (top->next != nullptr)
    {
        i += recursive_print(top->next, s);
    }

    s << i << " : " << top->data << std::endl;

    return i;
}
