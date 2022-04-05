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
    //muuttaa ko. attribuuttien arvot
    width_ = width;
    height_ = height;
}

void OrienteeringMap::add_point(std::string name,
                                int x,
                                int y,
                                int height,
                                char marker)
{
    //jos koordinaatit osuvat kartalle, voidaan lisätä rasti kartalle
    if (x >=0 && x <= width_ && y >= 0 && y <= height_)
    {
        //jos rastia ei ole vielä listalla
        if (all_points_.find(name) == all_points_.end())
        {
           std::shared_ptr<Point> new_point( std::make_shared<Point>(name, x, y, height, marker, this));
           all_points_.insert({name, new_point});
        }
     }
        //ja onko oliota jo olemassa eli onko pointnameslistalla

        //lisätään allpointsiin

   /* std::cout << all_points_.size() << std::endl;

    std::map<std::string, std::shared_ptr<Point>>::iterator iter;
    iter = all_points_.begin();
    while (iter != all_points_.end())
    {
        std::cout << iter->first << std::endl;
        ++iter;
    }*/

}

/*void OrienteeringMap::get_route(std::map<std::string, std::vector<Point *> > route_name)
{

}*/

bool OrienteeringMap::connect_route(std::string from,
                                    std::string to,
                                    std::string route_name)
{
    //tehdään temppipointterit
    std::shared_ptr<Point> tempfrom = nullptr;
    std::shared_ptr<Point> tempto = nullptr;

    //ensin tarkistetaan onko rastit olemassa. mikäli ei, palauttaa false.
    if (all_points_.find(from) != all_points_.end())
    {
        tempfrom = all_points_.at(from);
    }
    if (all_points_.find(to) != all_points_.end())
    {
        tempto = all_points_.at(to);
    }
    else
    {
        return false;
    }

    std::vector<std::shared_ptr<Point>> tempvec;

    // jos reittiä ei ole vielä tallennettuna, ensin alustetaan reitti
    // ja sitten lisätään rastit vektoriin
    if (all_routes_.find(route_name) == all_routes_.end())
    {
        all_routes_.insert({route_name, tempvec});
        all_routes_.at(route_name).push_back(tempfrom);
        all_routes_.at(route_name).push_back(tempto);
        //std::cout << "koko on:" << all_routes_.at(route_name) << std::endl;
    }
    //muuten pitäisi olla niin että vain to päivitetään oikeaan paikkaan
    else
    {
      for (uint i = 0; i <= all_routes_.at(route_name).size(); ++i)
      {
          if (all_routes_.at(route_name).at(i)->get_name() == from)
          {
              all_routes_.at(route_name).push_back(tempto);
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
}

void OrienteeringMap::print_route(const std::string &name) const
{
    //pakollinen
    std::cout << name << std::endl;
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
