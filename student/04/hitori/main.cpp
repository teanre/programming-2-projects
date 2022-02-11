/*Hitori
 *
 *Kuvaus:
 *   Ohjelma toteuttaa Hitori-pelin. Pelissä on peliruudukko kooltaan
 * 5 x 5. Kukin ruutu sisältää jonkin numeroista 1-5. Vaaka- ja
 * pystyriveillä voi aluksi olla useita samoja numeroita, mutta
 * tarkoituksena on poistaa numeroita niin, että kullakin vaaka- ja
 * pystyrivillä on kutakin numeroa maksimissaan yksi kappale. Vierekkäisten
 * ruutujen numeroita ei saa poistaa, eikä mikään jäljelle
 * jäävä numero saa jäädä irralleen muista, eli sen ympäriltä
 * (yläpuolelta, alapuolelta, vasemmalta, oikealta) ei saa poistaa
 * kaikkia numeroita.
 *   Aluksi käyttäjältä kysytään, täytetäänkö peliruudukko satunnaisesti
 * arvottavilla luvuilla 1-5 vai käyttäjän valitsemilla 25 luvulla.
 * Ensimmäisessä vaihtoehdossa käyttäjältä kysytään satunnaisluku-
 * generaattorin siemenlukua ja jälkimmäisessä häntä pyydetään syöttämään
 * 25 lukua.
 *   Joka kierroksella käyttäjältä kysytään poistettavan numeron
 * koordinaatteja eli kahta lukua. Peli päättyy pelaajan voittoon,
 * jos peliruudukon kaikilla vaaka- ja pystyriveillä esiintyy kukin
 * numero 1-5 korkeintaan kerran. Peli päättyy pelaajan häviöön,
 * jos hän poistaa jo poistetun numeron viereisen numeron tai jos
 * jokin numero jää irralleen muista.
 *   Ohjelma tarkistaa annetut koordinaatit. Koordinaattien pitää olla
 * peliruudukon sisällä, ja niiden osoittaman ruudun pitää sisältää
 * numero, eli jo poistettua numeroa ei voi poistaa toiseen kertaan.
 *   Pelin päättyessä kerrotaan, voittiko vai hävisikö pelaaja.
 *
 *
 * Ohjelman kirjoittaja
 * Nimi: Terhi Rees
 * Opiskelijanumero: 150250878
 * Käyttäjätunnus: rctere
 * E-Mail: terhi.rees@tuni.fi
 * */


#include <iostream>
#include <vector>
#include <random>
#include <string>

using namespace std;

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';
const unsigned int EMPTY_SPACE = 0;

using Gameboard = std::vector<std::vector<int>>;

unsigned int stoi_with_check(const string& str);
void print(const Gameboard& gameboard);
Gameboard createBoard();
void askForCoordinates(string& x, string& y, Gameboard& gameboard);
bool areCoordinatesValid(string& x, string& y, Gameboard& gameboard);
void makeAmove(string& x, string& y, Gameboard& gameboard);
bool didYouLose(Gameboard& gameboard);
bool didYouLoseEmpty(Gameboard& gameboard);
bool didYouLoseLonelySpace(Gameboard& gameboard);
bool didYouWin(Gameboard& gameboard);
bool didYouWinRows(Gameboard& gameboard);
bool didYouWinColumns(Gameboard& gameboard);

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
void print(const Gameboard& gameboard)
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

// Luo pelilaudan käyttäjän valinnan mukaan joko satunnaisluvuilla
// tai käyttäjän syöttämillä luvuilla.
Gameboard createBoard()
{
    string input = "";
    std::vector<std::vector<int>> gameboard;

    while (input != "r" || input != "R" || input != "i" || input != "I")
    {
        string input = "";
        cout << "Select start (R for random, I for input): ";
        getline(cin, input);

        // luodaan lauta satunnaisluvuilla
        if (input == "r" || input == "R")
        {
            int int_seed = -1;

            while (int_seed <= 0)
            {
                string seed = "";
                cout << "Enter a seed value: ";
                cin >> seed;

                int_seed = stoi_with_check(seed);

                // seed tulee olla positiivinen kokonaisluku,
                // kyselyä jatketaan kunnes oikea syöte käyttäjältä
                if (int_seed > 0)
                {
                    default_random_engine gen(int_seed);
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
                }
            }
            break;
        }

        // kysytään 25 numeroa käyttäjältä
        if (input == "i" or input == "I")
        {
            cout << "Input: ";

            int number_from_user = 0;

            for (int x = 0; x <5; ++x)
            {
                std::vector<int> row;
                for (int y = 0; y < 5; ++y)
                {
                    cin >> number_from_user;
                    row.push_back(number_from_user);
                }
                gameboard.push_back(row);
            }
            break;
        }
    }
    return gameboard;
}

