// [file name] : point.cpp
// [function] : implement the Point class
// [author] : Huayu Chen
// [date] : 2024/8/4

// [edit history] :
// -----------------------------------------------------------
// date: 2024/8/4
// author: Huayu Chen
// edit: add implementation of the Point class
// reason: to support storing the point in the 3D space
// -----------------------------------------------------------

#include "point.hpp"
#include "vector.hpp"
#include <string>
#include <vector>


#include <exception>
#include <stdexcept>

using namespace std;

// -----------------------------------------------------------
// [name] : Point
// [function] : constructor of the Point class
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Point::Point() {
    m_uiDim = MIN_DIM;
    m_vrCoords = vector<double>(MIN_DIM);
}


// -----------------------------------------------------------
// [name] : Point
// [function] : constructor of the Point class
// [input] : a vector of doubles
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Point::Point(const vector<double>& coords) {
    m_uiDim = static_cast<unsigned int>(coords.size());
    m_vrCoords = coords;
}

// -----------------------------------------------------------
// [name] : Point
// [function] : copy constructor of the Point class
// [input] : a Point object
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Point::Point(const Point& point) {
    m_uiDim = point.m_uiDim;
    m_vrCoords = point.m_vrCoords;
}

// -----------------------------------------------------------
// [name] : Point
// [function] : constructor of the Point class
// [input] : a Vector object
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Point::Point(const Vector& vec) {
    m_uiDim = vec.Dim;
    m_vrCoords = vector<double>(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        m_vrCoords[i] = vec[i];
    }
}

// -----------------------------------------------------------
// [name] : ~Point
// [function] : destructor of the Point class
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Point::~Point() {}

// -----------------------------------------------------------
// [name] : operator=
// [function] : assignment operator of the Point class
// [input] : a Point object
// [output] : a reference to the assigned Point object
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Point& Point::operator=(const Point& point) {
    m_uiDim = point.m_uiDim;
    m_vrCoords = point.m_vrCoords;
    return *this;
}

// -----------------------------------------------------------
// [name] : At
// [function] : returns the coordinate at a specific index
// [input] : an unsigned int representing the index
// [output] : a double reference to the value at the index
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Point::At(unsigned int index) const
{
    // Check index
    if (index <= MIN_DIM)
    {
        throw invalid_argument("Index out of range");
    }
    if (index > m_uiDim)
    {
        throw invalid_argument("Index out of range");
    }
    // Return the value at the index
    try {
        // index - 1 because the input index starts from 1,
        // but the array index starts from 0.
        return m_vrCoords.at(index - 1);
    } 
    catch (exception& e) {
        throw runtime_error("Error: " + string(e.what()));
    }
    
}

// -----------------------------------------------------------
// [name] : operator[]
// [function] : returns the coordinate at a specific index
// [input] : an unsigned int representing the index
// [output] : a double reference to the value at the index
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Point::operator[](unsigned int index) const
{
    return At(index);
}

// -----------------------------------------------------------
// [name] : operator[]
// [function] : returns the coordinate at a specific index (modifiable)
// [input] : an unsigned int representing the index
// [output] : a modifiable double reference to the value at the index
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double& Point::operator[](unsigned int index)
{
    // Check index
    if (index <= MIN_DIM)
    {
        throw invalid_argument("Index out of range");
    }
    if (index > m_uiDim)
    {
        throw invalid_argument("Index out of range");
    }
    // Return the reference of the value at the index
    try {
        // index - 1 because the input index starts from 1,
        // but the array index starts from 0.
        return m_vrCoords.at(index - 1);
    } 
    catch (exception& e) {
        throw runtime_error("Error: " + string(e.what()));
    }
}

// -----------------------------------------------------------
// [name] : Translate
// [function] : translates the point by a given vector
// [input] : a Vector object representing the translation vector
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
void Point::Translate(const Vector& vec)
{
    // Check dimension
    if (vec.Dim != m_uiDim)
    {
        throw invalid_argument("Vector dimension should be \
            equal to point dimension.");
    }
    for (unsigned int i = 0; i < m_uiDim; i++)
    {
        m_vrCoords[i] += vec[i];
    }
}

// -----------------------------------------------------------
// [name] : DistanceFromOrigin
// [function] : calculates the distance of the point from the origin
// [input] : none
// [output] : a double representing the distance from the origin
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Point::DistanceFromOrigin() const
{
    double sum = 0;
    for (unsigned int i = 0; i < m_uiDim; i++)
    {
        sum += m_vrCoords[i] * m_vrCoords[i];
    }
    return sqrt(sum);
}

