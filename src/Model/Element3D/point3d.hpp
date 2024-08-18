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
    Point3D(double x, double y, double z);  
    // remember to add const unsigned int& Dim{3} in the cpp file
    Point3D(const vector<double>& coords);
    Point3D(const Point3D& point);
    Point3D& operator=(const Point3D& point);
    virtual ~Point3D();

    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);

    // double DistanceToLine3D(const Line3D& line) const;
    // double DistanceToFace3D(const Face3D& face) const;

    // Point3D ProjectToLine3D(const Line3D& line) const;
    // Point3D ProjectToPlane3D(const Face3D& face) const;

    // bool IsOnBoundary(const Face3D& face) const;
    // bool IsInside(const Line3D& line) const;
    // bool IsInside(const Face3D& face) const;
    // bool IsOnEnd(const Line3D& line) const;

    const double& X{m_rX};
    const double& Y{m_rY};
    const double& Z{m_rZ};

private:
    double m_rX;
    double m_rY;
    double m_rZ;
};

#endif // POINT3D_HPP