// Kysyy käyttäjältä koordinaatit ja tekee siirrot niin kauan kuin mahdollista.
void askForCoordinates(string& x,
                       string& y,
                       Gameboard& gameboard)
{
    while (true)
    {
        cout << "Enter removable element (x, y): ";

        cin >> x;

        // jos käyttäjä haluaa lopettaa pelin
        if (x == "q" || x == "Q")
        {
            cout << "Quitting" << endl;
            return;
        }

        cin >> y;

        // tarkistetaan koordinaatit, tehdään siirto jos ovat ok
        if (areCoordinatesValid(x, y, gameboard))
        {
            makeAmove(x, y, gameboard);

            // Tarkistetaan tuliko häviö tai voitto.
            // Muussa tapauksessa siirtoja jatketaan.
            if (didYouLose(gameboard) ||
                didYouWin(gameboard))
            {
                break;
            }
        }
    }
}

// Tarkistaa käyttäjän antamien koordinaattien käyttökelpoisuuden,
// paluuarvona true mikäli koordinaatit ok ja siirto voidaan tehdä.
bool areCoordinatesValid( string& x,
                          string& y,
                          Gameboard& gameboard)
{
    // Muunnetaan koordinaatit numeerisiksi arvoiksi (mikäli
    // käyttäjä antanut muun kun numeron, stoi with check palauttaa nollan)
    unsigned int x_as_int = stoi_with_check(x);
    unsigned int y_as_int = stoi_with_check(y);

    // Tarkistetaan osuvatko annetut koordinaatit ruutuun
    if (x_as_int < 1 || x_as_int > BOARD_SIDE ||
            y_as_int < 1 || y_as_int > BOARD_SIDE)
    {
        cout << "Out of board" << endl;
        return false;
    }

    // Jos koordinaatit jo arvattu, ohjelma ilmoittaa myös tästä
    else if (gameboard.at(y_as_int-1).at(x_as_int-1) == EMPTY_SPACE)
    {
        cout << "Already removed" << endl;
        return false;
    }
    return true;
}


// Tekee siirron, tulostaa pelilaudan siirron jälkeen.
void makeAmove(string& x,
               string& y,
               Gameboard& gameboard)
{
    unsigned int x_as_int = stoi_with_check(x);
    unsigned int y_as_int = stoi_with_check(y);

    gameboard.at(y_as_int-1).at(x_as_int-1) = EMPTY_SPACE;
    print(gameboard);
}


// Tarkistaa alifunktioiden avulla häviötilanteet.
bool didYouLose(Gameboard& gameboard)
{
    if (didYouLoseEmpty(gameboard) || didYouLoseLonelySpace(gameboard))
    {
        return true;
    }
    return false;
}

// Tarkistaa, onko vierekkäisiä tai alekkaisia ruutuja tyhjänä.
bool didYouLoseEmpty(Gameboard& gameboard)
{
    // tarkistetaan vaakariveittäin onko vierekkäiset tyhjiä
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            // paitsi rivin viimeisen ruudun kohdalla ei tarvitse enää tarkistaa
            if (j == 4 )
            {
                continue;
            }
            else if (gameboard.at(i).at(j) == EMPTY_SPACE
                     && gameboard.at(i).at(j+1) == EMPTY_SPACE)
            {
                        return true;
            }
        }
    }

    // katsotaan sarakkeittain, onko allaoleva ruutu tyhjä
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            // alimman rivin osalta ei tarvitse enää tarkistaa
            if (i == 4)
            {
                continue;
            }
            else if (gameboard.at(i).at(j) == EMPTY_SPACE
                     && gameboard.at(i+1).at(j) == EMPTY_SPACE)
            {
                return true;
            }
        }
    }
    return false;
}


