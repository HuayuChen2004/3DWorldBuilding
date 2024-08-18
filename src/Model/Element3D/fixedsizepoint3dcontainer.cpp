// [file name] : fixedsizepoint3dcontainer.cpp
// [function] : implement the FixedSizePoint3DContainer class
// [author] : Huayu Chen
// [date] : 2024/8/3

// [edit history] :
// -----------------------------------------------------------
// date: 2024/8/3
// author: Huayu Chen
// edit: add implementation of the FixedSizePoint3DContainer class
// reason: to support storing a fixed size container of 3D points
// -----------------------------------------------------------

#include "fixedsizepoint3dcontainer.hpp"
#include "point3d.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <regex>

using namespace std;

// -----------------------------------------------------------
// [name] : FixedSizePoint3DContainer
// [function] : constructor of the FixedSizePoint3DContainer class
// [input] : a vector of Point3D
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
FixedSizePoint3DContainer::FixedSizePoint3DContainer(
            const vector<Point3D>& points) : m_points(points) {
    m_uiSize = points.size();
}

// -----------------------------------------------------------
// [name] : FixedSizePoint3DContainer
// [function] : copy constructor of the FixedSizePoint3DContainer class
// [input] : a FixedSizePoint3DContainer object
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
FixedSizePoint3DContainer::FixedSizePoint3DContainer(
            const FixedSizePoint3DContainer& container) : 
    m_points(container.m_points) {
    m_uiSize = container.m_uiSize;
}

// -----------------------------------------------------------
// [name] : GetPoints
// [function] : get the points in the container
// [input] : none
// [output] : a vector of Point3D
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
vector<Point3D> FixedSizePoint3DContainer::GetPoints() const {
    vector<Point3D> pointsCopy = m_points;
    return pointsCopy;
}

// -----------------------------------------------------------
// [name] : GetPoint
// [function] : get a point in the container by index
// [input] : an unsigned int index
// [output] : a Point3D object
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
Point3D FixedSizePoint3DContainer::GetPoint(unsigned int index) const {
    Point3D point = m_points.at(index);
    return point;
}

// -----------------------------------------------------------
// [name] : ModifyPoint
// [function] : modify a point in the container by index
// [input] : an unsigned int index and a Point3D object
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
void FixedSizePoint3DContainer::ModifyPoint(unsigned int index, 
            const Point3D& point) {
    // check if the index is out of range
    if (index >= m_uiSize) {
        throw invalid_argument("Index out of range");
    }
    // check if the point already exists in the container
    if (find(m_points.begin(), m_points.end(), point) != m_points.end()) {
        throw invalid_argument("Point already exists in the container.");
    }
    // modify m_points
    m_points[index].Set(point);
}

// -----------------------------------------------------------
// [name] : ToStrings
// [function] : convert the container to a vector of strings
// [input] : none
// [output] : a vector of strings
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
vector<string> FixedSizePoint3DContainer::ToStrings() const {
    vector<string> pointStrings;
    // convert each point to a string
    for (const Point3D& point : m_points) {
        pointStrings.push_back(point.ToString());
    }
    return pointStrings;
}

// -----------------------------------------------------------
// [name] : operator<<
// [function] : overload the output operator for the class
// [input] : an ostream object and a FixedSizePoint3DContainer object
// [output] : an ostream object
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
ostream& FixedSizePoint3DContainer::operator<<(ostream& os) const {
    // output each point in the container
    for (const Point3D& point : m_points) {
        os << point << " ";
    }
    return os;
}

// -----------------------------------------------------------
// [name] : operator==
// [function] : overload the equal operator for the class
// [input] : a FixedSizePoint3DContainer object
// [output] : a boolean value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
bool FixedSizePoint3DContainer::operator==(
            const FixedSizePoint3DContainer& container) const {
    return m_points == container.m_points;
}

// -----------------------------------------------------------
// [name] : operator!=
// [function] : overload the not equal operator for the class
// [input] : a FixedSizePoint3DContainer object
// [output] : a boolean value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
bool FixedSizePoint3DContainer::operator!=(const FixedSizePoint3DContainer& 
            container) const {
    return m_points != container.m_points;
}

// -----------------------------------------------------------
// [name] : ~FixedSizePoint3DContainer
// [function] : destructor of the FixedSizePoint3DContainer class
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
FixedSizePoint3DContainer::~FixedSizePoint3DContainer() {
    m_points.clear();
}

// -----------------------------------------------------------
// [name] : operator<<
// [function] : overload the output operator for the class
// [input] : an ostream object and a FixedSizePoint3DContainer object
// [output] : an ostream object
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
ostream& operator<<(ostream& os, const FixedSizePoint3DContainer& container) {
    return container.operator<<(os);
}

// -----------------------------------------------------------
// [name] : IsPoint3DInContainer
// [function] : check if a Point3D object is in the container
// [input] : a Point3D object
// [output] : a boolean value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
bool FixedSizePoint3DContainer::IsPoint3DInContainer(
            const Point3D& point) const {
    return find(m_points.begin(), m_points.end(), point) != m_points.end();
}
