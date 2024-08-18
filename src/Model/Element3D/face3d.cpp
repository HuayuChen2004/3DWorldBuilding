// [file name] : face3d.cpp
// [function] : implement the Face3D class
// [author] : Huayu Chen
// [date] : 2024/8/4

// [edit history] :
// -----------------------------------------------------------
// date: 2024/8/4
// author: Huayu Chen
// edit: add implementation of the Face3D class
// reason: to support storing the 3D face
// -----------------------------------------------------------

#include "face3d.hpp"
#include "line3d.hpp"
#include "point3d.hpp"
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

// -----------------------------------------------------------
// [name] : Face3D
// [function] : constructor of the Face3D class
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Face3D::Face3D() : FixedSizePoint3DContainer(
                        {Point3D(), Point3D(), Point3D()}) {}


// -----------------------------------------------------------
// [name] : Face3D
// [function] : constructor of the Face3D class
// [input] : three points of class Point3D
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Face3D::Face3D(const Point3D& point1, const Point3D& point2, 
             const Point3D& point3) : 
    FixedSizePoint3DContainer({point1, point2, point3}) {
        // check if the three points are distinct
    if (point1 == point2 || point1 == point3 || point2 == point3) {
        throw invalid_argument("The three points are not distinct");
    }
}

// -----------------------------------------------------------
// [name] : ~Face3D
// [function] : destructor of the Face3D class
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Face3D::~Face3D() {}

// -----------------------------------------------------------
// [name] : Face3D
// [function] : constructor of the Face3D class
// [input] : a point and a line
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Face3D::Face3D(const Point3D& point, const Line3D& line) : 
    FixedSizePoint3DContainer({point, line.GetPoint(0), line.GetPoint(1)}) {
        // check if the point is on the line
    if (line.IsPointOnLine(point)) {
        throw invalid_argument("The point is on the line");
    }
}

// -----------------------------------------------------------
// [name] : Face3D
// [function] : constructor of the Face3D class
// [input] : two lines
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Face3D::Face3D(const Line3D& line1, const Line3D& line2) : 
    FixedSizePoint3DContainer({line1.GetPoint(0), line1.GetPoint(1), 
                               line2.GetPoint(1)}) {
    // check if the two lines are on the same plane
    if (!line1.OnSamePlane(line2)) {
        throw invalid_argument("The two lines are not on the same plane");
    }
    // check if the two lines are coincident
    if (line1.IsCoincidentTo(line2)) {
        throw invalid_argument("The two lines are coincident");
    }
    // check if the two lines have a common point
    if (line2.GetPoint(1) == line1.GetPoint(0) || 
        line2.GetPoint(1) == line1.GetPoint(1)) {
        ModifyPoint(2, line2.GetPoint(0));
    }
}

// -----------------------------------------------------------
// [name] : Face3D
// [function] : constructor of the Face3D class
// [input] : a vector of points
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Face3D::Face3D(const vector<Point3D>& points) : 
    FixedSizePoint3DContainer(points) {
    // check if the number of points is 3
    if (points.size() != 3) {
        throw invalid_argument("Face3D must have 3 points");
    }
    // check if the three points are distinct
    if (points[0] == points[1] || points[0] == points[2] || 
        points[1] == points[2]) {
        throw invalid_argument("The three points are not distinct");
    }
}

// -----------------------------------------------------------
// [name] : operator=
// [function] : assignment operator of the Face3D class
// [input] : a Face3D object
// [output] : a Face3D object
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Face3D& Face3D::operator=(const Face3D& face) {
    // check if the two faces are the same
    if (this != &face) {
        ModifyPoint(0, face.GetPoint(0));
        ModifyPoint(1, face.GetPoint(1));
        ModifyPoint(2, face.GetPoint(2));
    }
    return *this;
}