// Tarkistetaan jääkö jokin ruutu irralleen muista luoden häviötilanteen.
bool didYouLoseLonelySpace(Gameboard& gameboard)
{
    //kulmatilanteet, ovatko lähimmät ruudut ryhjä
    if (gameboard.at(0).at(1) == EMPTY_SPACE &&
            gameboard.at(1).at(0) == EMPTY_SPACE)
    {
        return true;
    }
    else if (gameboard.at(0).at(3) == EMPTY_SPACE &&
            gameboard.at(1).at(4) == EMPTY_SPACE)
    {
        return true;
    }
    else if (gameboard.at(3).at(0) == EMPTY_SPACE &&
             gameboard.at(4).at(1) == EMPTY_SPACE)
    {
        return true;
    }
    else if (gameboard.at(3).at(4) == EMPTY_SPACE &&
             gameboard.at(4).at(3) == EMPTY_SPACE)
    {
        return true;
    }


    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++ j)
        {   // keskellä
            if (i > 0 && i < 4 && j > 0 && j < 4)
            {
                if (gameboard.at(i).at(j-1) == EMPTY_SPACE &&
                        gameboard.at(i).at(j+1) == EMPTY_SPACE &&
                        gameboard.at(i-1).at(j) == EMPTY_SPACE &&
                        gameboard.at(i+1).at(j) == EMPTY_SPACE)
                {
                    return true;
                }
            }
            // ylin rivi
            else if (i == 0 && j > 0 && j < 4)
            {
                if (gameboard.at(i).at(j-1) == EMPTY_SPACE &&
                        gameboard.at(i).at(j+1) == EMPTY_SPACE &&
                        gameboard.at(i+1).at(j) == EMPTY_SPACE)
                {
                    return true;
                }
            }
            // alin rivi
            else if (i == 4 && j > 0 && j < 4)
            {
                if (gameboard.at(i).at(j-1) == EMPTY_SPACE &&
                        gameboard.at(i).at(j+1) == EMPTY_SPACE &&
                        gameboard.at(i-1).at(j) == EMPTY_SPACE)
                {
                    return true;
                }
            }
            // vasen reuna
            else if (i > 0 && i < 4 && j == 0)
            {
                if (gameboard.at(i-1).at(j) == EMPTY_SPACE &&
                    gameboard.at(i+1).at(j) == EMPTY_SPACE &&
                    gameboard.at(i).at(j+1) == EMPTY_SPACE)
                {
                    return true;
                }
            }
            // oikea reuna
            else if (i > 0 && i < 4 && j == 4)
            {
                if (gameboard.at(i-1).at(j) == EMPTY_SPACE &&
                    gameboard.at(i+1).at(j) == EMPTY_SPACE &&
                    gameboard.at(i).at(j-1) == EMPTY_SPACE)
                {
                    return true;
                }
            }
        }  
    }
    return false;
}

// Tarkistaa voittotilanteen alifunktioiden avulla. Mikäli vaaka-
// ja pystyriveissä lukuja 1-5 vain kerran, paluuarvona true
bool didYouWin(Gameboard& gameboard)
{
    if (didYouWinRows(gameboard) &&
        didYouWinColumns(gameboard))
    {
        return true;
    }
    return false;
}

// Tarkistaa vaakariveiltä voittotilanteen.
bool didYouWinRows(Gameboard& gameboard)
{
    std::vector<int> row;
    for(int i = 0; i < 5; ++i)
    {
        row = gameboard.at(i);

        // apumuuttujien avulla pidetään kirjaa numeroiden esiintymisestä riveillä
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

        if (nr_1 > 1 || nr_2 > 1 || nr_3 > 1 || nr_4 > 1 || nr_5 > 1)
        {
            return false;
        }
    }
    return true;
}

// Tarkistaa onko sarakkeissa voittotilanne.
bool didYouWinColumns(Gameboard& gameboard)
{
    // tallennetaan pelilauta väliaikaiseen tietorakenteeseen
    // kääntäen sarakkeet riveiksi
    std::vector<std::vector<int>> gameboard_swapped;

    for (int i = 0; i < 5; ++i)
    {   std::vector<int> column;
        for (int j = 0; j < 5; ++j)
            {
                column.push_back(gameboard.at(j).at(i));
            }
        gameboard_swapped.push_back(column);
    }

    // tarkistetaan onko "uusilla riveillä" voittotilanne
    if (not didYouWinRows(gameboard_swapped))
    {
        return false;
    }
    return true;
}

int main()
{
    Gameboard gameboard = createBoard();
    print(gameboard);

    string x = "";
    string y = "";

    // peli jatkuu kunnes käyttäjältä poistumiskäsky, pelilauta
    // on voittotilanteessa tai häviävä siirto tehdään
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

        if (didYouLose(gameboard))
        {
            cout << "You lost" << endl;
            break;
        }
    }
    return EXIT_SUCCESS;
}
