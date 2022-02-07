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


bool didYouWin(std::vector<std::vector<int>>& gameboard);
//bool didYouLose(std::vector<std::vector<int>>& gameboard);

//bool errorChecks(string x, string y, std::vector<std::vector<int>>& gameboard);

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

//checks if the given coordinates can be used
bool errorChecks(string& x, string& y, std::vector<std::vector<int>>& gameboard)
{
    unsigned int x_as_int = stoi_with_check(x);
    unsigned int y_as_int = stoi_with_check(y);

    //tarkistetaan osuuko annetut koordinaatit koordinaatistoon
    //mikäli käyttäjä antanut muun kun numeron, stoi with check palauttaa nollan
    if (x_as_int < 1 || x_as_int > 5 || y_as_int < 1 || y_as_int > 5)
    {
        cout << "Out of board" << endl;
        return false;
    }

    //jos koordinaatit jo arvattu, ohjelma ilmoittaa
    else if (gameboard.at(x_as_int-1).at(y_as_int-1) == 0)
    {
        cout << "Already removed" << endl;
        return false;
    }
    return true;
}


void makeAmove(string& x, string& y, std::vector<std::vector<int>>& gameboard)
{
    unsigned int x_as_int = stoi_with_check(x);
    unsigned int y_as_int = stoi_with_check(y);

    gameboard.at(x_as_int-1).at(y_as_int-1) = 0;
    print(gameboard);
    didYouWin(gameboard);

}


//asks for coordinates from user
//if user inputs x, quit the game
void askForCoordinates(string& x,
                       string& y,
                       std::vector<std::vector<int>>& gameboard)
{

    while (not didYouWin(gameboard))
    {
        cout << "Enter removable element (x, y):";

        cin >> x;

        //jos käyttäjä haluaa lopettaa pelin, x-koordinaatti on q
        //eikä y-koordinaattia kysytä
        if (x == "q" or x == "Q")
        {
            cout << "Quitting" << endl;
            return;
        }

        else
        {
        cin >> y;
        }

        //jos errorilta tulee true, tekee muuvin
        if (errorChecks(x, y, gameboard))
        {
            makeAmove(x, y, gameboard);
        }

    }

}



bool didYouWin(std::vector<std::vector<int>>& gameboard)
{
    //Voitto: joka rivillä ei ole samaa numeroa kuin kerran
    //käydään jokaisen rivin alkiot läpi, mikäli kullakin rivillä
    //1-5 vain kerran, voitat

    std::vector<int> row;
    for(int y = 0; y < 5; ++y)
    {
        row = gameboard.at(y);

        int nr_1 = 0;
        int nr_2 = 0;
        int nr_3 = 0;
        int nr_4 = 0;
        int nr_5 = 0;

        for (int nr : row)
        {
            if (nr == 1)
            {
                nr_1 +=1;
            }
            if (nr == 2)
            {
                nr_2 +=1;
            }
            if (nr == 3)
            {
                nr_3 +=1;
            }
            if (nr == 4)
            {
                nr_4 +=1;
            }
            if (nr == 5)
            {
                nr_5 +=1;
            }
        }

        if (nr_1 > 1 || nr_2 > 1 or nr_3 > 1 || nr_4 > 1 || nr_5 > 1)
        {
            return false;
        }

        }


    return true;

}



int main()
{
    std::vector<std::vector<int>> gameboard = createBoard();
    print(gameboard);


    string x = "";
    string y = "";


    // peli jatkuu kunnes didyouwinistä tulee true tai didyoulosesta tulee true
    // tai x - koordinaatti on q tai Q
    while (true)
    {

        askForCoordinates(x, y, gameboard);

        if (x == "q" || x == "Q")
        {
            break;
        }

        if (didYouWin(gameboard))
        {
            cout << "You won" << endl;
            break;
        }


    }
    return EXIT_SUCCESS;
}