// -----------------------------------------------------------
// [name] : DistanceFrom
// [function] : calculates the distance between this point and another point
// [input] : a Point object representing the other point
// [output] : a double representing the distance between the points
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Point::DistanceFrom(const Point& p) const
{
    // Check dimension
    if (p.m_uiDim != m_uiDim)
    {
        throw invalid_argument("Point dimension should be \
            equal to point dimension.");
    }
    double sum = 0;
    for (unsigned int i = 0; i < m_uiDim; i++)
    {
        sum += (m_vrCoords[i] - p.m_vrCoords[i]) * 
            (m_vrCoords[i] - p.m_vrCoords[i]);
    }
    return sqrt(sum);
}

// -----------------------------------------------------------
// [name] : operator==
// [function] : compares two points for equality
// [input] : a Point object
// [output] : a boolean indicating if the points are equal
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
bool Point::operator==(const Point& point) const
{
    // Check dimension
    if (m_uiDim != point.m_uiDim)
    {
        return false;
    }
    for (unsigned int i = 0; i < m_uiDim; i++)
    {
        if (fabs(m_vrCoords[i] - point.m_vrCoords[i]) > 1e-6)
        {
            return false;
        }
    }
    return true;
}

// -----------------------------------------------------------
// [name] : operator!=
// [function] : compares two points for inequality
// [input] : a Point object
// [output] : a boolean indicating if the points are not equal
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
bool Point::operator!=(const Point& point) const
{
    return !(*this == point);
}

// -----------------------------------------------------------
// [name] : IsOrigin
// [function] : checks if the point is at the origin
// [input] : none
// [output] : a boolean indicating if the point is at the origin
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
bool Point::IsOrigin() const
{
    for (unsigned int i = 0; i < m_uiDim; i++)
    {
        if (fabs(m_vrCoords[i]) > 1e-6)
        {
            return false;
        }
    }
    return true;
}

// -----------------------------------------------------------
// [name] : Middle
// [function] : calculates the midpoint between this point and another point
// [input] : a Point object representing the other point
// [output] : a Point object representing the midpoint
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Point Point::Middle(const Point& point) const
{
    // Check dimension
    if (point.m_uiDim != m_uiDim)
    {
        throw invalid_argument("Point dimension should be \
            equal to point dimension.");
    }
    vector<double> coords(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++)
    {
        coords[i] = (m_vrCoords[i] + point.m_vrCoords[i]) / 2;
    }
    return Point(coords);
}

// -----------------------------------------------------------
// [name] : Lerp
// [function] : linearly interpolates between this point and another point
// [input] : a Point object representing the other point, and a double t
// [output] : a Point object representing the interpolated point
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Point Point::Lerp(const Point& point, const double& t) const
{
    // Check dimension
    if (point.m_uiDim != m_uiDim)
    {
        throw invalid_argument("Point dimension should be \
            equal to point dimension.");
    }
    vector<double> coords(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++)
    {
        coords[i] = m_vrCoords[i] + t * (point.m_vrCoords[i] - m_vrCoords[i]);
    }
    return Point(coords);
}

// -----------------------------------------------------------
// [name] : ToVector
// [function] : converts the point to a Vector object
// [input] : none
// [output] : a Vector object
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Point::ToVector() const
{
    return Vector(m_vrCoords);
}

// -----------------------------------------------------------
// [name] : Copy
// [function] : creates a copy of the point
// [input] : none
// [output] : a Point object that is a copy of the original
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Point Point::Copy() const
{
    return Point(m_vrCoords);
}

// -----------------------------------------------------------
// [name] : ToString
// [function] : converts the point to a string representation
// [input] : none
// [output] : a string representing the point
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
string Point::ToString() const
{
    // Create a string representation of the point
    // The format is (x1, x2, ..., xn)
    string str = "(";
    for (unsigned int i = 0; i < m_uiDim; i++)
    {
        str += to_string(m_vrCoords[i]);
        if (i < m_uiDim - 1)
        {
            // Add a comma and a space if it is not the last coordinate
            str += ", ";
        }
    }
    str += ")";
    return str;
}

// -----------------------------------------------------------
// [name] : operator<<
// [function] : outputs the point to a stream
// [input] : an ostream object and a Point object
// [output] : an ostream reference
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
ostream& Point::operator<<(ostream& os) const
{
    os << ToString();
    return os;
}

// -----------------------------------------------------------
// [name] : Distance
// [function] : calculates the distance between two points
// [input] : two Point objects
// [output] : a double representing the distance between the points
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Point::Distance(const Point& point1, const Point& point2)
{
    return point1.DistanceFrom(point2);
}

