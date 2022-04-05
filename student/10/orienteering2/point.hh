/* Module: Point.
 * Includes the data and functionality of a single Point.
 *
 */

#ifndef POINT_HH
#define POINT_HH

#include <string>

class OrienteeringMap;

class Point
{
public:
    Point(std::string name, int x, int y, int height,
          char id, OrienteeringMap *map);
    ~Point();

    // returns the name of the route
    std::string get_name();

    // returns the id of the route
    char get_id();

private:
    // name of the route, location of the route with x and y coordinates,
    // height of the route and id of the route
    std::string name_;
    int x_;
    int y_;
    int height_;
    char id_;

    // pointer to the orienteeringmap, where the points are located
    OrienteeringMap *map_;

};

#endif // POINT_HH

