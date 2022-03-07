/*  COMP.CS.110 Project 2: GAME STATISTICS
 * ===============================
 *
 * Acts as a game statistics with commands:
 * ALL_GAMES - Prints all known game names
 * GAME <game name> - Prints all players playing the given game
 * ALL_PLAYERS - Prints all known player names
 * PLAYER <player name> - Prints all games the given player plays
 * ADD_GAME <game name> - Adds a new game
 * ADD_PLAYER <game name> <player name> <score> - Adds a new player with the
 * given score for the given game, or updates the player's score if the player
 * already playes the game
 * REMOVE_PLAYER <player name> - Removes the player from all games
 * QUIT - Exits the game
 *
 * The data file's lines should be in format game_name;player_name;score
 * Otherwise the program execution terminates instantly.
 *
 * Program author
 * Name: Terhi Rees
 * Student number: 150250878
 * UserID: rctere
 * E-Mail: terhi.rees@tuni.fi
 *
 * */

#include <iostream>
#include <cctype>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <map>

// Data structure where game statistics are saved to {game, {player, points}}
using GAMES = std::map<std::string, std::map<std::string, int>>;

const std::string FILE_OPEN_ERROR_MSG = "Error: File could not be read.",
                  INVALID_FORMAT_ERROR_MSG = "Error: Invalid format in file.",
                  INVALID_INPUT_ERROR_MSG = "Error: Invalid input.",
                  GAME_NOT_FOUND_ERROR_MSG = "Error: Game could not be found.",
                  PLAYER_NOT_FOUND_ERROR_MSG = "Error: Player could not be found.",
                  ALREADY_EXISTS_ERROR_MSG = "Error: Already exists.",
                  PLAYER_ADDED_MSG = "Player was added.",
                  PLAYER_REMOVED_MSG = "Player was removed from all games.";

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

// Checks if the line of data from file is acceptable:
// line has the three strings required and game name or player name is not empty
bool line_is_ok(std::vector<std::string> const& data)
{
    return data.size() == 3
        && !data.at(0).empty()
        && !data.at(1).empty();
}

// Adds the statistics to data structure.
void save_game_stats(GAMES& gamestatistics, std::string& game,
                std::string& player, std::string pts_as_string)
{
    int points = stoi(pts_as_string);

    // checks if game is in the data structure yet, adds if not
    if (gamestatistics.find(game) == gamestatistics.end() )
    {
        gamestatistics.insert( {game, {}} );
    }
    // add the statistics in the data structure
    gamestatistics.at(game).insert({player, points});
}

// Opens the file, saves the data to data structure if possible.
// Returns true if succeeds.
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

// Converts the input given by user to upper characters
void convert_to_upper(std::string& input)
{
    for (uint i = 0; i < input.length(); ++i)
    {
        input.at(i) = toupper(input.at(i));
    }
}

// Asks for input from user. Returns false if quit is given as input.
bool ask_for_input(std::vector<std::string>& command_and_parametres)
{
    std::string input = "";
    std::cout << "games> ";
    getline(std::cin, input);

    command_and_parametres = split(input, ' ');
    std::string command = command_and_parametres.at(0);

    convert_to_upper(command);

    // if incorrect command is given, notify user
    if (COMMANDS.find(command) == COMMANDS.end())
    {
        std::cout << INVALID_INPUT_ERROR_MSG << std::endl;
    }
    return command != "QUIT";
}

// Prints all games in the statistics in alphabetical order.
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

// Organizes the stats by given game in form points, players
std::map<int, std::vector<std::string>> save_scores_per_game
        (GAMES& gamestatistics, const std::string& gamename)
{
    //tää antaa peliä vastaavat pelaajat ja pojot
    std::map<std::string, int> players_and_scores = gamestatistics.at(gamename);

    // data structure to reorganize the statistics
    std::map<int, std::vector<std::string>> sort_by_score;

    for (auto info : players_and_scores)
    {
        // check if the points are in sort_by_score yet
        if ( sort_by_score.find(info.second) == sort_by_score.end())
        {
            sort_by_score.insert( {info.second, {}});
        }
        // add the players who
        sort_by_score.at(info.second).push_back(info.first);
    }
    return sort_by_score;
}

