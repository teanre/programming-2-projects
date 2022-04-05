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

    std::shared_ptr<Point> from_ptr = nullptr;
    std::shared_ptr<Point> to_ptr = nullptr;

    //check if the given points exist. if not, returns false.
    if (all_points_.find(from) != all_points_.end())
    {
        from_ptr = all_points_.at(from);
    }
    if (all_points_.find(to) != all_points_.end())
    {
        to_ptr = all_points_.at(to);
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
        all_routes_.at(route_name).push_back(from_ptr);
        all_routes_.at(route_name).push_back(to_ptr);
    }
    // otherwise connect the routes
    else
    {
      for (uint i = 0; i <= all_routes_.at(route_name).size(); ++i)
      {
          if (all_routes_.at(route_name).at(i)->get_name() == from)
          {
              all_routes_.at(route_name).push_back(to_ptr);
              break;
          }
      }
    }
    return true;
}

void OrienteeringMap::print_map() const
{

   std::vector<std::vector<std::shared_ptr <Point>>> board;

    for(int y = 0; y < height_; ++y)
    {
        std::vector< std::shared_ptr<Point> > line;
        for(int x = 0; x < width_; ++x)
        {
            std::shared_ptr< Point > newPoint = nullptr;
            line.push_back(newPoint);
        }
        board.push_back(line);
    }

    int x_coord = 0;
    int y_coord = 0;

    for (const auto& pts : all_points_)
    {
        x_coord = pts.second->get_x();
        y_coord = pts.second->get_y();
        board.at(y_coord-1).at(x_coord-1) = pts.second;
    }

    std::cout << "  ";
    for(int x = 0; x < width_; ++x)
    {
        if (x < 9)
        {
            std::cout << " " << x+1 << " ";
        }
        else
        {
            std::cout << x+1 << " ";
        }
    }
    std::cout << std::endl;


    for(int y = 0; y < height_; ++y)
    {
        if (y < 9)
        {
            std::cout << " " << (y+1) << " ";
        }
        else
        {
            std::cout << y+1 << " ";
        }
        for(int x = 0; x < width_; ++x)
        {
            if(board.at(y).at(x) != nullptr)
            {
                std::cout << " " << board.at(y).at(x)->get_id() << " ";
            }
            else
            {
                std::cout << " . " ;
            }
        }
        std::cout << std::endl;
    }
}

void OrienteeringMap::print_routes() const
{
    std::cout << "Routes:" << std::endl;
    for (const auto& r : all_routes_)
    {
        std::cout << " - " << r.first << std::endl;
    }
}

void OrienteeringMap::print_points() const
{
    std::cout << "Points: " << std::endl;
    for (const auto& pts : all_points_)
    {
        std::cout << " - " << pts.first << " : " << pts.second->get_id() << std::endl;
    }
}

void OrienteeringMap::print_route(const std::string &name) const
{
    if (all_routes_.find(name) == all_routes_.end())
    {
        std::cout << "Error: Route named " << name << " can't be found" << std::endl;
        return;
    }
    else
    {
        std::cout << all_routes_.at(name).at(0)->get_name() << std::endl;

        for (uint i = 1; i < all_routes_.at(name).size(); ++i)
        {
            std::cout << " -> " << all_routes_.at(name).at(i)->get_name() << std::endl;
        }
    }
}

void OrienteeringMap::route_length(const std::string &name) const
{
    //not implementing this
    std::string length;
    length = name;
}

void OrienteeringMap::greatest_rise(const std::string &point_name) const
{
    //not implementing this
    std::string greatest;
    greatest = point_name;
}
