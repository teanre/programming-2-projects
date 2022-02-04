/*Hitori
 *
 * Ohjelma toteuttaa Hitori-pelin.
 *
 * Ohjelman kirjoittaja
 * Nimi: Terhi Rees
 * Opiskelijanumero: 150250878
 * Käyttäjätunnus: rctere
 * E-Mail: terhi.rees@tuni.fi
 *
 *
 * */



#include <iostream>
#include <vector>
#include <random>
#include <string>

using namespace std;

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';


// Muuttaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan.
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Tulostaa pelilaudan rivi- ja sarakenumeroineen.
void print(const std::vector<std::vector<int>>& gameboard)
{
    cout << "=================" << endl;
    cout << "|   | 1 2 3 4 5 |" << endl;
    cout << "-----------------" << endl;
    for(unsigned int i = 0; i < BOARD_SIDE; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < BOARD_SIDE; ++j)
        {
            if(gameboard.at(i).at(j) == 0)
            {
                cout << EMPTY << " ";
            }
            else
            {
                cout << gameboard.at(i).at(j) << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << "=================" << endl;
}

//Luo pelilaudan käyttäjän valinnan mukaan joko satunnaisluvuilla tai
//käyttäjän syöttämillä luvuilla. Luvut tallennetaan riveittäin vektoreihin,
//jotka sijoitetaan vektoriin

std::vector<std::vector<int>> createBoard()
{
    string input = "";
    std::vector<std::vector<int>> gameboard;

    while (input != "r" || input != "R" || input != "i" || input != "I")
    {
        string input = "";
        cout << "Select start (R for random, I for input) :" << endl;
        cin >> input;

        if (input == "r" || input == "R")
        {
            unsigned int seed = 0;
            cout << "Enter a seed value: ";
            cin >> seed;

            default_random_engine gen(seed);
            uniform_int_distribution<int> distr(1, 5);


            for( int y = 0; y < 5; ++y )
            {
                std::vector<int> row;
                for( int x = 0; x < 5; ++x )
                {
                   row.push_back(distr(gen) );
                }

                gameboard.push_back( row );
            }
            break;
        }

        if (input == "i" or input == "I")
        {
            cout << "Input: " << endl;

            int numbers_from_user = 0;

            for (int x = 0; x <5; ++x)
            {
                std::vector<int> row;
                for (int y = 0; y < 5; ++y)
                {
                    cin >> numbers_from_user;
                    row.push_back(numbers_from_user);
                }

                gameboard.push_back(row);
            }

            break;
        }

    }
    return gameboard;
}

void askForCoordinates(string& x,
                       string& y,
                       std::vector<std::vector<int>>& gameboard
                       )
{

    while (x != "q" or x != "Q")
    {
        cout << "Enter removable element (x, y):";

        cin >> x;

        //jos käyttäjä haluaa lopettaa pelin, x-koordinaatti on q
        //eikä y-koordinaattia kysytä
        if (x == "q" or x == "Q")
        {
            cout << "Quitting" << endl;
            break;
        }

        cin >> y;

        unsigned int x_as_int = stoi_with_check(x);
        unsigned int y_as_int = stoi_with_check(y);

        // tarkistetaan, onko annetut koordinaatit numeroita
        // yrittämällä muuntaa stoi with check funktiolla
        if (x_as_int == 0 or y_as_int == 0)
        {
            cout << "out of board" << endl;
        }
        // jos koordinaatti on jo arvattu, eli sijainti on "nollilla"
        // annetaan virheilmoitus
        // huom!! koordinaatista miinustetaan yksi jotta vastaa indeksöintiä
        else if (gameboard.at(x_as_int-1).at(y_as_int-1) == 0)
        {
            cout << "out of board" << endl;
        }
        //muussa tapauksessa siirron teko on mahdollista
        else
        {
            gameboard.at(x_as_int-1).at(y_as_int-1) = 0;
            print(gameboard);

        }

    }

}



int main()
{
    std::vector<std::vector<int>> gameboard = createBoard();
    print(gameboard);


    string x = "";
    string y = "";


    askForCoordinates(x, y, gameboard);



    if (x == "q" || x == "Q")
    {
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
