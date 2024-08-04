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
#include "vector.hpp"
using namespace std;



class Point
{
//
//
public:
    Point(const vector<double>& coords);  
    Point(const Point& point);
    Point(const Vector& vec);
    virtual ~Point();
    Point& operator=(const Point& point);

    double operator[](unsigned int index) const;
    double& operator[](unsigned int index);

    double At(unsigned int index) const;
    double& At(unsigned int index);

    void Set(const vector<double>& coords);
    void Set(const Point& point);
    void Set(const Vector& vec);

    void Translate(const Vector& vec);

    double DistanceFromOrigin() const;
    double DistanceFrom(const Point& point) const;
    bool operator==(const Point& point) const;
    bool operator!=(const Point& point) const;

    bool IsOrigin() const;

    Point Middle(const Point& point) const;
    Point Lerp(const Point& point, const double& t) const;
    Vector ToVector() const;
    
    Point Copy() const;
    string ToString() const;
    

    ostream& operator<<(ostream& os) const;

    static double Distance(const Point& point1, const Point& point2);
    static double LengthFromOrigin(const Point& point);
    static double AngleFromOrigin(const Point& point1, const Point& point2);
    static double Angle(const Point& LeftPoint, const Point& MiddlePoint, 
                            const Point& RightPoint);
    static Point Middle(const Point& point1, const Point& point2);
    static Point Lerp(const Point& point1, const Point& point2, const double& t);
    static Vector ToVector(const Point& point);
    static Point Copy(const Point& point);
    static string ToString(const Point& point);

    static const unsigned int MAX_DIM {999u};
    static const unsigned int MIN_DIM {1u};
    const unsigned int& Dim {m_uiDim};

    friend ostream& operator<<(ostream& os, const Point& point);
//
//
private:
    unsigned int m_uiDim;
    vector<double> m_vrCoords;


};




#endif // POINT_HPP