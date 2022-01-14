#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a number: ";
    int number = 0;
    cin >> number;

    int cube = 0;
    cube = number * number * number;

    if (cube < 0){
        cout << "Error! The cube of " << number << " is not " <<
                cube << "." << endl;
    } else if (cube / number / number != number){
        cout << "Error! The cube of " << number << " is not " <<
                cube << "." << endl;
    }else {
    cout << "The cube of " << number << " is " << cube << "." << endl;
    }

    return 0;
}
