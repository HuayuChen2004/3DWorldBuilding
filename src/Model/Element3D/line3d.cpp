// [file name] : line3d.cpp
// [function] : implement the Line3D class
// [author] : Huayu Chen
// [date] : 2024/8/3

// [edit history] :
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

// -----------------------------------------------------------
// [name] : Line3D
// [function] : constructor of the Line3D class
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
Line3D::Line3D() : FixedSizePoint3DContainer({Point3D(), Point3D()}) {}

// -----------------------------------------------------------
// [name] : Line3D
// [function] : constructor of the Line3D class
// [input] : const Point3D& point1, const Point3D& point2
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
Line3D::Line3D(const Point3D& point1, const Point3D& point2) : 
    FixedSizePoint3DContainer({point1, point2}) {
        // Check if the two points are the same
        if (point1 == point2) {
            throw invalid_argument("The two points are the same");
        }
    }

// -----------------------------------------------------------
// [name] : Line3D
// [function] : constructor of the Line3D class
// [input] : a vector of Point3D
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
Line3D::Line3D(const vector<Point3D>& points) : 
            FixedSizePoint3DContainer(points) {
    // Check if the number of points is not 2
    if (points.size() != 2) {
        throw invalid_argument("Line3D must have 2 points");
    }
    // Check if the two points are the same
    if (points[0] == points[1]) {
        throw invalid_argument("The two points are the same");
    }
}

// -----------------------------------------------------------
// [name] : operator=
// [function] : assignment operator of the Line3D class
// [input] : a Line3D object
// [output] : the reference of the assigned Line3D object
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
Line3D& Line3D::operator=(const Line3D& line) {
    // Check if the two lines are the same
    if (this != &line) {
        ModifyPoint(0, line.GetPoint(0));
        ModifyPoint(1, line.GetPoint(1));
    }
    return *this;
}

// -----------------------------------------------------------
// [name] : ~Line3D
// [function] : destructor of the Line3D class
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
Line3D::~Line3D() {}

// -----------------------------------------------------------
// [name] : Distance
// [function] : calculate the distance between the line and a point
// [input] : a Point3D object
// [output] : a double value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
double Line3D::Distance(const Point3D& point) const {
    // Get the vectors for the points on the line and the target point
    Vector vector1 = GetPoint(0).ToVector();
    Vector vector2 = GetPoint(1).ToVector();
    Vector vector3 = point.ToVector();
    // Vector from the first point on the line to the second point on the line (direction vector)
    Vector direction = vector2 - vector1;
    // Vector from the first point on the line to the point in question
    Vector toPoint = vector3 - vector1;
    // Compute the cross product of the direction vector and toPoint vector
    Vector crossProduct = direction.Cross(toPoint);
    // Calculate the magnitude of the cross product vector and the direction vector
    double crossProductLength = crossProduct.Length();
    double directionLength = direction.Length();
    // Distance from the point to the line
    double distance = crossProductLength / directionLength;
    return distance;
}


// -----------------------------------------------------------
// [name] : Distance
// [function] : calculate the distance between the line and another line
// [input] : a Line3D object
// [output] : a double value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
double Line3D::Distance(const Line3D& line) const {
    // Get the vectors for the points on the two lines
    Vector vector1 = GetPoint(0).ToVector();
    Vector vector2 = GetPoint(1).ToVector();
    Vector vector3 = line.GetPoint(0).ToVector();
    Vector vector4 = line.GetPoint(1).ToVector();
    // Vector from the first point on the first line to the 
    // second point on the first line 
    Vector vector5 = vector2 - vector1;
    Vector vector6 = vector4 - vector3;
    Vector vector7 = vector3 - vector1;
    // Calculate the cross product of the two direction vectors
    // and the third direction vector
    double crossProduct1 = vector5.Cross(vector6).Length();
    double crossProduct2 = vector5.Cross(vector7).Length();
    double distance = crossProduct1 / vector5.Length();
    // Check if the two lines are parallel
    if (crossProduct2 != 0) {
        return distance;
    }
    return 0;
}

// -----------------------------------------------------------
// [name] : Intersection
// [function] : find the intersection point between the line and another line
// [input] : a Line3D object
// [output] : a Point3D object
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
Point3D Line3D::Intersection(const Line3D& line) const {
    // Check if the two lines are not intersected
    if (Distance(line) != 0) {
        throw invalid_argument("Lines are not intersected");
    }
    // Get the vectors for the points on the two lines
    Vector vector1 = GetPoint(0).ToVector();
    Vector vector2 = GetPoint(1).ToVector();
    Vector vector3 = line.GetPoint(0).ToVector();
    Vector vector4 = line.GetPoint(1).ToVector();
    // Vector from the first point on the first line to the 
    // second point on the first line
    Vector vector5 = vector2 - vector1;
    Vector vector6 = vector4 - vector3;
    Vector vector7 = vector3 - vector1;
    // Calculate the cross product of the two direction vectors
    // and the third direction vector
    double crossProduct1 = vector5.Cross(vector6).Length();
    double crossProduct2 = vector5.Cross(vector7).Length();
    double crossProduct3 = vector6.Cross(vector7).Length();
    // Calculate the intersection point
    double t1 = crossProduct1 / crossProduct3;
    double t2 = crossProduct2 / crossProduct3;
    Point3D intersection = Point3D((vector1 + vector5 * t1).GetData());
    return intersection;
}

