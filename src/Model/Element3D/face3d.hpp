// [file name] : face3d.hpp
// [function] : declare the Face3D class
// [author] : Huayu Chen
// [date] : 2024/7/30

// [edit history] :
// -----------------------------------------------------------
// date: 2024/7/30
// author: Huayu Chen
// edit: init face3d class
//       add face3d operations with points and lines
//       add some common math functions
// reason: to support various operations on face3d
// -----------------------------------------------------------

#ifndef FACE3D_HPP
#define FACE3D_HPP

#include <string>
#include <ostream>
#include <vector>
#include "point3d.hpp"
#include "line3d.hpp"
#include <string>
#include "fixedsizepoint3dcontainer.hpp"

using namespace std;

// notes about the class Face3D
// -----------------------------------------------------------
// [class name] : Face3D
// [function] : represent a face in a three-dimensional space
// [notes on interface] :
// 1. the face is defined by three points or two lines or a point and a line
// 2. the face has some common geometric operations such as distance calculation
//    and angle calculation
// 3. the class is derived from the FixedSizePoint3DContainer class, which means
//    that the face can be represented by a fixed number of points
// [author] : Huayu Chen
// [date] : 2024/8/2
// -----------------------------------------------------------


class Face3D : public FixedSizePoint3DContainer
{
public:
    // constructor 1: three points
    Face3D(const Point3D& point1, const Point3D& point2, const Point3D& point3);
    // constructor 2: a point and a line
    Face3D(const Point3D& point, const Line3D& line);
    // constructor 3: two lines
    Face3D(const Line3D& line1, const Line3D& line2);
    // constructor 4: three points in a vector
    Face3D(const vector<Point3D>& points);
    // virtual destructor
    virtual ~Face3D();
    // assignment operator
    Face3D& operator=(const Face3D& face);

    // check if the face is parallel to another face
    bool IsParallel(const Face3D& face) const;
    // check if the face is parallel to a line
    bool IsParallel(const Line3D& line) const;
    // check if the face is perpendicular to another face
    bool IsPerpendicular(const Face3D& face) const;
    // check if the face is coincident with another face
    bool IsCoincident(const Face3D& face) const;
    // check if a point is on the face plane
    bool IsPointOnFacePlane(const Point3D& point) const;
    // calculate the angle between two faces
    double Angle(const Face3D& face) const;
    // calculate the distance between two faces
    double Distance(const Face3D& face) const;
    // calculate the distance between a face and a point
    double Distance(const Point3D& point) const;
    // calculate the distance between a face and a line
    double Distance(const Line3D& line) const;
    // get the normal vector of the face
    Line3D PerpendicularLine() const;
    // get the area of the face defined by the three points
    double Area() const;
    // check if the two faces are identical in that 
    // the three points are the same
    static bool IsSameFace(const Face3D& face1, const Face3D& face2);
};

#endif // FACE3D_HPP
