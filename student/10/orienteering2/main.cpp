/*Orienteerin map
 *
 * Desc:
 *  This program blabla
 *
 *
 *
 *
 *
 *
 *
 * Program author
 * Name: Terhi Rees
 * Student number: 150250878
 * UserID: rctere
 * E-Mail: terhi.rees@tuni.fi
 */


#include "orienteeringmap.hh"
#include "parser.hh"
#include "cli.hh"
#include <iostream>

int main()
{
    std::shared_ptr<OrienteeringMap> routes(new OrienteeringMap);
    std::cout << "Input> ";
    std::string input;
    getline(std::cin, input);
    if( not read_input_from_file(input, routes) )
    {
        return EXIT_FAILURE;
    }
    Cli cli(routes);
    while( cli.exec_prompt() ){ }
    return EXIT_SUCCESS;
}


