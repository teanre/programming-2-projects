#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string input_file = "";
    cout << "Input file: ";
    getline(cin, input_file);

    string output_file = "";
    cout << "Output file: ";
    getline(cin, output_file);

    ifstream inputf(input_file);
    ofstream outputf(output_file);
    if (not inputf)
    {
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
    }
    else
    {
        string row;
        int row_number = 1;
        while ( getline (inputf, row))
        {
            outputf << row_number << " " <<  row << endl;
            row_number += 1;
        }
        inputf.close();
        outputf.close();
    }

    return EXIT_FAILURE;
}
