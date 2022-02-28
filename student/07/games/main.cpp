/*  COMP.CS.110 Project 2: GAME STATISTICS
 * ===============================
 *
 *  Acts as a game statistics with n commands:
 * ALL_GAMES - Prints all known game names
 * GAME <game name> - Prints all players playing the given game
 * ALL_PLAYERS - Prints all known player names
 * PLAYER <player name> - Prints all games the given player plays
 * ADD_GAME <game name> - Adds a new game
 * ADD_PLAYER <game name> <player name> <score> - Adds a new player with the
 * given score for the given game, or updates the player's score if the player
 * already playes the game
 * REMOVE_PLAYER <player name> - Removes the player from all games
 *
 *  The data file's lines should be in format game_name;player_name;score
 * Otherwise the program execution terminates instantly (but still gracefully).
 *
 * */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

// {game{name, points}}
using GAMES = std::map<std::string, std::map<std::string, int>>;

const std::string FILE_OPEN_ERROR_MSG = "Error: File could not be read.";
const std::string INVALID_FORMAT_ERROR_MSG = "Error: Invalid format in file";

// Casual split func, if delim char is between "'s, ignores it.
std::vector<std::string> split( const std::string& str, char delim = ';' )
{
    std::vector<std::string> result = {""};
    bool inside_quatation = false;
    for ( auto current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quatation = not inside_quatation;
        }
        else if ( current_char == delim and not inside_quatation )
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}

// jos tiedosto saadaan auki, mutta ei ole oikeassa muodossa
// luetaan rivi riviltä, jos splitvektorin pituus yli kolme, errori, tai
// jos peli ja tai nimi kohta tyhjä (split-vektorin 0 ja 1 indeksi)
bool line_is_ok(std::vector<std::string> const& data)
{
    return data.size() == 3
        && !data.at(0).empty()
        && !data.at(1).empty();
}

// Opens the file and saves the data
bool open_file(GAMES& gamestatistics)
{
    std::string filename = "";

    std::cout << "Give a name for input file: ";
    getline(std::cin, filename);

    std::ifstream file_object(filename);

    if ( not file_object)
    {
        std::cout << FILE_OPEN_ERROR_MSG << std::endl;
        return false;
    }

    else
    {
        std::string line;
        std::vector<std::string> data;

        while( getline (file_object, line) )
        {
            data = split(line);

            if (!line_is_ok(data))
            {
                std::cout << INVALID_FORMAT_ERROR_MSG << std::endl;
                return false;
            }

            std::string game = data.at(0),
                        player = data.at(1),
                        pts_as_string = data.at(2);
            int points = stoi(pts_as_string);

            //jos peliä ei ole vielä tilastossa, lisätään
            if (gamestatistics.find(game) == gamestatistics.end() )
            {
                gamestatistics.insert( {game, {}} );
            }
            //muuten lisätään pelaajan tiedot peliin
            else
            {
                gamestatistics.at(game).insert({player, points});
            }

         }
    }
    return true;
}

/*void read_file(GAMES& gamestatistics)
{

    std::string line;

    std::vector<std::string> data;

    while( getline (file_object, line) )
    {
        data = split(line);
        if (data.size() > 3
         || data.at(0) == EMPTY_INPUT
         || data.at(1) == EMPTY_INPUT)
        {
            std::cout << INVALID_FORMAT_ERROR_MSG << std::endl;
            return false;
        }
        else
        {

        }
}*/



std::string ask_for_command()
{
    std::string command = "";
    std::cout << "games>";
    getline(std::cin, command);
    return command;
}


int main()
{
    GAMES gamestatistics;

    if (not open_file(gamestatistics))
    {
        return EXIT_FAILURE;
    }

    if (ask_for_command() == "QUIT")
    {
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}
