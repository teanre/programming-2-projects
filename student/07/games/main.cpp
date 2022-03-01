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
#include <cctype>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <map>

// {game{name, points}}
using GAMES = std::map<std::string, std::map<std::string, int>>;

const std::string FILE_OPEN_ERROR_MSG = "Error: File could not be read.";
const std::string INVALID_FORMAT_ERROR_MSG = "Error: Invalid format in file.";
const std::string INVALID_INPUT_ERROR_MSG = "Error: Invalid input.";
const std::string GAME_NOT_FOUND_ERROR_MSG = "Error: Game could not be found.";
const std::string PLAYER_NOT_FOUND_ERROR_MSG = "Error: Player could not be found.";
const std::string ALREADY_EXISTS_ERROR_MSG = "Error: Already exists." ;
const std::string PLAYER_ADDED_MSG = "Player was added.";

std::set<std::string> COMMANDS = {"QUIT", "ALL_GAMES", "GAME", "ALL_PLAYERS",
                                     "PLAYER""", "ADD_GAME", "ADD_PLAYER", "REMOVE"};

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


void save_game_stats(GAMES& gamestatistics, std::string& game,
                std::string& player, std::string pts_as_string)
{
    int points = stoi(pts_as_string);
    //jos peliä ei ole vielä tietokannassa, alustetaan
    if (gamestatistics.find(game) == gamestatistics.end() )
    {
        gamestatistics.insert( {game, {}} );
    }
    //muuten lisätään pelaajan tiedot peliin
    gamestatistics.at(game).insert({player, points});
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

            save_game_stats(gamestatistics, game, player, pts_as_string);
         }
        file_object.close();
    }
    return true;
}



// converts the input given by user to upper characters
void convert_to_upper(std::string& input)
{
    for (uint i = 0; i < input.length(); ++i)
    {
        input.at(i) = toupper(input.at(i));
    }
}

// returns false if quit is given as input
bool ask_for_command(std::vector<std::string>& command_and_parametres )
{
    std::string input = "";
    std::cout << "games> ";
    getline(std::cin, input);

    command_and_parametres = split(input, ' ');
    std::string command = command_and_parametres.at(0);

    convert_to_upper(command);
    return command != "QUIT";
}

void print_all_games(GAMES& gamestatistics)
{
    GAMES::iterator iter;
    iter = gamestatistics.begin();
    std::cout << "All games in alphabetical order:" << std::endl;
    while ( iter != gamestatistics.end() )
    {
        std::cout << iter->first << std::endl;
        ++iter;
    }
}

std::map<int, std::vector<std::string>> save_scores_per_game
        (GAMES& gamestatistics, const std::string& gamename)
{
    // käydään läpi ko. peliä koskeva tulokset, tehään mappi jossa pisteet ja vektori nimistä
    std::map<int, std::vector<std::string>> sort_by_score;
    //tää antaa peliä vastaavat pelaajat ja pojot
    std::map<std::string, int> players_and_scores = gamestatistics.at(gamename);

    for (auto info : players_and_scores)
    {
        //jos pisteitä ei oo vielä mapissa
        if ( sort_by_score.find(info.second) == sort_by_score.end())
        {
            sort_by_score.insert( {info.second, {}});
        }
        // muuten lisätään vaan pelaajat joilla samat pisteet
        sort_by_score.at(info.second).push_back(info.first);
    }
    return sort_by_score;
}

void print_scores_per_game(GAMES& gamestatistics, std::string gamename)
{
    std::map<int, std::vector<std::string>> sort_by_score =
            save_scores_per_game(gamestatistics, gamename);

    std::cout << "Game " << gamename <<  " has these scores and players,"
                " listed in ascending order:" << std::endl;

    for (auto& pts : sort_by_score)
    {
        //ensin tulostetaan pistemäärä
        std::cout << pts.first << " : ";

        std::vector<std::string>::iterator last_player
                                            = sort_by_score.at(pts.first).end();
        std::vector<std::string>::iterator iter
                                            = sort_by_score.at(pts.first).begin();
        for (; iter != sort_by_score.at(pts.first).end(); ++iter)
        {
            std::cout << *iter;
            if ((++iter) != last_player)
            {
                std::cout << ", ";
            }
            else
            {
                std::cout << std::endl;
            }
            --iter;
            }
        }
}

std::set<std::string> save_names_of_all_players(GAMES& gamestatistics)
{
    // save info of players in set, so there is no duplicates
    std::set<std::string> players;

    for (auto& info : gamestatistics)
    {
        std::map<std::string, int> playerdata = info.second;
        for(auto& name : playerdata)
        {
            //lisätään pelaajan nimi settiin
            players.insert(name.first);
        }
    }
    return players;
}

