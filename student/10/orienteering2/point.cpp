#include "point.hh"
#include "orienteeringmap.hh"
#include <string>

Point::Point(std::string name, int x, int y, int height, char id, OrienteeringMap *map):
    name_(name), x_(x), y_(y), height_(height), id_(id), map_(map)

{

}

Point::~Point()
{

}

std::string Point::get_name()
{
    return name_;
}

char Point::get_id()
{
    return id_;
}

int Point::get_x()
{
    return x_;
}

int Point::get_y()
{
    return y_;
}
