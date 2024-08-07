// This is the implementation of the FixedSizePoint3DContainer class.
// This class is used to store a fixed size container of 3D points.
// edit logging:
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

FixedSizePoint3DContainer::FixedSizePoint3DContainer(
            const vector<Point3D>& points) : m_points(points) {
    m_uiSize = points.size();
}

FixedSizePoint3DContainer::FixedSizePoint3DContainer(
            const FixedSizePoint3DContainer& container) : 
    m_points(container.m_points) {
    m_uiSize = container.m_uiSize;
}

vector<Point3D> FixedSizePoint3DContainer::GetPoints() const {
    vector<Point3D> pointsCopy = m_points;
    return pointsCopy;
}

Point3D FixedSizePoint3DContainer::GetPoint(unsigned int index) const {
    Point3D point = m_points.at(index);
    return point;
}

void FixedSizePoint3DContainer::ModifyPoint(unsigned int index, 
            const Point3D& point) {
    if (index >= m_uiSize) {
        throw invalid_argument("Index out of range");
    }
    if (find(m_points.begin(), m_points.end(), point) != m_points.end()) {
        throw invalid_argument("Point already exists in the container.");
    }
    m_points.at(index) = point;
}

vector<string> FixedSizePoint3DContainer::ToStrings() const {
    vector<string> pointStrings;
    for (const Point3D& point : m_points) {
        pointStrings.push_back(point.ToString());
    }
    return pointStrings;
}

ostream& FixedSizePoint3DContainer::operator<<(ostream& os) const {
    for (const Point3D& point : m_points) {
        os << point << " ";
    }
    return os;
}

bool FixedSizePoint3DContainer::operator==(
            const FixedSizePoint3DContainer& container) const {
    return m_points == container.m_points;
}

bool FixedSizePoint3DContainer::operator!=(const FixedSizePoint3DContainer& 
            container) const {
    return m_points != container.m_points;
}

vector<Point3D> FixedSizePoint3DContainer::StringsToPoints(
            const vector<string>& pointStrings) {
    vector<Point3D> points;
    for (const string& pointString : pointStrings) {
        points.push_back(StringToPoint(pointString));
    }
    return points;
}

Point3D FixedSizePoint3DContainer::StringToPoint(const string& pointString) {
    vector<double> numbers;
    string trimmedInput = pointString;

    // 去除前后的括号和空格
    trimmedInput.erase(trimmedInput.begin(), find_if(trimmedInput.begin(), 
        trimmedInput.end(), [](unsigned char ch) {  
        return !isspace(ch) && ch != '(';
    }));
    trimmedInput.erase(find_if(trimmedInput.rbegin(), trimmedInput.rend(), 
            [](unsigned char ch) {
        return !isspace(ch) && ch != ')';
    }).base(), trimmedInput.end());

    // 使用正则表达式匹配数字
    regex re("\\s*([-+]?[0-9]*\\.?[0-9]+)\\s*");
    auto begin = sregex_iterator(trimmedInput.begin(), trimmedInput.end(), re);
    auto end = sregex_iterator();

    for (sregex_iterator i = begin; i != end; ++i) {
        smatch match = *i;
        try {
            double num = stod(match.str());
            numbers.push_back(num);
        } catch (const invalid_argument& e) {
            throw invalid_argument("Invalid number format.");
        }
    }

    // 检查是否正好有三个数字
    if (numbers.size() != 3) {
        throw invalid_argument("Exactly three numbers are required.");
    }

    return Point3D(numbers[0], numbers[1], numbers[2]);
}

FixedSizePoint3DContainer::~FixedSizePoint3DContainer() {
    m_points.clear();
}

ostream& operator<<(ostream& os, const FixedSizePoint3DContainer& container) {
    return container.operator<<(os);
}

bool FixedSizePoint3DContainer::IsPoint3DInContainer(
            const Point3D& point) const {
    return find(m_points.begin(), m_points.end(), point) != m_points.end();
}
