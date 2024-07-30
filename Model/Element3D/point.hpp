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
// date: 2024/7/29
// author: Huayu Chen
// edit: delete some math functions that are not suitable for the point class
// reason: the point class should only contain operations that are suitable for points
// -----------------------------------------------------------
// date: 2024/7/30
// author: Huayu Chen
// edit: add string representation for the point class
// reason: to support the output of the point class in string format
// -----------------------------------------------------------
//
//


#ifndef POINT_HPP
#define POINT_HPP

#include <vector>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

//
class Vector;

class Point
{
//
//
public:
    Point(const vector<double>& coords);  
    Point(const Point& p);
    Point(const Vector& vec);
    virtual ~Point();
    Point& operator=(const Point& p);

    double operator[](unsigned int index) const;
    double& operator[](unsigned int index);

    double At(unsigned int index) const;
    void Translate(const Vector& vec);

    double DistanceFromOrigin() const;
    double DistanceFrom(const Point& p) const;
    bool operator==(const Point& p) const;
    bool operator!=(const Point& p) const;

    bool IsOrigin() const;

    Point Middle(const Point& p) const;
    Point Lerp(const Point& p, const double& t) const;
    Vector ToVector() const;
    
    Point Copy() const;
    string ToString() const;

    ostream& operator<<(ostream& os) const;

    static double Distance(const Point& p1, const Point& p2);
    static double LengthFromOrigin(const Point& p);
    static double AngleFromOrigin(const Point& p, const Point& q);
    static double Angle(const Point& p, const Point& q, const Point& r);
    static Point Middle(const Point& p, const Point& q);
    static Point Lerp(const Point& p, const Point& q, const double& t);
    static Vector ToVector(const Point& p);

    static const unsigned int MAX_DIM {999u};
    static const unsigned int MIN_DIM {1u};
    const unsigned int& Dim {m_uiDim};
//
//
private:
    unsigned int m_uiDim;
    vector<double> m_vrCoords;


};




#endif // POINT_HPP