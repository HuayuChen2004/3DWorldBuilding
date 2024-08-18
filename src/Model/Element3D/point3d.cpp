// [file name] : point3d.cpp
// [function] : implement the Point3D class
// [author] : Huayu Chen
// [date] : 2024/8/4

// [edit history] :
// -----------------------------------------------------------
// date: 2024/8/4
// author: Huayu Chen
// edit: add implementation of the Point3D class
// reason: to support storing the 3D point
// -----------------------------------------------------------


#include "point3d.hpp"
#include <vector>
#include <stdexcept>
#include <string>
#include <exception>

using namespace std;

// -----------------------------------------------------------
// [name] : Point3D
// [function] : constructor of the Point3D class
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Point3D::Point3D() : Point(), m_rX(0), m_rY(0), m_rZ(0) {}

// -----------------------------------------------------------
// [name] : Point3D
// [function] : constructor of the Point3D class
// [input] : a vector of doubles
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Point3D::Point3D(const vector<double>& coords) : Point(coords) {
    // Check if the vector has 3 elements
    if (coords.size() != 3) {
        throw invalid_argument("Point3D must have 3 coordinates");
    }
    m_rX = coords[0];
    m_rY = coords[1];
    m_rZ = coords[2];
}

// -----------------------------------------------------------
// [name] : Point3D
// [function] : constructor of the Point3D class
// [input] : three doubles
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Point3D::Point3D(double x, double y, double z) : Point(vector<double>{x, y, z}),
                                    m_rX(x), m_rY(y), m_rZ(z) {}

// -----------------------------------------------------------
// [name] : Point3D
// [function] : copy constructor of the Point3D class
// [input] : a Point3D object
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Point3D::Point3D(const Point3D& point) : Point(point),      
                    m_rX(point.m_rX), m_rY(point.m_rY), m_rZ(point.m_rZ) {}

// -----------------------------------------------------------
// [name] : ~Point3D
// [function] : destructor of the Point3D class
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Point3D::~Point3D() {}

// -----------------------------------------------------------
// [name] : SetX
// [function] : set the x coordinate of the point
// [input] : a double
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
void Point3D::SetX(double x) {
    m_rX = x;
    try {
        // call the Set function of the base class
        Point::Set(static_cast<Point>(*this));
    }
    catch (exception& e) {
        throw e;
    }
}

// -----------------------------------------------------------
// [name] : SetY
// [function] : set the y coordinate of the point
// [input] : a double
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
void Point3D::SetY(double y) {
    m_rY = y;
    try {
        // call the Set function of the base class
        Point::Set(static_cast<Point>(*this));
    }
    catch (exception& e) {
        throw e;
    }
}

// -----------------------------------------------------------
// [name] : SetZ
// [function] : set the z coordinate of the point
// [input] : a double
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
void Point3D::SetZ(double z) {
    m_rZ = z;
    try {
        // call the Set function of the base class
        Point::Set(static_cast<Point>(*this));
    }
    catch (exception& e) {
        throw e;
    }
}

// -----------------------------------------------------------
// [name] : operator=
// [function] : assignment operator of the Point3D class
// [input] : a Point3D object
// [output] : a reference to the Point3D object
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Point3D& Point3D::operator=(const Point3D& point) {
    m_rX = point.m_rX;
    m_rY = point.m_rY;
    m_rZ = point.m_rZ;
    // call the Set function of the base class
    try {
        Point::Set(static_cast<Point>(*this));
    }
    catch (exception& e) {
        throw e;
    }
    return *this;
}





