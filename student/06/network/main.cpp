#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";

using Database = std::map<std::string, std::vector <std::string>>;

std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void save_data(const std::string id1, const std::string id2, Database& database)
{
    if (database.find(id1) == database.end())
    {
        database.insert( {id1, {}});
    }
    database.at(id1).push_back(id2);
}

void print(const std::string id, Database const& database, std::string indent = "")
{
    //jos hlöä ei ole tallennettuna, tai henkilöllä ei ole rekrytoituja
    if (database.find(id) == database.end()
            || database.at(id).empty())
    {
        std::cout <<  indent << id << std::endl;
    }

    //muuten pitää tulostaa henkilö aliverkostoineen
    else
    {
        std::cout << indent << id << std::endl;
        std::vector<std::string>::const_iterator iter = database.at(id).begin();
        for (; iter!=database.at(id).end(); ++iter)
        {
            print(*iter, database, indent + "..");
        }
    }
}

int count(std::string id, Database const& database)
{
    //triviaali, ei rekryttyjä eli ei ole mapissa avaimena
    if (database.find(id) == database.end())
    {
        return 0;
    }
    else
    {
       // lasketaan kutakin nimeä koskevan vektorin pituus
        std::vector<std::string>::const_iterator iter = database.at(id).begin();
        int size = database.at(id).size();
        for(; iter != database.at(id).end(); ++iter)
        {
            size += count(*iter, database);
        }
        return size;
    }
}

int depth(std::string id, const Database& database)
{
    int max_depth = 0;

    if (database.find(id) != database.end())
    {
        for (std::string key : database.at(id))
        {
            if(depth(key, database) > max_depth)
            {
                max_depth = depth(key, database);
            }
        }
    }
    return max_depth +1;
}

int main()
{
    // TODO: Implement the datastructure here
    Database database = {};

    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            save_data(id1, id2, database);

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            print(id, database);

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout << count(id, database) << std::endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout << depth(id, database) << std::endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