// -----------------------------------------------------------
// [name] : LengthFromOrigin
// [function] : calculates the distance from the origin to a point
// [input] : a Point object
// [output] : a double representing the distance from the origin
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Point::LengthFromOrigin(const Point& point)
{
    return point.DistanceFromOrigin();
}

// -----------------------------------------------------------
// [name] : AngleFromOrigin
// [function] : calculates the angle between the origin and two points
// [input] : two Point objects
// [output] : a double representing the angle in radians
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Point::AngleFromOrigin(const Point& point1, const Point& point2)
{
    // Check dimension
    if (point1.m_uiDim != point2.m_uiDim)
    {
        throw invalid_argument("Point dimension should be \
            equal to point dimension.");
    }
    double dot = 0;
    double norm1 = 0;
    double norm2 = 0;
    // Calculate the dot product and the norms of the two points
    for (unsigned int i = 0; i < point1.m_uiDim; i++)
    {
        dot += point1.m_vrCoords[i] * point2.m_vrCoords[i];
        norm1 += point1.m_vrCoords[i] * point1.m_vrCoords[i];
        norm2 += point2.m_vrCoords[i] * point2.m_vrCoords[i];
    }
    return acos(dot / sqrt(norm1 * norm2));
}

// -----------------------------------------------------------
// [name] : Angle
// [function] : calculates the angle between three points
// [input] : three Point objects
// [output] : a double representing the angle in radians
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Point::Angle(const Point& LeftPoint, const Point& MiddlePoint, 
                        const Point& RightPoint)
{
    // Calculate the vectors from the middle point to the left and right points
    // and calculate the angle between them
    // The angle is calculated using the dot product and the norms 
    // of the two vectors
    Vector vec1 = MiddlePoint.ToVector() - LeftPoint.ToVector();
    Vector vec2 = MiddlePoint.ToVector() - RightPoint.ToVector();
    return vec1.AngleFrom(vec2);
}

// -----------------------------------------------------------
// [name] : Middle
// [function] : calculates the midpoint between two points
// [input] : two Point objects
// [output] : a Point object representing the midpoint
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Point Point::Middle(const Point& point1, const Point& point2)
{
    return point1.Middle(point2);
}

// -----------------------------------------------------------
// [name] : Lerp
// [function] : linearly interpolates between two points
// [input] : two Point objects and a double t
// [output] : a Point object representing the interpolated point
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Point Point::Lerp(const Point& point1, const Point& point2, const double& t)
{
    return point1.Lerp(point2, t);
}

// -----------------------------------------------------------
// [name] : ToVector
// [function] : converts a Point object to a Vector object
// [input] : a Point object
// [output] : a Vector object
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Point::ToVector(const Point& point)
{
    return point.ToVector();
}

// -----------------------------------------------------------
// [name] : Copy
// [function] : creates a copy of a Point object
// [input] : a Point object
// [output] : a Point object that is a copy of the original
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Point Point::Copy(const Point& point)
{
    return point.Copy();
}

// -----------------------------------------------------------
// [name] : ToString
// [function] : converts a Point object to a string representation
// [input] : a Point object
// [output] : a string representing the point
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
string Point::ToString(const Point& point)
{
    return point.ToString();
}

// -----------------------------------------------------------
// [name] : Set
// [function] : sets the coordinates of the point
// [input] : a vector of doubles representing the coordinates
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
void Point::Set(const vector<double>& coords)
{
    // cast the size of the vector to unsigned int
    m_uiDim = static_cast<unsigned int>(coords.size());
    m_vrCoords = coords;
}

// -----------------------------------------------------------
// [name] : Set
// [function] : sets the coordinates of the point to those of another point
// [input] : a Point object
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
void Point::Set(const Point& point)
{
    m_uiDim = point.m_uiDim;
    m_vrCoords = point.m_vrCoords;
}

// -----------------------------------------------------------
// [name] : Set
// [function] : sets the coordinates of the point to those of a vector
// [input] : a Vector object
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
void Point::Set(const Vector& vec)
{
    m_uiDim = vec.Dim;
    m_vrCoords = vector<double>(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++)
    {
        m_vrCoords[i] = vec[i];
    }
}

// -----------------------------------------------------------
// [name] : operator<<
// [function] : outputs the Point object to an output stream
// [input] : an ostream reference and a Point object
// [output] : an ostream reference
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
ostream& operator<<(ostream& os, const Point& point)
{
    os << point.ToString();
    return os;
}

