//
//
//
// the header file of the class Point3D
// the class Point3D is a class that represents a point in a three-dimensional space
// a point3d can be initiated with a 3d vector
// some vector operations can also be used on points
// edit logging:
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
//
//
//
//
//
//更改记录
//
//
//
//
//
//
#ifndef POINT3D_HPP
#define POINT3D_HPP

#include <vector>
#include <cmath>


class Line3D;
class Face3D;

class Point3D
{
public:
    Point3D(double x, double y, double z);
    Point3D(const Point3D& p);
    Point3D(const std::vector<double>& v);
    virtual ~Point3D();
    Point3D& operator=(const Point3D& p);

    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);

    double GetX() const;
    double GetY() const;
    double GetZ() const;
    
    bool operator==(const Point3D& p) const;
    bool operator!=(const Point3D& p) const;

    Point3D AddVector(const std::vector<double>& v);
    Point3D SubtractVector(const std::vector<double>& v);

    double DistanceToLine3d(const Line3D& line) const;
    double DistanceToFace3d(const Face3D& face) const;

    bool IsOnLine3D(const Line3D& line) const;
    bool IsOnPlane3D(const Face3D& face) const;

    Point3D ProjectToLine3D(const Line3D& line) const;
    Point3D ProjectToPlane3D(const Face3D& face) const;

    std::vector<double> ToVector() const;

private:
    double m_rX;
    double m_rY;
    double m_rZ;
};

#endif // POINT3D_HPP

