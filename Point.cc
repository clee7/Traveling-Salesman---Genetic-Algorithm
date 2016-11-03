#include "Point.hh"
#include <cmath>


// Default constructor:  initializes the point to (0, 0).
Point::Point() {
    x_coord = 0;
    y_coord = 0;
    z_coord = 0;
}

// Initializes the point to (x, y).
Point::Point(double x, double y, double z) {
    x_coord = x;
    y_coord = y;
    z_coord = z;
}

// Destructor - Point allocates no dynamic resources.
Point::~Point() {
  // no-op
}

// Mutators:

void Point::setX(double val) {
    x_coord = val;
}

void Point::setY(double val) {
    y_coord = val;
}

void Point::setZ(double val) {
    z_coord = val;
}

// Accessors:
 
double Point::getX() const{
    return x_coord;
}

double Point::getY() const{
    return y_coord;
}

double Point::getZ() const{
    return z_coord;
}

// member function
double Point::distanceTo(const Point &p) const{
    // given a point, the distance between two points in 3D is given by the
    // equation: d = sqrt((x1 - x2)^2 + (y1 - y2)^2 + (z1 - z2)^2).
    double d;
    d = sqrt(((x_coord - p.getX()) * (x_coord - p.getX())) + 
        ((y_coord - p.getY()) * (y_coord - p.getY())) +  
        ((z_coord - p.getZ()) * (z_coord - p.getZ())));
    return d;
}
