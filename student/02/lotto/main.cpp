#include <iostream>

using namespace std;

int error_checks(int total_amount, int drawn_balls) {
    if (total_amount <=0 or drawn_balls <=0) {
        cout << "The number of balls must be a positive number." << endl;
        return 1;
    } else if (drawn_balls > total_amount) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return 1;
    } else {
        return 0;
    }}

unsigned long int factorial(int number) {
    unsigned long int fact = 1;
    for (int x = 1; x < number +1; ++x){
        fact *=x;
    }return fact;
}

unsigned long int probability(int total_amount, int drawn_balls) {
    unsigned long int calc = 0;
    calc = factorial(total_amount) / (factorial((total_amount-drawn_balls))*factorial(drawn_balls));{
    }return calc ;
}

int main() {

    cout << "Enter the total number of lottery balls: ";
    int total_amount = 0;
    cin >> total_amount;

    cout << "Enter the number of drawn balls: ";
    int drawn_balls = 0;
    cin >> drawn_balls;

    if (error_checks(total_amount, drawn_balls) == 1){
        return 0;}

    cout << "The probability of guessing all " << drawn_balls << " balls correctly is 1/" <<
    probability(total_amount, drawn_balls) << endl;



    return 0;
}
