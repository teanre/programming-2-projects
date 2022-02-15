#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

std::vector <std::string> split(std::string const& text,
                                bool pass_or_not = false)
{
    std::vector<std::string> parts;

    std::string::size_type start = 0;
    std::string::size_type end = 0;

    string splitting_char = ":";

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


int main()
{

    string filename = "";
    cout << "Input file: ";
    getline(cin, filename);

    ifstream readfile(filename);
    map<string, uint> scores;
    if (not readfile)
    {
        cout << "Error! The file " << filename << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else
    {
        cout << "Final scores:" << endl;

        //luetaan rivi, splitataan se - vectorin nolla & 1 mappiin - jos nimi on jo mapis ni pitesst lisätään vaa
        string row;
        while ( getline (readfile, row) )
        {
            std::vector<string> namescore = split(row);
            string name = namescore.at(0);
            uint score = stoi(namescore.at(1));
            uint score_altogether = 0;


            //nimi on jo mapissa
            if (scores.find(name) != scores.end() )
            {
                uint old_score = scores.at(name);
                score_altogether = old_score + score;

                //päivitetään uusi pistemäärä
                scores[name] = score_altogether;
            }
            //muuten lisätään uusi mappiin
            else
            {
                scores.insert( {name, score});
            }

        }
        readfile.close();
    }

    map<string, uint>::iterator iter;
    iter = scores.begin();
    while( iter != scores.end() )
    {
        cout << iter->first << ": " << iter->second << endl;
        ++iter;
    }



    return EXIT_SUCCESS;
}
