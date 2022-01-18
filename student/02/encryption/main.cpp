#include <iostream>
#include <cctype>

using namespace std;

int main()
{
    cout << "Enter the encryption key: ";
    string encr_key = "";
    cin >> encr_key ;

    if (encr_key.length() < 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;}
    //} else if ()

     //Error! The encryption key must contain only lower case characters.

    //Error! The encryption key must contain all alphabets a-z.
    return 0;
}
