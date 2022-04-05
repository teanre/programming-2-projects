#ifndef POINT_HH
#define POINT_HH

#include <string>

// sisältää paikan nimen, sijainnin ja mihin reitteihin kuuluu

class OrienteeringMap;

/*struct Point_data {
    std::string name;
    int x;
    int y;
    int height;
    char id;
};*/

class Point
{
public:
    Point(std::string name, int x, int y, int height, char id, OrienteeringMap *map);
    ~Point();

    //void add(std::string name, int x, int y, int height, char id, OrienteeringMap *map);

    std::string get_name();
    char get_id();

private:
    std::string name_;
    int x_;
    int y_;
    int height_;
    char id_;

    OrienteeringMap *map_;

};

#endif // POINT_HH

