// the header file of the class Face3D
// the class Face3D is a class that represents a face in a three-dimensional space
// edit logging:
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
#include "fixedsizepoint3dcontainer.hpp"

using namespace std;

class Line3D;
class Point3D;

class Face3D : public FixedSizePoint3DContainer
{
public:
    // 记得在构造函数里面调用父类的构造函数
    Face3D(const Point3D& point1, const Point3D& point2, const Point3D& point3);
    Face3D(const Point3D& point, const Line3D& line);
    Face3D(const Line3D& line1, const Line3D& line2);
    Face3D(const Face3D& face);
    Face3D(const vector<Point3D>& points);
    virtual ~Face3D();
    Face3D& operator=(const Face3D& face);

    bool operator==(const Face3D& face) const;
    bool operator!=(const Face3D& face) const;

    bool IsParallel(const Face3D& face) const;
    bool IsPerpendicular(const Face3D& face) const;
    bool IsCoincident(const Face3D& face) const;

    bool IsPointOnFace(const Point3D& point) const;

    double Angle(const Face3D& face) const;
    double Distance(const Face3D& face) const;
    double Distance(const Point3D& point) const;
    double Distance(const Line3D& line) const;

    Line3D Intersection(const Face3D& face) const;
    Point3D Intersection(const Line3D& line) const;

    Line3D PerpendicularLine() const;

    double Area() const;

private:
// if the face is initiated with a line and a point, 
// convert the line to two points that the line is made up of 
    Point3D* m_pp1;
    Point3D* m_pp2;
    Point3D* m_pp3;

};


#endif // FACE3D_HPP
