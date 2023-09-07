#include <iostream>
#include <iomanip>

class Point{
public:
    Point(int x_, int y_) : x(x_), y(y_) {} 
    int x;
    int y;
};

int find_paths(const Point& point)
{
    if(point.x == 0 && point.y == 0)
        return 1;

    int path_count = 0;
    if(point.x != 0)
        path_count += find_paths(Point(point.x - 1, point.y));
    if(point.y != 0)
        path_count += find_paths(Point(point.x,point.y-1));

    //All finished
    return path_count;
}

int main(){
    Point loc(2, 2);
    int path_count = find_paths(loc);
    std::cout << path_count << '\n';    
}



