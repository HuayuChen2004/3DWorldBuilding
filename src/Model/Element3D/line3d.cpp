// This is the implementation of the Line3D class.
// This class is used to store the 3D line.
// edit logging:
// -----------------------------------------------------------
// date: 2024/8/3
// author: Huayu Chen
// edit: add implementation of the Line3D class
// reason: to support storing the 3D line
// -----------------------------------------------------------

#include "line3d.hpp"
#include "point3d.hpp"
#include "vector.hpp"
#include <vector>
#include <stdexcept>
#include <cmath>
#include <string>

using namespace std;

Line3D::Line3D(const Point3D& point1, const Point3D& point2) : 
    FixedSizePoint3DContainer({point1, point2}) {
        if (point1 == point2) {
            throw invalid_argument("The two points are the same");
        }
    }

Line3D::Line3D(const vector<Point3D>& points) : 
            FixedSizePoint3DContainer(points) {
    if (points.size() != 2) {
        throw invalid_argument("Line3D must have 2 points");
    }
    if (points[0] == points[1]) {
        throw invalid_argument("The two points are the same");
    }
}

Line3D& Line3D::operator=(const Line3D& line) {
    if (this != &line) {
        ModifyPoint(0, line.GetPoint(0));
        ModifyPoint(1, line.GetPoint(1));
    }
    return *this;
}

Line3D::~Line3D() {}

double Line3D::Distance(const Point3D& point) const {
    Vector vector1 = GetPoint(0).ToVector();
    Vector vector2 = GetPoint(1).ToVector();
    Vector vector3 = point.ToVector();
    Vector vector4 = vector2 - vector1;
    Vector vector5 = vector3 - vector1;
    double dotProduct = vector4.Dot(vector5);
    double length = vector4.Length();
    double distance = dotProduct / length;
    return distance;
}

double Line3D::Distance(const Line3D& line) const {
    Vector vector1 = GetPoint(0).ToVector();
    Vector vector2 = GetPoint(1).ToVector();
    Vector vector3 = line.GetPoint(0).ToVector();
    Vector vector4 = line.GetPoint(1).ToVector();
    Vector vector5 = vector2 - vector1;
    Vector vector6 = vector4 - vector3;
    Vector vector7 = vector3 - vector1;
    double crossProduct1 = vector5.Cross(vector6).Length();
    double crossProduct2 = vector5.Cross(vector7).Length();
    double distance = crossProduct1 / vector5.Length();
    if (crossProduct2 != 0) {
        return distance;
    }
    return 0;
}

Point3D Line3D::Intersection(const Line3D& line) const {
    if (Distance(line) != 0) {
        throw invalid_argument("Lines are not intersected");
    }
    Vector vector1 = GetPoint(0).ToVector();
    Vector vector2 = GetPoint(1).ToVector();
    Vector vector3 = line.GetPoint(0).ToVector();
    Vector vector4 = line.GetPoint(1).ToVector();
    Vector vector5 = vector2 - vector1;
    Vector vector6 = vector4 - vector3;
    Vector vector7 = vector3 - vector1;
    double crossProduct1 = vector5.Cross(vector6).Length();
    double crossProduct2 = vector5.Cross(vector7).Length();
    double crossProduct3 = vector6.Cross(vector7).Length();
    double t1 = crossProduct1 / crossProduct3;
    double t2 = crossProduct2 / crossProduct3;
    Point3D intersection = Point3D((vector1 + vector5 * t1).GetData());
    return intersection;
}

bool Line3D::IsParallel(const Line3D& line) const {
    Vector vector1 = GetPoint(0).ToVector();
    Vector vector2 = GetPoint(1).ToVector();
    Vector vector3 = line.GetPoint(0).ToVector();
    Vector vector4 = line.GetPoint(1).ToVector();
    Vector vector5 = vector2 - vector1;
    Vector vector6 = vector4 - vector3;
    return vector5.IsParallel(vector6) && !((*this).IsCoincident(line));
}

