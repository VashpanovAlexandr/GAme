#ifndef VEC
#define VEC

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const double PI = 3.1415926535897931;

class vec {

public:
    double x, y;


    vec() {
        x = y = 0;
    }

    vec(double x, double y) : x{ x }, y{ y }
    { }

    vec operator+(vec const& a) const {
        return { x + a.x, y + a.y };
    }

    vec operator-(vec const& a) const {
        return { x - a.x, y - a.y };
    }

    vec operator-() const {
        return { -x, -y };
    }

    vec operator*(double k) const {
        return { x * k, y * k };
    }

    double operator*(vec const& a) const {
        return x * a.x + y * a.y;
    }

    double len2() const {
        return x * x + y * y;
    }

    double length() const {
        return sqrt(x * x + y * y);
    }

    vec dir() const {
        return vec(x, y) * (1 / length());
    }

    vec left() const {
        return { y, -x };
    }
};

class Line {


private:
    vec p0, n;

public:
    Line() {
        p0 = n = { 0, 0 };
    }

    Line(vec const& p0, vec const& n) : p0{ p0 }, n{ n } {}

    static Line from_points(vec const& A, vec const& B) {
        return Line(A, (B - A).left());
    }

    static Line from_k(double const& a, double const& b, double const& c) {
        vec n = { a, b };
        vec p0 = n * (-c / n.len2());

        return Line(p0, n);
    }

    bool ContainPoint(vec const& v) const {
        if ((p0 - v) * n == 0)
            return true;
        return false;
    }
};

#endif