// -----------------------------------------------------------
// [name] : PerpendicularLine
// [function] : get the perpendicular line of the face
// [input] : none
// [output] : a Line3D object
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Line3D Face3D::PerpendicularLine() const {
    // get the normal vector of the face
    // the normal vector is the cross product of two vectors on the face
    // the two vectors are the two edges of the face
    Vector vector1 = GetPoint(0).ToVector();
    Vector vector2 = GetPoint(1).ToVector();
    Vector vector3 = GetPoint(2).ToVector();
    Vector vector4 = vector2 - vector1;
    Vector vector5 = vector3 - vector1;
    Vector normal = vector4.Cross(vector5);
    Point3D point = GetPoint(0);
    // the perpendicular line is defined by the normal vector 
    // and a point on the face
    try {
        Line3D line(point, Point3D((point.ToVector() + normal).GetData()));
        return line;
    }
    catch (exception& e) {
        throw e;
    }
}

// -----------------------------------------------------------
// [name] : IsParallel
// [function] : check if the face is parallel to another face
// [input] : a Face3D object
// [output] : a bool value
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
bool Face3D::IsParallel(const Face3D& face) const {
    // check if the two faces are parallel
    // the two faces are parallel if the normal vectors 
    // of the faces are parallel
    Line3D line1 = PerpendicularLine();
    Line3D line2 = face.PerpendicularLine();
    return line1.IsParallel(line2) && !IsCoincidentTo(face);
}

// -----------------------------------------------------------
// [name] : IsPerpendicular
// [function] : check if the face is perpendicular to another face
// [input] : a Face3D object
// [output] : a bool value
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
bool Face3D::IsPerpendicular(const Face3D& face) const {
    // check if the two faces are perpendicular
    // the two faces are perpendicular if the normal vectors
    // of the faces are perpendicular
    Line3D line1 = PerpendicularLine();
    Line3D line2 = face.PerpendicularLine();
    return line1.IsPerpendicular(line2);
}

// -----------------------------------------------------------
// [name] : IsCoincidentTo
// [function] : check if the face is coincident to another face
// [input] : a Face3D object
// [output] : a bool value
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
bool Face3D::IsCoincidentTo(const Face3D& face) const {
    // check if the two faces are coincident
    // the two faces are coincident if they are on the same plane
    return face.IsPointOnFacePlane(GetPoint(0)) && 
           face.IsPointOnFacePlane(GetPoint(1)) && 
           face.IsPointOnFacePlane(GetPoint(2));
}

// -----------------------------------------------------------
// [name] : IsPointOnFacePlane
// [function] : check if a point is on the face plane
// [input] : a Point3D object
// [output] : a bool value
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
bool Face3D::IsPointOnFacePlane(const Point3D& point) const {
    Vector vector1 = GetPoint(0).ToVector() - point.ToVector();
    Vector vector2 = GetPoint(1).ToVector() - point.ToVector();
    Vector vector3 = GetPoint(2).ToVector() - point.ToVector();
    // check if the three vectors are linearly dependent
    // if they are linearly dependent, the point is on the face plane
    if (!Vector::IsLinearIndependent(
            vector<Vector>({vector1, vector2, vector3}))) {
        return true;
    }
    return false;
}

// -----------------------------------------------------------
// [name] : Angle
// [function] : get the angle between two faces
// [input] : a Face3D object
// [output] : a double value
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Face3D::Angle(const Face3D& face) const {
    // the angle between two faces is the angle between the normal vectors
    // of the faces
    Line3D line1 = PerpendicularLine();
    Line3D line2 = face.PerpendicularLine();
    return line1.AngleFrom(line2);
}

// -----------------------------------------------------------
// [name] : Distance
// [function] : get the distance between two faces
// [input] : a Face3D object
// [output] : a double value
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Face3D::Distance(const Face3D& face) const {
    // the distance between two faces is the distance between the two points
    // on the faces that are perpendicular to each other
    // check if the two faces are coincident
    if (IsCoincidentTo(face)) {
        return 0;
    }
    // check if the two faces are parallel
    if (!IsParallel(face)) {
        throw invalid_argument("The two faces are not parallel");
    }
    Point3D PerpendicularPoint1 = PerpendicularLine().GetPoint(0);
    Point3D PerpendicularPoint2 = PerpendicularLine().GetPoint(1);
    // the normal vector of the face is the vector between the two points
    // on the face that are perpendicular to each other
    Vector normal = PerpendicularPoint1.ToVector() - 
                    PerpendicularPoint2.ToVector();
    Point3D PointOnPlane1 = GetPoint(0);
    Point3D PointOnPlane2 = face.GetPoint(0);
    // the distance is the projection of the vector between the two points
    // on the face plane onto the normal vector of the face
    Vector crossPlane = PointOnPlane1.ToVector() - PointOnPlane2.ToVector();
    return crossPlane.Dot(normal) / normal.Norm();
}