// -----------------------------------------------------------
// [name] : IsParallel
// [function] : check if the line is parallel to another line
// [input] : a Line3D object
// [output] : a bool value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
bool Line3D::IsParallel(const Line3D& line) const {
    // Get the vectors for the points on the two lines
    Vector vector1 = GetPoint(0).ToVector();
    Vector vector2 = GetPoint(1).ToVector();
    Vector vector3 = line.GetPoint(0).ToVector();
    Vector vector4 = line.GetPoint(1).ToVector();
    // Vector from the first point on the first line to the 
    // second point on the first line
    Vector vector5 = vector2 - vector1;
    Vector vector6 = vector4 - vector3;
    // Check if the two lines are parallel
    return vector5.IsParallel(vector6) && !((*this).IsCoincidentTo(line));
}

// -----------------------------------------------------------
// [name] : IsPerpendicular
// [function] : check if the line is perpendicular to another line
// [input] : a Line3D object
// [output] : a bool value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
bool Line3D::IsPerpendicular(const Line3D& line) const {
    // Get the vectors for the points on the two lines
    Vector vector1 = GetPoint(0).ToVector();
    Vector vector2 = GetPoint(1).ToVector();
    Vector vector3 = line.GetPoint(0).ToVector();
    Vector vector4 = line.GetPoint(1).ToVector();
    // Vector from the first point on the first line to the 
    // second point on the first line
    Vector vector5 = vector2 - vector1;
    Vector vector6 = vector4 - vector3;
    return vector5.IsOrthogonal(vector6);
}

// -----------------------------------------------------------
// [name] : IsCoincidentTo
// [function] : check if the line is coincident with another line
// [input] : a Line3D object
// [output] : a bool value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
bool Line3D::IsCoincidentTo(const Line3D& line) const {
    // Get the vectors for the points on the two lines
    Vector vector1 = GetPoint(0).ToVector();
    Vector vector2 = GetPoint(1).ToVector();
    Vector vector3 = line.GetPoint(0).ToVector();
    Vector vector4 = line.GetPoint(1).ToVector();
    // Vector from the first point on the first line to the 
    // second point on the first line
    Vector vector5 = vector2 - vector1;
    Vector vector6 = vector4 - vector3;
    Vector vector7 = vector3 - vector1;
    // if the two vectors are parallel and the vector from the first point
    // on the first line to the first point on the second line is parallel to
    // the two vectors, then the two lines are coincident
    return vector5.IsParallel(vector6) && vector5.IsParallel(vector7);
}

// -----------------------------------------------------------
// [name] : IsPointOnLine
// [function] : check if a point is on the line
// [input] : a Point3D object
// [output] : a bool value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
bool Line3D::IsPointOnLine(const Point3D& point) const {
    return fabs(Distance(point)) < 1e-6;
}

// -----------------------------------------------------------
// [name] : Angle
// [function] : calculate the angle between the line and another line
// [input] : a Line3D object
// [output] : a double value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
double Line3D::AngleFrom(const Line3D& line) const {
    // Get the vectors for the points on the two lines
    Vector vector1 = GetPoint(0).ToVector();
    Vector vector2 = GetPoint(1).ToVector();
    Vector vector3 = line.GetPoint(0).ToVector();
    Vector vector4 = line.GetPoint(1).ToVector();
    // Vector from the first point on the first line to the 
    // second point on the first line
    Vector vector5 = vector2 - vector1;
    Vector vector6 = vector4 - vector3;
    // Calculate the angle between the two lines
    // if the angle is greater than 90 degrees, return 180 - angle
    return vector5.AngleFrom(vector6) > 90 ? 
            180 - vector5.AngleFrom(vector6) : vector5.AngleFrom(vector6);
}

// -----------------------------------------------------------
// [name] : Angle
// [function] : calculate the angle between two lines
// [input] : two Line3D objects
// [output] : a double value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
double Line3D::Angle(const Line3D& line1, const Line3D& line2) {
    return line1.AngleFrom(line2);
}

// -----------------------------------------------------------
// [name] : Distance
// [function] : calculate the distance between two lines
// [input] : two Line3D objects
// [output] : a double value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
double Line3D::Distance(const Line3D& line1, const Line3D& line2) {
    return line1.Distance(line2);
}

