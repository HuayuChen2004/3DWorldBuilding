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

Point3D::Point3D(const vector<double>& coords) : Point(coords) {
    if (coords.size() != 3) {
        throw invalid_argument("Point3D must have 3 coordinates");
    }
    m_rX = coords[0];
    m_rY = coords[1];
    m_rZ = coords[2];
}

Point3D::Point3D(double x, double y, double z) : Point(vector<double>{x, y, z}),
                                    m_rX(x), m_rY(y), m_rZ(z) {}

Point3D::Point3D(const Point3D& point) : Point(point),      
                    m_rX(point.m_rX), m_rY(point.m_rY), m_rZ(point.m_rZ) {}

Point3D::~Point3D() {}

void Point3D::SetX(double x) {
    m_rX = x;
    try {
        Point::Set(static_cast<Point>(*this));
    }
    catch (exception& e) {
        throw e;
    }
}

void Point3D::SetY(double y) {
    m_rY = y;
    try {
        Point::Set(static_cast<Point>(*this));
    }
    catch (exception& e) {
        throw e;
    }
}

void Point3D::SetZ(double z) {
    m_rZ = z;
    try {
        Point::Set(static_cast<Point>(*this));
    }
    catch (exception& e) {
        throw e;
    }
}

Point3D& Point3D::operator=(const Point3D& point) {
    m_rX = point.m_rX;
    m_rY = point.m_rY;
    m_rZ = point.m_rZ;
    try {
        Point::Set(static_cast<Point>(*this));
    }
    catch (exception& e) {
        throw e;
    }
    return *this;
}