// -----------------------------------------------------------
// [name] : Distance
// [function] : get the distance between a face and a point
// [input] : a Point3D object
// [output] : a double value
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Face3D::Distance(const Point3D& point) const {
    // the distance between a face and a point is the projection of the vector
    // between the point and the face plane onto the normal vector of the face

    // check if the point is on the face plane
    if (IsPointOnFacePlane(point)) {
        return 0;
    }
    Line3D line = PerpendicularLine();
    Point3D PerpendicularPoint1 = line.GetPoint(0);
    Point3D PerpendicularPoint2 = line.GetPoint(1);
    // the normal vector of the face is the vector between the two points
    // on the face that are perpendicular to each other
    Vector normal = PerpendicularPoint1.ToVector() - 
                    PerpendicularPoint2.ToVector();
    // the distance is the projection of the vector between the point and the
    // face plane onto the normal vector of the face
    
    // the vector between the point and the face plane is the vector between
    // the point and the first point of the face
    Vector crossPlane = GetPoint(0).ToVector() - point.ToVector();
    return crossPlane.Dot(normal) / normal.Norm();
}

// -----------------------------------------------------------
// [name] : IsParallel
// [function] : check if the face is parallel to a line
// [input] : a Line3D object
// [output] : a bool value
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
bool Face3D::IsParallel(const Line3D& line) const {
    Line3D normal = PerpendicularLine();
    // the face is parallel to the line if the normal vector of the face
    // is perpendicular to the line and the line is not on the face plane
    return normal.IsPerpendicular(line) && 
            !IsPointOnFacePlane(line.GetPoint(0));
}

// -----------------------------------------------------------
// [name] : Distance
// [function] : get the distance between a face and a line
// [input] : a Line3D object
// [output] : a double value
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Face3D::Distance(const Line3D& line) const {
    // the distance between a face and a line is the projection of the vector
    // between the line and the face plane onto the normal vector of the face
    // check if the line is parallel to the face
    if (!IsParallel(line)) {
        throw invalid_argument("The line is not parallel to the face");
    }
    Point3D PerpendicularPoint1 = PerpendicularLine().GetPoint(0);
    Point3D PerpendicularPoint2 = PerpendicularLine().GetPoint(1);
    // the normal vector of the face is the vector between the two points
    // on the face that are perpendicular to each other
    Vector normal = PerpendicularPoint1.ToVector() - 
                    PerpendicularPoint2.ToVector();
    Point3D PointOnPlane1 = GetPoint(0);
    Point3D PointOnPlane2 = line.GetPoint(0);
    // the distance is the projection of the vector between the line and the
    // face plane onto the normal vector of the face
    Vector crossPlane = PointOnPlane1.ToVector() - PointOnPlane2.ToVector();
    return crossPlane.Dot(normal) / normal.Norm();
}

// -----------------------------------------------------------
// [name] : Area
// [function] : get the area of the face defined by the three points
// [input] : none
// [output] : a double value
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Face3D::Area() const {
    // the area of the face is the half of the cross product of two vectors
    // on the face
    Vector vector1 = GetPoint(0).ToVector();
    Vector vector2 = GetPoint(1).ToVector();
    Vector vector3 = GetPoint(2).ToVector();
    Vector vector4 = vector2 - vector1;
    Vector vector5 = vector3 - vector1;
    return 0.5 * vector4.Cross(vector5).Norm();
}

// -----------------------------------------------------------
// [name] : IsSameFace
// [function] : check if two faces are the same 
//              in that the three points are the same
// [input] : two Face3D objects
// [output] : a bool value
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
bool Face3D::IsSameFace(const Face3D& face1, const Face3D& face2) {
    vector<Point3D> points1 = face1.GetPoints();
    vector<Point3D> points2 = face2.GetPoints();
    // check if the two faces have the same three points
    for (const Point3D& point : points1) {
        if (find(points2.begin(), points2.end(), point) == points2.end()) {
            return false;
        }
    }
    return true;
}