// -----------------------------------------------------------
// [name] : Distance
// [function] : calculate the distance between a point and a line
// [input] : a Point3D object, a Line3D object
// [output] : a double value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
double Line3D::Distance(const Point3D& point, const Line3D& line) {
    return line.Distance(point);
}

// -----------------------------------------------------------
// [name] : Projection
// [function] : calculate the projection of a point on a line
// [input] : a Point3D object, a Line3D object
// [output] : a Point3D object
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
Point3D Line3D::Projection(const Point3D& point, const Line3D& line) {
    // Get the vectors for the points on the line and the target point
    Vector vector1 = line.GetPoint(0).ToVector();
    Vector vector2 = line.GetPoint(1).ToVector();
    Vector vector3 = point.ToVector();
    // Vector from the first point on the line to the second point on the line
    Vector vector4 = vector2 - vector1;
    Vector vector5 = vector3 - vector1;
    // Calculate the projection of the point on the line
    double dotProduct = vector4.Dot(vector5);
    double length = vector4.Length();
    double t = dotProduct / length / length;
    Point3D projection = Point3D((vector1 + vector4 * t).GetData());
    return projection;
}

// -----------------------------------------------------------
// [name] : Intersection
// [function] : find the intersection point between two lines
// [input] : two Line3D objects
// [output] : a Point3D object
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
Point3D Line3D::Intersection(const Line3D& line1, const Line3D& line2) {
    return line1.Intersection(line2);
}

// -----------------------------------------------------------
// [name] : IsParallel
// [function] : check if two lines are parallel
// [input] : two Line3D objects
// [output] : a bool value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
bool Line3D::IsParallel(const Line3D& line1, const Line3D& line2) {
    return line1.IsParallel(line2);
}

// -----------------------------------------------------------
// [name] : IsPerpendicular
// [function] : check if two lines are perpendicular
// [input] : two Line3D objects
// [output] : a bool value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
bool Line3D::IsPerpendicular(const Line3D& line1, const Line3D& line2) {
    return line1.IsPerpendicular(line2);
}

// -----------------------------------------------------------
// [name] : IsCoincident
// [function] : check if two lines are coincident
// [input] : two Line3D objects
// [output] : a bool value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
bool Line3D::IsCoincident(const Line3D& line1, const Line3D& line2) {
    return line1.IsCoincidentTo(line2);
}

// -----------------------------------------------------------
// [name] : IsPointOnLine
// [function] : check if a point is on a line
// [input] : a Point3D object, a Line3D object
// [output] : a bool value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
bool Line3D::IsPointOnLine(const Point3D& point, const Line3D& line) {
    return line.IsPointOnLine(point);
}

// -----------------------------------------------------------
// [name] : GetP1
// [function] : get the first point of the line
// [input] : none
// [output] : a Point3D object
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
Point3D Line3D::GetP1() const {
    return GetPoint(0);
}

// -----------------------------------------------------------
// [name] : GetP2
// [function] : get the second point of the line
// [input] : none
// [output] : a Point3D object
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
Point3D Line3D::GetP2() const {
    return GetPoint(1);
}

// -----------------------------------------------------------
// [name] : SetP1
// [function] : set the first point of the line
// [input] : a Point3D object
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
void Line3D::SetP1(const Point3D& point) {
    ModifyPoint(0, point);
}

// -----------------------------------------------------------
// [name] : SetP2
// [function] : set the second point of the line
// [input] : a Point3D object
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
void Line3D::SetP2(const Point3D& point) {
    ModifyPoint(1, point);
}

// -----------------------------------------------------------
// [name] : Length
// [function] : calculate the length of the line
// [input] : none
// [output] : a double value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
double Line3D::Length() const {
    return GetP1().DistanceFrom(GetP2());
}

// -----------------------------------------------------------
// [name] : OnSamePlane
// [function] : check if the line and another line lie on the same plane
// [input] : a Line3D object
// [output] : a bool value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
bool Line3D::OnSamePlane(const Line3D& line) const {
    // Get the vectors for the points on the two lines
    Vector vector1 = GetP1().ToVector() - GetP2().ToVector();
    Vector vector2 = line.GetP1().ToVector() - line.GetP2().ToVector();
    Vector vector3 = GetP1().ToVector() - line.GetP1().ToVector();
    // Check if the three vectors are linearly dependent
    // if they are linearly dependent, the two lines lie on the same plane
    return !Vector::IsLinearIndependent(
        vector<Vector>({vector1, vector2, vector3}));
}

// -----------------------------------------------------------
// [name] : IsSameSegment
// [function] : check if two line segments are the same
// [input] : two Line3D objects
// [output] : a bool value
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
bool Line3D::IsSameSegment(const Line3D& line1, const Line3D& line2) {
    // if the two lines have the same two points, they are the same line segment
    return line1.GetP1() == line2.GetP1() && line1.GetP2() == line2.GetP2()
        || line1.GetP1() == line2.GetP2() && line1.GetP2() == line2.GetP1();
}
