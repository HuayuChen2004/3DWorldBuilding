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

using namespace std;

class Line3D;
class Point3D;

class Face3D {
public:
    Face3D(const Point3D& p1, const Point3D& p2, const Point3D& p3);
    Face3D(const Point3D& p, const Line3D& l);
    Face3D(const Line3D& l1, const Line3D& l2);
    Face3D(const Face3D& face);
    virtual ~Face3D();

    bool operator==(const Face3D& face) const;
    bool operator!=(const Face3D& face) const;

    bool IsParallel(const Face3D& face) const;
    bool IsPerpendicular(const Face3D& face) const;
    bool IsCoincident(const Face3D& face) const;

    bool IsPointOnFace(const Point3D& p) const;

    double Angle(const Face3D& face) const;
    double Distance(const Face3D& face) const;
    double Distance(const Point3D& p) const;
    double Distance(const Line3D& line) const;

    Line3D Intersection(const Face3D& face) const;
    Point3D Intersection(const Line3D& line) const;

    Line3D PerpendicularLine() const;

    string ToString() const;
    ostream& operator<<(ostream& os) const;

private:
// if the face is initiated with a line and a point, 
// convert the line to two points that the line is made up of 
    Point3D* p1;
    Point3D* p2;
    Point3D* p3;
};


#endif // FACE3D_HPP
