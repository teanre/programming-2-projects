#include <iostream>

using namespace std;

//pieni a
const int ASCII_MIN = 97;
//pieni z
const int ASCII_MAX = 122;
const int KEY_LENGTH = 26;

const string ERROR_LENGTH = "Error! The encryption key must contain 26 characters." ;
const string LOWER_CASE = "Error! The encryption key must contain only lower case characters.";
const string ERROR_ALPHABET = "Error! The encryption key must contain all alphabets a-z.";
const string LOWER_CASE_ENCRKEY = "Error! The encryption key must contain all alphabets a-z.";

bool check_length(string string_input) {

    if (string_input.length() != KEY_LENGTH) {
        return false;
    }
    return true;
    }


bool check_lower_case(string string_input) {

    for (uint i = 1; i < string_input.length(); ++i) {
        char c = string_input.at(i);
        if (c < ASCII_MIN || c > ASCII_MAX) {
            return false;
        }
    }
    return true;
    }


bool check_alphabet(string string_input){

    for (uint c = ASCII_MIN; c < ASCII_MAX; ++c){

        if (string_input.find(c) == string::npos){
            return false;
        }
    }
    return true;
    }

string encryption(string encryption_key, string text){

    for (uint i = 0; i < text.length(); ++i){
        char c_in_text = text.at(i);
        text.at(i) = encryption_key.at(c_in_text - ASCII_MIN);
    }
    return text;
}


int main()
{
    cout << "Enter the encryption key: ";
    string encr_key = "";
    cin >> encr_key;

    if (!check_length(encr_key)) {
        cout << ERROR_LENGTH << endl;
        return EXIT_FAILURE;
    } else if (!check_lower_case(encr_key)) {
        cout << LOWER_CASE << endl;
        return EXIT_FAILURE;
    } else if (!check_alphabet(encr_key)){
        cout << ERROR_ALPHABET << endl;
        return EXIT_FAILURE;
    }

    string text = "";
    cout << "Enter the text to be encrypted: ";
    cin >> text;
    //virhetarkastus lower case

    if (!check_lower_case(text)) {
        cout << LOWER_CASE_ENCRKEY << endl;
        return EXIT_FAILURE;
    }

    ;

    cout << "Encrypted text: " << encryption(encr_key, text) << endl;

    return 0;
}
