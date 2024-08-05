//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
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
#include "point.hpp"
#include "vector.hpp"
#include <string>
#include <vector>


#include <exception>
#include <stdexcept>

using namespace std;



Point::Point(const vector<double>& coords) {
    m_uiDim = coords.size();
    m_vrCoords = coords;
}

Point::Point(const Point& point) {
    m_uiDim = point.m_uiDim;
    m_vrCoords = point.m_vrCoords;
}

Point::Point(const Vector& vec) {
    m_uiDim = vec.Dim;
    m_vrCoords = vector<double>(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        m_vrCoords[i] = vec[i];
    }
}

Point& Point::operator=(const Point& point) {
    m_uiDim = point.m_uiDim;
    m_vrCoords = point.m_vrCoords;
    return *this;
}
//
//
//
double Point::At(unsigned int index) const
{
    // Check index
    if (index <= MIN_DIM)
    {
        throw invalid_argument("Index should be greater than 0.");
    }
    if (index > m_uiDim)
    {
        throw invalid_argument("Index should be less \
                than or equal to dimension.");
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
//
//
//
double Point::operator[](unsigned int index) const
{
    return At(index);
}

double& Point::operator[](unsigned int index)
{
    // Check index
    if (index <= MIN_DIM)
    {
        throw invalid_argument("Index should be greater than 0.");
    }
    if (index > m_uiDim)
    {
        throw invalid_argument("Index should be less than \
            or equal to dimension.");
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

void Point::Translate(const Vector& vec)
{
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

double Point::DistanceFromOrigin() const
{
    double sum = 0;
    for (unsigned int i = 0; i < m_uiDim; i++)
    {
        sum += m_vrCoords[i] * m_vrCoords[i];
    }
    return sqrt(sum);
}

double Point::DistanceFrom(const Point& p) const
{
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

bool Point::operator==(const Point& point) const
{
    if (m_uiDim != point.m_uiDim)
    {
        return false;
    }
    for (unsigned int i = 0; i < m_uiDim; i++)
    {
        if (m_vrCoords[i] != point.m_vrCoords[i])
        {
            return false;
        }
    }
    return true;
}

bool Point::operator!=(const Point& point) const
{
    return !(*this == point);
}

bool Point::IsOrigin() const
{
    for (unsigned int i = 0; i < m_uiDim; i++)
    {
        if (m_vrCoords[i] != 0)
        {
            return false;
        }
    }
    return true;
}

Point Point::Middle(const Point& point) const
{
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
 
Point Point::Lerp(const Point& point, const double& t) const
{
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

Vector Point::ToVector() const
{
    return Vector(m_vrCoords);
}

Point Point::Copy() const
{
    return Point(m_vrCoords);
}

string Point::ToString() const
{
    string str = "(";
    for (unsigned int i = 0; i < m_uiDim; i++)
    {
        str += to_string(m_vrCoords[i]);
        if (i < m_uiDim - 1)
        {
            str += ", ";
        }
    }
    str += ")";
    return str;
}

ostream& Point::operator<<(ostream& os) const
{
    os << ToString();
    return os;
}

double Point::Distance(const Point& point1, const Point& point2)
{
    return point1.DistanceFrom(point2);
}

double Point::LengthFromOrigin(const Point& point)
{
    return point.DistanceFromOrigin();
}

double Point::AngleFromOrigin(const Point& point1, const Point& point2)
{
    if (point1.m_uiDim != point2.m_uiDim)
    {
        throw invalid_argument("Point dimension should be \
            equal to point dimension.");
    }
    double dot = 0;
    double norm1 = 0;
    double norm2 = 0;
    for (unsigned int i = 0; i < point1.m_uiDim; i++)
    {
        dot += point1.m_vrCoords[i] * point2.m_vrCoords[i];
        norm1 += point1.m_vrCoords[i] * point1.m_vrCoords[i];
        norm2 += point2.m_vrCoords[i] * point2.m_vrCoords[i];
    }
    return acos(dot / sqrt(norm1 * norm2));
}

double Point::Angle(const Point& LeftPoint, const Point& MiddlePoint, 
                        const Point& RightPoint)
{
    Vector vec1 = MiddlePoint.ToVector() - LeftPoint.ToVector();
    Vector vec2 = MiddlePoint.ToVector() - RightPoint.ToVector();
    return vec1.AngleFrom(vec2);
}

Point Point::Middle(const Point& point1, const Point& point2)
{
    return point1.Middle(point2);
}

Point Point::Lerp(const Point& point1, const Point& point2, const double& t)
{
    return point1.Lerp(point2, t);
}

Vector Point::ToVector(const Point& point)
{
    return point.ToVector();
}

Point Point::Copy(const Point& point)
{
    return point.Copy();
}

string Point::ToString(const Point& point)
{
    return point.ToString();
}

void Point::Set(const vector<double>& coords)
{
    m_uiDim = coords.size();
    m_vrCoords = coords;
}

void Point::Set(const Point& point)
{
    m_uiDim = point.m_uiDim;
    m_vrCoords = point.m_vrCoords;
}

void Point::Set(const Vector& vec)
{
    m_uiDim = vec.Dim;
    m_vrCoords = vector<double>(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++)
    {
        m_vrCoords[i] = vec[i];
    }
}

ostream& operator<<(ostream& os, const Point& point)
{
    os << point.ToString();
    return os;
}



//
//
//
