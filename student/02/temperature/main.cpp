#include <iostream>

using namespace std;

int main()
{
    double temperature = 0;
    cout << "Enter a temperature: ";
    cin >> temperature;

    // Write your code here

    cout << temperature << " degrees Celsius is " << 1.8 * temperature + 32 <<
            " degrees Fahrenheit" << endl;

    return 0;
}
