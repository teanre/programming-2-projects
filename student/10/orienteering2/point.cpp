#include "point.hh"
#include "orienteeringmap.hh"
#include <string>

Point::Point(std::string name, int x, int y, int height, char id, OrienteeringMap *map):
    name_(name), x_(x), y_(y), height_(height), id_(id), map_(map)

{

}

/*void Point::add(std::string name, int x, int y, int height, char id, OrienteeringMap *map)
{
    Point_data *new_point = new Point_data({name, x, y, height, id});

    map->
    new_point->x = x;
    new_point->y = y;
    new_point->height = height;
    new_point->id = id;

}*/



Point::~Point()
{

}

std::string Point::get_name()
{
    return name_;
}
