#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), has_credit_(has_credit)
{
    generate_iban();
}

void Account::set_credit_limit(int credit_limit)
{
    if (has_credit_ == false){
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;

    } else {
        credit_limit_ = credit_limit;
    }
}

void Account::save_money(int sum)
{
    balance_ += sum;
}

bool Account::take_money(int sum)
{
    if (has_credit_ == true)
    {
        if ((balance_ - sum)< -credit_limit_){
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
            return false;
        } else {
            balance_ -= sum;
            std::cout << sum << " euros taken: new balance of " << iban_ << " is " <<
                         balance_ << " euros" << std::endl;
            return true;
        }
    }

    if (has_credit_ == false)
    {
        if(sum > balance_) {
        std::cout << "Cannot take money: balance underflow" << std::endl;
        return false;
    } else {
        balance_ -= sum;
        std::cout << sum << " euros taken: new balance of " << iban_ << " is "
        << balance_ <<  " euros" << std::endl;
        return true;
    }
}
}

void Account::transfer_to(Account& receiving_owner, int sum)
{
    if (take_money(sum) == false) {
        std::cout << "Transfer from " << iban_ << " failed" << std::endl;
    } else {
        receiving_owner.save_money(sum); }
}

void Account::print() const
{
    std::cout << owner_ << " : " << iban_ << " : " << balance_ << " euros" << std::endl;
}


// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}