// Prints the score situation from the given game.
void print_scores_per_game(GAMES& gamestatistics, std::string gamename)
{
    std::map<int, std::vector<std::string>> sort_by_score =
            save_scores_per_game(gamestatistics, gamename);

    std::cout << "Game " << gamename <<  " has these scores and players,"
                " listed in ascending order:" << std::endl;

    for (auto& stats : sort_by_score)
    {
        // first print the amount of the points
        std::cout << stats.first << " : ";

        std::vector<std::string>::iterator last_player
                                         = sort_by_score.at(stats.first).end();
        std::vector<std::string>::iterator iter
                                         = sort_by_score.at(stats.first).begin();

        // prints the players that have the same points
        for (; iter != sort_by_score.at(stats.first).end(); ++iter)
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

// Checks if the given game is in the data structure.
bool search_game(GAMES& gamestatistics, std::string gamename)
{
    if (gamestatistics.find(gamename) == gamestatistics.end())
    {
        std::cout << GAME_NOT_FOUND_ERROR_MSG << std::endl;
        return false;
    }
    return true;
}

// Stores the names of all current players in the data structure.
std::set<std::string> save_names_of_all_players(GAMES& gamestatistics)
{
    // save names of players in set, so there is no duplicates
    std::set<std::string> players;

    for (auto& info : gamestatistics)
    {
        std::map<std::string, int> playerdata = info.second;
        for(auto& name : playerdata)
        {
            players.insert(name.first);
        }
    }
    return players;
}

// Prints all current players in alphabetical order.
void print_all_players(GAMES& gamestatistics)
{
    std::set<std::string> players = save_names_of_all_players(gamestatistics);

    std::cout << "All players in alphabetical order:" << std::endl;

    for (std::set<std::string>::iterator iter = players.begin();
         iter != players.end(); ++iter)
    {
        std::cout << *iter << std::endl;
    }
}

// Checks if player is in the data structure (i.e. plays any of the games).
bool search_player(GAMES& gamestatistics, std::string name)
{
    std::set<std::string> players = save_names_of_all_players(gamestatistics);
    if (players.find(name) == players.end())
    {
        std::cout << PLAYER_NOT_FOUND_ERROR_MSG << std::endl;
        return false;
    }
    return true;
}

// Saves in a set all the games the given player plays.
std::set<std::string> save_player_stats(GAMES& gamestatistics,
                                        std::string& name_of_player)
{
    // go through all of the statistics, if player is found
    // add the name of the game to games_played set
    std::set<std::string> games_played;
    for (auto& info : gamestatistics)
    {
        std::map<std::string, int> playerdata = info.second;
        for(auto& data : playerdata)
        {
            if ( playerdata.find(name_of_player) != playerdata.end())
            {
                games_played.insert(info.first);
            }
        }
    }
    return games_played;
}

// Prints the games the given player plays in alphabetical order.
void print_player_stats(GAMES& gamestatistics, std::string& name_of_player)
{
    std::set<std::string> games_played =
            save_player_stats(gamestatistics, name_of_player);

    std::cout << "Player " << name_of_player <<
                 " playes the following games:" << std::endl;
    for (const std::string& game : games_played)
    {
        std::cout << game << std::endl;
    }
}

// Adds the given game to the data structure.
void add_game(GAMES& gamestatistics, std::string& gamename)
{
    if (gamestatistics.find(gamename) == gamestatistics.end() )
    {
        gamestatistics.insert( {gamename, {}} );
        std::cout << "Game was added." << std::endl;
    }

    // if the game is already in the database, notify user
    else
    {
        std::cout << ALREADY_EXISTS_ERROR_MSG << std::endl;
    }
}

// Adds the given player and points for the given game in the data structure.
void add_player(GAMES& gamestatistics, std::string& game,
                std::string& player, std::string pts_as_string)
{
    int pts = stoi(pts_as_string);

    // if player is already in database, only update the points
    if (save_names_of_all_players(gamestatistics).find(player) !=
            save_names_of_all_players(gamestatistics).end())
    {
        gamestatistics[game][player] =  pts;
    }
    else
    {
        save_game_stats(gamestatistics, game, player, pts_as_string);
    }
    std::cout << PLAYER_ADDED_MSG << std::endl;
}

// Removes the given player from the data structure (i.e. from all games).
void remove_player(GAMES& gamestatistics, std::string& player)
{
    GAMES::iterator iter;
    iter = gamestatistics.begin();

    while (iter != gamestatistics.end())
    {
        std::map<std::string, int>& player_and_points = iter->second;
        std::map<std::string, int>::iterator it;
        it = player_and_points.begin();
        while (it != player_and_points.end())
        {
            if (it->first == player)
            {
                it = player_and_points.erase(it);
            }
            else
            {
                ++it;
            }
        }
        ++iter;
    }
    std::cout << PLAYER_REMOVED_MSG << std::endl;
}

// Checks if user has given enough parametres to execute the command.
bool is_enough_parametres(const std::string& command,
                          const std::vector<std::string>& commands)
{
    if (commands.size() >= 2
       && (command == "GAME" || command == "PLAYER"
          || command == "ADD_GAME" || command == "REMOVE"))
    {
        return true;
    }
    else if (command == "ADD_PLAYER" && commands.size() >= 4)
    {
        return true;
    }
    else
    {
        std::cout << INVALID_INPUT_ERROR_MSG << std::endl;
        return false;
    }
}


int main()
{
    GAMES gamestatistics;

    if (not open_file(gamestatistics))
    {
        return EXIT_FAILURE;
    }

    //first key will be the command, rest the parametres for commands
    std::vector<std::string> command_and_parametres;

    while (ask_for_input(command_and_parametres))
    {
        std::string command = command_and_parametres.at(0);
        convert_to_upper(command);

        if (command == "ALL_GAMES")
        {
            print_all_games(gamestatistics);
        }
        else if (command == "GAME"
                 && is_enough_parametres(command, command_and_parametres)
                 && search_game(gamestatistics, command_and_parametres.at(1)))
        {        
            print_scores_per_game(gamestatistics, command_and_parametres.at(1));
        }
        else if (command == "ALL_PLAYERS")
        {
            print_all_players(gamestatistics);
        }
        else if (command == "PLAYER"
                 && is_enough_parametres(command, command_and_parametres)
                 && search_player(gamestatistics, command_and_parametres.at(1)))
        {
            print_player_stats(gamestatistics, command_and_parametres.at(1));
        }
        else if (command == "ADD_GAME"
                 && is_enough_parametres(command, command_and_parametres))
        {
            add_game(gamestatistics, command_and_parametres.at(1));
        }
        else if (command == "ADD_PLAYER"
                 && is_enough_parametres(command, command_and_parametres)
                 && search_game(gamestatistics, command_and_parametres.at(1)))
        {
            add_player(gamestatistics, command_and_parametres.at(1),
                            command_and_parametres.at(2),
                            command_and_parametres.at(3));
        }
        else if (command == "REMOVE"
                 && is_enough_parametres(command, command_and_parametres)
                 && search_player(gamestatistics, command_and_parametres.at(1)))
        {
            remove_player(gamestatistics, command_and_parametres.at(1));
        }
    }
    return EXIT_SUCCESS;
}