bool Line3D::IsPerpendicular(const Line3D& line) const {
    Vector vector1 = GetPoint(0).ToVector();
    Vector vector2 = GetPoint(1).ToVector();
    Vector vector3 = line.GetPoint(0).ToVector();
    Vector vector4 = line.GetPoint(1).ToVector();
    Vector vector5 = vector2 - vector1;
    Vector vector6 = vector4 - vector3;
    return vector5.IsOrthogonal(vector6);
}

bool Line3D::IsCoincident(const Line3D& line) const {
    Vector vector1 = GetPoint(0).ToVector();
    Vector vector2 = GetPoint(1).ToVector();
    Vector vector3 = line.GetPoint(0).ToVector();
    Vector vector4 = line.GetPoint(1).ToVector();
    Vector vector5 = vector2 - vector1;
    Vector vector6 = vector4 - vector3;
    Vector vector7 = vector3 - vector1;
    return vector5.IsParallel(vector6) && vector5.IsParallel(vector7);
}

bool Line3D::IsPointOnLine(const Point3D& point) const {
    return Distance(point) == 0;
}

double Line3D::Angle(const Line3D& line) const {
    Vector vector1 = GetPoint(0).ToVector();
    Vector vector2 = GetPoint(1).ToVector();
    Vector vector3 = line.GetPoint(0).ToVector();
    Vector vector4 = line.GetPoint(1).ToVector();
    Vector vector5 = vector2 - vector1;
    Vector vector6 = vector4 - vector3;
    return vector5.AngleFrom(vector6) > 90 ? 
            180 - vector5.AngleFrom(vector6) : vector5.AngleFrom(vector6);
}

double Line3D::Angle(const Line3D& line1, const Line3D& line2) {
    return line1.Angle(line2);
}

double Line3D::Distance(const Line3D& line1, const Line3D& line2) {
    return line1.Distance(line2);
}

double Line3D::Distance(const Point3D& point, const Line3D& line) {
    return line.Distance(point);
}

Point3D Line3D::Projection(const Point3D& point, const Line3D& line) {
    Vector vector1 = line.GetPoint(0).ToVector();
    Vector vector2 = line.GetPoint(1).ToVector();
    Vector vector3 = point.ToVector();
    Vector vector4 = vector2 - vector1;
    Vector vector5 = vector3 - vector1;
    double dotProduct = vector4.Dot(vector5);
    double length = vector4.Length();
    double t = dotProduct / length / length;
    Point3D projection = Point3D((vector1 + vector4 * t).GetData());
    return projection;
}

Point3D Line3D::Intersection(const Line3D& line1, const Line3D& line2) {
    return line1.Intersection(line2);
}

bool Line3D::IsParallel(const Line3D& line1, const Line3D& line2) {
    return line1.IsParallel(line2);
}

bool Line3D::IsPerpendicular(const Line3D& line1, const Line3D& line2) {
    return line1.IsPerpendicular(line2);
}

bool Line3D::IsCoincident(const Line3D& line1, const Line3D& line2) {
    return line1.IsCoincident(line2);
}

bool Line3D::IsPointOnLine(const Point3D& point, const Line3D& line) {
    return line.IsPointOnLine(point);
}

Point3D Line3D::GetP1() const {
    return GetPoint(0);
}

Point3D Line3D::GetP2() const {
    return GetPoint(1);
}

void Line3D::SetP1(const Point3D& point) {
    ModifyPoint(0, point);
}

void Line3D::SetP2(const Point3D& point) {
    ModifyPoint(1, point);
}

double Line3D::Length() const {
    return GetP1().DistanceFrom(GetP2());
}

bool Line3D::OnSamePlane(const Line3D& line) const {
    Vector vector1 = GetP1().ToVector() - GetP2().ToVector();
    Vector vector2 = line.GetP1().ToVector() - line.GetP2().ToVector();
    Vector vector3 = GetP1().ToVector() - line.GetP1().ToVector();
    return !Vector::IsLinearIndependent(
        vector<Vector>({vector1, vector2, vector3}));
}

bool Line3D::IsSameSegment(const Line3D& line1, const Line3D& line2) {
    return line1.GetP1() == line2.GetP1() && line1.GetP2() == line2.GetP2()
        || line1.GetP1() == line2.GetP2() && line1.GetP2() == line2.GetP1();
}
