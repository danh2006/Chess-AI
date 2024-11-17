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
    bool  operator==(Point p) { return x == p.x && y == p.y; }
    bool  operator!=(Point p) { return !(*this == p); }
};

std::istream& operator>>(std::istream& is, Point& p){
    is >> p.x >> p.y;
    return is;
}
std::ostream& operator<<(std::ostream& os, Point p){
    os << p.x << ' ' << p.y << "\n";
    return os;
}

auto GetIdx(int x, int y){ 
    return (x << 3) + y; 
}
auto GetIdx (Point p){ return Getidx(p.x, p.y); }

