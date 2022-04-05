/*Orienteering map
 *
 * Desc:
 *  This program simulates an orienteering map. It stores data of different
 *  orienteering routes and information of the control points on the route.
 *
 *  First the programme reads the data including all information on the points
 *  and routes from a file, and stores the data in datastructure in
 *  class orienteeringmap.
 *
 *  Commands:
 *  QUIT - Exits the programme
 *  MAP - Prints the map, showing the location of a point as their marker
 *       scharacter. If a point is empty, shows a dot (.).
 *  ROUTES - Prints the routes in alphabetical order.
 *  ROUTE <Route> - Prints the points belonging to the given route.
 *  POINTS - Prints the all the stored control point names and their markers.
 *  LENGTH <route> - not implemented.
 *  RISE <point> - not implemented. *
 *
 *
 * Program author
 * Name: Terhi Rees
 * Student number: 150250878
 * UserID: rctere
 * E-Mail: terhi.rees@tuni.fi
 *
 * Notes:
 * The programme was implemented unfortunately in quite a hurry, and some of the
 * functions are too long - for example print map could have been done more
 * efficienly.
 *
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


