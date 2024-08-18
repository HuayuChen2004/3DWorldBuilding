// [file name] : line3d.hpp
// [function] : declare the Line3D class
// [author] : Huayu Chen
// [date] : 2024/7/20

// [edit history] :
// -----------------------------------------------------------
// date: 2024/7/20
// author: Huayu Chen
// edit: init line class
//       add line operations
//       add some common math functions
// reason: to support various operations on lines
//         so that the line class can be used in many places
//         and can be extended to support more operations
// -----------------------------------------------------------
// date: 2024/7/30
// author: Huayu Chen
// edit: add angle calculation for lines
//       add string representation for the line class
//       add some static functions for line operations
//       add some relationship judgement functions for lines and points
// reason: to support more operations on lines and points
//         and to make the line class more useful
// -----------------------------------------------------------

#ifndef LINE3D_HPP
#define LINE3D_HPP

#include <string>
#include <ostream>
#include <vector>
#include "point3d.hpp"
#include "fixedsizepoint3dcontainer.hpp"

using namespace std;

// notes about the class Line3D
// -----------------------------------------------------------
// [class name] : Line3D
// [function] : represent a line in a three-dimensional space
// [notes on interface] :
// 1. the line is defined by two points, derived from the 
//    FixedSizePoint3DContainer class
// 2. the line has some common geometric operations such as distance calculation
//    and angle calculation
// 3. the line has some relationship judgement functions such as parallel,
//    perpendicular, and coincident, these functions have static versions
// 4. there are getter and setter functions for the two points of the line
// [author] : Huayu Chen
// [date] : 2024/8/2
// -----------------------------------------------------------


class Line3D : public FixedSizePoint3DContainer
{
public:
    // constructor 1: init with two points
    Line3D(const Point3D& point1, const Point3D& point2);
    // constructor 2: init with two points in a vector
    Line3D(const vector<Point3D>& points);
    // copy constructor
    virtual ~Line3D();
    // assignment operator
    Line3D& operator=(const Line3D& line);

    // calculate the distance from the current line to a given point.
    double Distance(const Point3D& point) const;
    // calculate the distance between the current line and another line.
    double Distance(const Line3D& line) const;
    // Find the intersection point between the current line and another line.
    Point3D Intersection(const Line3D& line) const;
    // check if the current line is parallel to another line.
    bool IsParallel(const Line3D& line) const;
    // check if the current line is perpendicular to another line.
    bool IsPerpendicular(const Line3D& line) const;
    // check if the current line is coincident (identical) with another line.
    bool Iscoincident(const Line3D& line) const;
    // check if a given point lies on the current line.
    bool IsPointOnLine(const Point3D& point) const;
    // check if the current line and another line lie on the same plane.
    bool OnSamePlane(const Line3D& line) const;
    // calculate the angle between the current line and another line.
    double Angle(const Line3D& line) const;
    // static method to calculate the angle between two lines.
    static double Angle(const Line3D& line1, const Line3D& line2);
    // static method to calculate the distance between two lines.
    static double Distance(const Line3D& line1, const Line3D& line2);
    // static method to calculate the distance between a point and a line.
    static double Distance(const Point3D& point, const Line3D& line);
    // static method to find the projection of a point onto a line.
    static Point3D Projection(const Point3D& point, const Line3D& line);
    // static method to find the intersection point between two lines.
    static Point3D Intersection(const Line3D& line1, const Line3D& line2);
    // static method to check if two lines are parallel.
    static bool IsParallel(const Line3D& line1, const Line3D& line2);
    // static method to check if two lines are perpendicular.
    static bool IsPerpendicular(const Line3D& line1, const Line3D& line2);
    // static method to check if two lines are coincident (identical).
    static bool IsCoincident(const Line3D& line1, const Line3D& line2);
    // static method to check if a point lies on a given line.
    static bool IsPointOnLine(const Point3D& point, const Line3D& line);
    // static method to check if two line segments are the same.
    static bool IsSameSegment(const Line3D& line1, const Line3D& line2);

    // get the first point of the line.
    Point3D GetP1() const;
    // get the second point of the line.
    Point3D GetP2() const;

    // set the first point of the line.
    void SetP1(const Point3D& point);
    // set the second point of the line.
    void SetP2(const Point3D& point);

    // calculate the length of the line.
    double Length() const;

};

#endif // LINE3D_HPP