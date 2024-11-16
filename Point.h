#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstdint>

struct Point{
    int x, y;
    Point(int x, int y): x(x), y(y) {}
    Point operator-(Point p){ x -= p.x, y -= p.y; return *this; }
    Point operator+(Point p){ x += p.x, y += p.y; return *this; }
    Point operator-=(Point p){ *this = *this - p; return *this; }
    Point operator+=(Point p){ *this = *this + p; return *this; }
};

std::istream& operator>>(std::istream& is, Point& p){
    is >> p.x >> p.y;
    return is;
}
std::ostream& operator<<(std::ostream& os, Point p){
    os << p.x << ' ' << p.y << "\n";
    return os;
}

