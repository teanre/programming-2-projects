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

    cout << temperature << " degrees Fahrenheit is " << (temperature - 32)/1.8 <<
            " degrees Celsius" << endl;

    return 0;
}