void print_all_players(std::set<std::string>& players)
{
    for (std::set<std::string>::iterator iter = players.begin();
         iter != players.end(); ++iter)
    {
        std::cout << *iter << std::endl;
    }
}

void print_player_stats(GAMES& gamestatistics, std::string& name_of_player)
{
    std::set<std::string> games_played;

    for (auto& info : gamestatistics)
    {
        std::map<std::string, int> playerdata = info.second;
        for(auto& name : playerdata)
        {
            // if name is found in the statistics of the game
            // add the name of the game to set
            if ( playerdata.find(name_of_player) != playerdata.end())
            {
                games_played.insert(info.first);
            }
        }
    }

    std::cout << "Player " << name_of_player <<
                 " plays the following games:" << std::endl;
    for (const std::string &game : games_played)
    {
        std::cout << game << std::endl;
    }

}

void add_game(GAMES& gamestatistics, std::string& gamename)
{
    if (gamestatistics.find(gamename) == gamestatistics.end() )
    {
        gamestatistics.insert( {gamename, {}} );
        std::cout << "Game was added." << std::endl;
    }
    else
    {
        std::cout << ALREADY_EXISTS_ERROR_MSG << std::endl;
    }
}

void add_player(GAMES& gamestatistics, std::string& game,
                std::string& player, std::string pts_as_string)
{
    int pts = stoi(pts_as_string);
    //jos pelaaja on jo listassa, päivitetään
    if (save_names_of_all_players(gamestatistics).find(player) !=
            save_names_of_all_players(gamestatistics).end())
    {
        //std::map<std::string, int> info = {{player, pts}};
        gamestatistics[game][player] =  pts;
    }
    else
    {
        save_game_stats(gamestatistics, game, player, pts_as_string);
    }
}

int main()
{
    GAMES gamestatistics;

    if (not open_file(gamestatistics))
    {
        return EXIT_FAILURE;
    }

    std::vector<std::string> command_and_parametres;

    while (ask_for_command(command_and_parametres))
    {
        std::string command = command_and_parametres.at(0);
        convert_to_upper(command);

        // if incorrect command is given
        if (COMMANDS.find(command) == COMMANDS.end())
        {
            std::cout << INVALID_INPUT_ERROR_MSG << std::endl;
        }
        else if (command == "ALL_GAMES")
        {
            print_all_games(gamestatistics);
        }
        else if (command == "GAME")
        {
            if (gamestatistics.find(command_and_parametres.at(1)) == gamestatistics.end())
            {
                std::cout << GAME_NOT_FOUND_ERROR_MSG << std::endl;
            }
            else if(command_and_parametres.size() <2)
            {
                std::cout << INVALID_INPUT_ERROR_MSG << std::endl;
            }
            else
            {
                print_scores_per_game(gamestatistics, command_and_parametres.at(1));
            }
        }
        else if (command == "ALL_PLAYERS")
        {
            std::set<std::string> players
                    = save_names_of_all_players(gamestatistics);
            print_all_players(players);
        }
        else if (command == "PLAYER")
        {
            std::set<std::string> players
                    = save_names_of_all_players(gamestatistics);
            if(command_and_parametres.size() <2)
            {
                std::cout << INVALID_INPUT_ERROR_MSG << std::endl;
            }
            else if (players.find(command_and_parametres.at(1))
                     == players.end())
            {
                std::cout << PLAYER_NOT_FOUND_ERROR_MSG << std::endl;
            }
            else
            {
                print_player_stats(gamestatistics, command_and_parametres.at(1));
            }
        }
        else if (command == "ADD_GAME")
        {
            if (command_and_parametres.size() <2)
            {
                std::cout << INVALID_INPUT_ERROR_MSG << std::endl;
            }
            else
            {
                add_game(gamestatistics, command_and_parametres.at(1));
            }
        }
        else if (command == "ADD_PLAYER")
        {
            if (command_and_parametres.size() <4)
            {
                std::cout << INVALID_INPUT_ERROR_MSG << std::endl;
            }
            else if (gamestatistics.find(command_and_parametres.at(1))
                     == gamestatistics.end())
            {
                std::cout << GAME_NOT_FOUND_ERROR_MSG << std::endl;
            }
            else
            {
                add_player(gamestatistics, command_and_parametres.at(1),
                                command_and_parametres.at(2),
                                command_and_parametres.at(3));
                std::cout << PLAYER_ADDED_MSG << std::endl;
            }
        }
    }
    return EXIT_SUCCESS;
}
