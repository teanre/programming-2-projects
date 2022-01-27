#include "book.hh"
#include "date.hh"

#include <iostream>


Book::Book(string const& author, string const& bookname):
  author_(author), bookname_(bookname), loaned_(false), loaning_date_(Date()), due_date_(Date())
{
}

void Book::loan(Date const& loan_date)
{
    if (loaned_ == false){
        loaning_date_ = loan_date;
        due_date_ = loaning_date_;
        due_date_.advance(28);
        loaned_ = true;
    } else {
        cout << "Already loaned: cannot be loaned" << endl;
    }
}

void Book::print() const
{
    cout << author_ << " : " << bookname_ << endl;
    if (loaned_ == false){
        cout << "- available" << endl;
    } else {
        cout << "- loaned: ";
        loaning_date_.print();
        cout << "- to be returned: ";
        due_date_.print();
        cout << endl;
    }
}

void Book::renew()
{
    if (loaned_ == true){
        due_date_.advance(28);
    } else {
        cout << "Not loaned: cannot be renewed" << endl;
    }
}

void Book::give_back()
{
    loaned_ = false;
}
