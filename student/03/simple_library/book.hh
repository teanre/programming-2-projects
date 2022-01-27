#ifndef BOOK_HH
#define BOOK_HH

#include "date.hh"
#include <iostream>


using namespace std;

class Book
{
public:
    Book();

    Book(string const& author, string const& bookname);

    void loan(const Date &loan_date);

    void print() const;

    void renew();

    void give_back();

private:

    string author_;
    string bookname_;

    bool loaned_;

    Date loaning_date_;

    Date due_date_;

};

#endif // BOOK_HH
