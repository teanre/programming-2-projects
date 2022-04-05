#include "orienteeringmap.hh"
#include "point.hh"
#include <memory>
#include <algorithm>
#include <iostream>

OrienteeringMap::OrienteeringMap():
    height_(0), width_(0), all_points_(), all_routes_()
{

}

OrienteeringMap::~OrienteeringMap()
{

}

void OrienteeringMap::set_map_size(int width, int height)
{
    width_ = width;
    height_ = height;
}

void OrienteeringMap::add_point(std::string name,
                                int x,
                                int y,
                                int height,
                                char marker)
{
    // adds new point, if point's coordinates are valid (fit the on the board)
    // and the point doesn't already exist
    if (x >=0 && x <= width_ && y >= 0 && y <= height_
            && all_points_.find(name) == all_points_.end())
    {
        std::shared_ptr<Point> new_point
                ( std::make_shared<Point>(name, x, y, height, marker, this));
        all_points_.insert({name, new_point});
    }
}

bool OrienteeringMap::connect_route(std::string from,
                                    std::string to,
                                    std::string route_name)
{

    std::shared_ptr<Point> fromptr = nullptr;
    std::shared_ptr<Point> toptr = nullptr;

    //check if the given points exist. if not, returns false.
    if (all_points_.find(from) != all_points_.end())
    {
        fromptr = all_points_.at(from);
    }
    if (all_points_.find(to) != all_points_.end())
    {
        toptr = all_points_.at(to);
    }
    else
    {
        return false;
    }

    std::vector<std::shared_ptr<Point>> vec;

    // if the route doesn't exist yet, add to route datastructure
    if (all_routes_.find(route_name) == all_routes_.end())
    {
        all_routes_.insert({route_name, vec});
        all_routes_.at(route_name).push_back(fromptr);
        all_routes_.at(route_name).push_back(toptr);
    }
    // otherwise connect the routes
    else
    {
      for (uint i = 0; i <= all_routes_.at(route_name).size(); ++i)
      {
          if (all_routes_.at(route_name).at(i)->get_name() == from)
          {
              all_routes_.at(route_name).push_back(toptr);
              break;
          }
      }
    }
    return true;
}

void OrienteeringMap::print_map() const
{
    //pakollinen
    //for loopilla widht ja heigfth attribuuttia hyödyntäen tulostaa koordinaatit
    // piste jos tyhjä, muuten sisältämä pointin id_
}

void OrienteeringMap::print_routes() const
{
    //pakollinen
    std::cout << "Routes:" << std::endl;
    for (const auto& p : all_routes_)
    {
        std::cout << " - " << p.first << std::endl;
    }
}

void OrienteeringMap::print_points() const
{
    //pakollinen
    std::cout << "Points: " << std::endl;
    //for
}

void OrienteeringMap::print_route(const std::string &name) const
{
    //pakollinen
    for (const auto& r : all_routes_.at(name))
    {
        std::cout << " -> " << r->get_name() << std::endl;
    }
}

void OrienteeringMap::route_length(const std::string &name) const
{

}

void OrienteeringMap::greatest_rise(const std::string &point_name) const
{

}
