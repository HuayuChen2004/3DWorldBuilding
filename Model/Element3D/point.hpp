// the header file of the class Point
// the class Point is a class that represents a point in a multi-dimensional space
// a point can be initiated with a vector
// some vector operations can also be used on points
// edit logging:
// -----------------------------------------------------------
// date: 2024/7/20
// author: Huayu Chen
// edit: init point class
//       add point operations
//       add some common math functions
// reason: to support various operations on points
//         so that the point class can be used in many places
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


#ifndef POINT_HPP
#define POINT_HPP

#include <vector>
using namespace std;

//
class Vector;
class Line;
class Face3D;

class Point
{
//
//
public:
    Point(unsigned int dim);
    Point(const vector<double>& coords);
    Point(const Point& p);
    Point(const Vector& vec);
    virtual ~Point();

    double operator[](unsigned int index) const;
    double& operator[](unsigned int index);

    double At(unsigned int index) const;
    void Translate(const Vector& vec);
    void Translate(const double& dx, const double& dy);
    void Scale(const double& factor);
    void Scale(const double& sx, const double& sy);
    void Rotate(const double& angle);
    void Rotate(const double& angle, const Point& center);
    void Reflect(const Point& p);
    void Normalize();
    double DistanceFromOrigin() const;
    double DistanceFrom(const Point& p) const;
    bool operator==(const Point& p) const;
    bool operator!=(const Point& p) const;
    Point operator+(const Point& p) const;
    Point operator-(const Point& p) const;
    Point operator*(const double& factor) const;
    Point operator/(const double& factor) const;
    double Dot(const Point& p) const;
    Vector Cross(const Point& p) const;
    double Angle(const Point& p) const;
    double DistanceToLine(const Line& line) const;
    Point ProjectToLine(const Line& line) const;
    double DistanceToPlane(const Face3D& face) const;
    Point ProjectToPlane(const Face3D& face) const;
    bool IsZero() const;
    bool IsInside(const Face3D& face) const;
    bool IsOnBoundary(const Face3D& face) const;
    bool IsOnFace(const Face3D& face) const;
    bool IsInside(const Line& line) const;
    bool IsOnEnd(const Line& line) const;
    Point Middle(const Point& p) const;
    Point Lerp(const Point& p, const double& t) const;
    Vector ToVector() const;
    Vector ToVector(const Point& p) const;
    void InsertDimension(unsigned int dim, double value = 0.0);
    void RemoveDimension(unsigned int dim);
    Point Copy() const;
    std::string ToString() const;

    static double Distance(const Point& p1, const Point& p2);
    static double LengthFromOrigin(const Point& p);
    static double Length(const Point& p, const Point& q);
    static double AngleFromOrigin(const Point& p, const Point& q);
    static double Angle(const Point& p, const Point& q, const Point& r);
    static Point Middle(const Point& p, const Point& q);
    static Point Lerp(const Point& p, const Point& q, const double& t);

    static const unsigned int MAX_DIM {999u};
    static const unsigned int MIN_DIM {1u};
    const unsigned int& Dim {m_uiDim};
//
//
private:
    unsigned int m_uiDim;
    vector<double> m_vdCoords;


};




#endif // POINT_HPP