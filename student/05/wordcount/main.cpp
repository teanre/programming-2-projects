#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <set>

using namespace std;

//using Wordcount = map<string, vector<int>>;
using Wordcount = map<string, set<int>>;


std::vector <std::string> split(std::string const& text,
                                bool pass_or_not = false)
{
    std::vector<std::string> parts;

    std::string::size_type start = 0;
    std::string::size_type end = 0;

    string splitting_char = " ";

    while (start <= text.size())
    {
        std::string part = "";

        end = text.find(splitting_char, start);

        if (end == std::string::npos)
        {
            end = text.size();
        }

        part = text.substr(start, (end - start));

        if (part != "" || !pass_or_not)
        {
            parts.push_back(part);
        }

        start = end+1;
    }
    return parts;
}

void add_word(Wordcount& wrds, const string& word, const int& pagenr)
{
    Wordcount::iterator iter = wrds.find(word);

    // If the word is not as a key in the map.
    if ( iter == wrds.end() )
    {
        wrds.insert( {word, { pagenr }} );

    // Otherwise we'll just add a new page number to the set
    }
    else
    {
        wrds.at(word).insert(pagenr);
    }
}

void print_pagenr_set(const set<int>& pagenumbers)
{
    cout << pagenumbers.size() << ": ";

    set<int>::const_iterator iter;
    iter = pagenumbers.begin();
    set<int>::const_iterator last_nr = pagenumbers.end();

    for (iter; iter != pagenumbers.end(); ++iter)
    {
        cout << *iter;
        if ((++iter) != last_nr)
        {
            cout << ", ";
        }
        --iter;
    }
}

void print_info(Wordcount& wordinfo)
{
    //tulostaa: sana , kuinka monella rivillä esiintyy eli sitä vastaavan vektorin pituus
    // ja ite rivit millä sijaitsee eli sitä vastaavan vektorin sisältö

    for ( const auto& pagenrdata : wordinfo )
    {
        cout << pagenrdata.first << " ";

        print_pagenr_set(pagenrdata.second);
        cout << endl;
    }
}


int main()
{
    // sanat riviltä aina tietorakenteeseen, ja merkintä millä rivillä esiintyy
    // jos on samalla rivillä monta kertaa, ei merkitystä

    Wordcount worderssons;


    string input_file = "";
    cout << "Input file: ";
    getline(cin, input_file);


    ifstream inputf(input_file);

    if (not inputf)
    {
       cout << "Error! The file " << input_file << " cannot be opened." << endl;
       return EXIT_FAILURE;
    }
     else
    {
        string row;
        int row_number = 1;

        while ( getline (inputf, row))
        {
            //splitataan rivilta " ", laitetaan mappiin sana, settiin row_number
            std::vector<string> words = split(row);

            for (string& word : words)
            {
               add_word(worderssons, word, row_number);
            }
            row_number += 1;
        }
        inputf.close();
     }


    print_info(worderssons);

    return EXIT_SUCCESS;
}



