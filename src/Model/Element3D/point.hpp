// [file name] : point.hpp
// [function] : declare the Point class
// [author] : Huayu Chen
// [date] : 2024/7/20

// [edit history] :
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
// reason: the point class should only contain operations 
//         that are suitable for points
// -----------------------------------------------------------
// date: 2024/7/30
// author: Huayu Chen
// edit: add string representation for the point class
// reason: to support the output of the point class in string format
// -----------------------------------------------------------

#ifndef POINT_HPP
#define POINT_HPP

#include <vector>
#include <sstream>
#include <string>
#include <cmath>
#include "vector.hpp"

using namespace std;

// notes about the class Point
// -----------------------------------------------------------
// [class name] : Point
// [function] : represent a point in a multi-dimensional space
// [notes on interface] :
// 1. the point is defined by a vector of coordinates, and can be initialized
//    with a vector object or another point object
// 2. the point class supports basic operations such as distance calculation
//    and angle calculation
// 3. these operations have static versions
// 4. the point class can be converted to a vector object
// 5. the point class can be copied and converted to a string representation
// 6. the point class supports output to a stream
// [author] : Huayu Chen
// [date] : 2024/8/2
// -----------------------------------------------------------

class Point
{
public:
    // default constructor that initializes a point at the origin
    // with a dimension of 1
    Point();
    // constructor that initializes a point with a vector of coordinates
    Point(const vector<double>& coords);  
    // copy constructor that initializes a point from another point
    Point(const Point& point);
    // constructor that initializes a point from a vector object
    Point(const Vector& vec);
    // virtual destructor
    virtual ~Point();
    // assignment operator to assign one point to another
    Point& operator=(const Point& point);

    // returns the coordinate value at the given index (read-only)
    double operator[](unsigned int index) const;
    // returns the coordinate value at the given index (modifiable)
    double& operator[](unsigned int index);

    // returns the coordinate value at the given index (read-only)
    double At(unsigned int index) const;
    // returns the coordinate value at the given index (modifiable)
    double& At(unsigned int index);

    // sets the point's coordinates using a vector of coordinates
    void Set(const vector<double>& coords);
    // sets the point's coordinates using another point
    void Set(const Point& point);
    // sets the point's coordinates using a vector object
    void Set(const Vector& vec);

    // translates the point by a given vector
    void Translate(const Vector& vec);

    // calculates the distance of the point from the origin
    double DistanceFromOrigin() const;
    // calculates the distance between the point and another point
    double DistanceFrom(const Point& point) const;
    // checks if two points are equal
    bool operator==(const Point& point) const;
    // checks if two points are not equal
    bool operator!=(const Point& point) const;

    // checks if the point is at the origin
    bool IsOrigin() const;

    // calculates the middle point between the point and another point
    Point Middle(const Point& point) const;
    // linearly interpolates between the point and another point
    Point Lerp(const Point& point, const double& t) const;
    // converts the point to a vector object
    Vector ToVector() const;
    
    // creates a copy of the point
    Point Copy() const;
    // converts the point to a string representation
    string ToString() const;
    
    // outputs the point to a stream
    ostream& operator<<(ostream& os) const;

    // static method to calculate the distance between two points
    static double Distance(const Point& point1, const Point& point2);
    // static method to calculate the length from the origin to a point
    static double LengthFromOrigin(const Point& point);
    // static method to calculate the angle formed 
    // by two points with respect to the origin
    static double AngleFromOrigin(const Point& point1, const Point& point2);
    // static method to calculate the angle between three points
    static double Angle(const Point& LeftPoint, const Point& MiddlePoint, 
                            const Point& RightPoint);
    // static method to calculate the middle point between two points
    static Point Middle(const Point& point1, const Point& point2);
    // static method to linearly interpolate between two points
    static Point Lerp(
        const Point& point1, const Point& point2, const double& t);
    // static method to convert a point to a vector object
    static Vector ToVector(const Point& point);
    // static method to create a copy of a point
    static Point Copy(const Point& point);
    // static method to convert a point to a string representation
    static string ToString(const Point& point);

    // maximum number of dimensions allowed for a point
    static const unsigned int MAX_DIM {999u};
    // minimum number of dimensions required for a point
    static const unsigned int MIN_DIM {1u};
    // reference to the dimension of the point
    const unsigned int& Dim {m_uiDim};

    // friend function to output a point to a stream
    friend ostream& operator<<(ostream& os, const Point& point);

private:
    // the number of dimensions of the point
    unsigned int m_uiDim;
    // the coordinates of the point
    vector<double> m_vrCoords;
};



#endif // POINT_HPP