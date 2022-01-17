#include <iostream>

using namespace std;

void error_checks(int total_amount, int drawn_balls) {
    if (total_amount <=0 or drawn_balls <=0) {
        cout << "The number of balls must be a positive number." << endl;
        return;
    } else if (drawn_balls > total_amount) {
        cout << "The maximum number of drawn balls if the total amount of balls." << endl;
        return;
    }}

int main() {

    cout << "Enter the total number of lottery balls: " << endl;
    int total_amount = 0;
    cin >> total_amount;

    cout << "Enter the number of drawn balls: " << endl;
    int drawn_balls = 0;
    cin >> drawn_balls;

    error_checks(total_amount, drawn_balls);


    return 0;
}
