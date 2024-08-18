// [file name] : point3d.hpp
// [function] : declare the Point3D class
// [author] : Huayu Chen
// [date] : 2024/7/20

// [edit history] :
// -----------------------------------------------------------
// date: 2024/7/20
// author: Huayu Chen
// edit: init point3d class
//       add point3d operations
//       add some common math functions
// reason: to support various operations on point3d
//         so that the point3d class can be used in many places
//         and can be extended to support more operations
// -----------------------------------------------------------
// date: 2024/7/30
// author: Huayu Chen
// edit: add some relationship judgement functions for points and lines and faces
//       add some distance calculation functions for points and lines and faces
//       add const reference for point3d members
// reason: to support more operations on points and lines and faces
//         and to make the code more readable and efficient
// -----------------------------------------------------------
// date: 2024/8/1
// author: Huayu Chen
//
//
//// the header file of the class Point3D
// the class Point3D is a class that represents a point in a three-dimensional space
// a point3d can be initiated with a 3d vector
// some vector operations can also be used on points
//
//
//
//
#ifndef POINT3D_HPP
#define POINT3D_HPP

#include <vector>
#include <cmath>
#include <string>
#include "point.hpp"

using namespace std;


class Point3D: public Point
{
public:
    // constructor that initializes the point with x, y, and z coordinates
    Point3D(double x, double y, double z);  
    // constructor that initializes the point using a vector of coordinates
    Point3D(const vector<double>& coords);
    // copy constructor that initializes the point from another Point3D object
    Point3D(const Point3D& point);
    // assignment operator to assign one Point3D object to another
    Point3D& operator=(const Point3D& point);
    // virtual destructor
    virtual ~Point3D();

    // sets the x coordinate of the point
    void SetX(double x);
    // sets the y coordinate of the point
    void SetY(double y);
    // sets the z coordinate of the point
    void SetZ(double z);

    // reference to the x coordinate of the point (read-only)
    const double& X{m_rX};
    // reference to the y coordinate of the point (read-only)
    const double& Y{m_rY};
    // reference to the z coordinate of the point (read-only)
    const double& Z{m_rZ};

private:
    // the x coordinate of the point
    double m_rX;
    // the y coordinate of the point
    double m_rY;
    // the z coordinate of the point
    double m_rZ;
};

#endif // POINT3D_HPP

