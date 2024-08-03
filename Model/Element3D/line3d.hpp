// this is the header file for the line class
// a line is made up of two Point3Ds
// the line class can be used to calculate the distance between two Point3Ds
// the line class can also be used to calculate the intersection of two lines
// edit logging:
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
#include "fixedsizepoint3dcontainer.hpp"

using namespace std;

class Point3D;
class Face3D;

class Line3D : public FixedSizePoint3DContainer
{
public:
    Line3D(const Point3D& point1, const Point3D& point2);
    Line3D(const Line3D& line);
    Line3D(const vector<Point3D>& points);
    virtual ~Line3D();
    Line3D& operator=(const Line3D& line);

    double Distance(const Point3D& point) const;
    double Distance(const Line3D& line) const;
    Point3D Intersection(const Line3D& line) const;

    bool operator==(const Line3D& line) const;
    bool operator!=(const Line3D& line) const;

    bool IsParallel(const Line3D& line) const;
    bool IsPerpendicular(const Line3D& line) const;
    bool IsCoincident(const Line3D& line) const;

    bool IsPointOnLine(const Point3D& point) const;

    double Angle(const Line3D& line) const;

    static double Angle(const Line3D& line1, const Line3D& line2);
    static double Distance(const Line3D& line1, const Line3D& line2);
    static double Distance(const Point3D& p, const Line3D& line);
    
    static Point3D Projection(const Point3D& point, const Line3D& line);
    static Point3D Intersection(const Line3D& line1, const Line3D& line2);
    static bool IsParallel(const Line3D& line1, const Line3D& line2);
    static bool IsPerpendicular(const Line3D& line1, const Line3D& line2);
    static bool IsCoincident(const Line3D& line1, const Line3D& line2);
    static bool IsPointOnLine(const Point3D& point, const Line3D& line);

    Face3D PerpendicularPlane() const;

    Point3D GetP1() const;
    Point3D GetP2() const;

    double Length() const;

private:
    Point3D* m_pp1;
    Point3D* m_pp2;
};

#endif // LINE3D_HPP