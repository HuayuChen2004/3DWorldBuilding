// This is the implementation of the Face3D class.
// This class is used to store the 3D face.
// edit logging:
// -----------------------------------------------------------
// date: 2024/8/4
// author: Huayu Chen
// edit: add implementation of the Face3D class
// reason: to support storing the 3D face
// -----------------------------------------------------------

#include "face3d.hpp"
#include "line3d.hpp"
#include "point3d.hpp"

using namespace std;

Face3D::Face3D(const Point3D& point1, const Point3D& point2, 
             const Point3D& point3) : 
    FixedSizePoint3DContainer({point1, point2, point3}) {}

Face3D::Face3D(const Point3D& point, const Line3D& line) : 
    FixedSizePoint3DContainer({point, line.GetPoint(0), line.GetPoint(1)}) {}

Face3D::Face3D(const Line3D& line1, const Line3D& line2) : 
    FixedSizePoint3DContainer({line1.GetPoint(0), line1.GetPoint(1), 
                               line2.GetPoint(1)}) {
    if (!line1.OnSamePlane(line2)) {
        throw invalid_argument("The two lines are not on the same plane");
    }
    if (line1.IsCoincident(line2)) {
        throw invalid_argument("The two lines are coincident");
    }
    if (line2.GetPoint(1) == line1.GetPoint(0) || 
        line2.GetPoint(1) == line1.GetPoint(1)) {
        ModifyPoint(2, line2.GetPoint(0));
    }
}

Face3D::Face3D(const Face3D& face) : 
    FixedSizePoint3DContainer(face.GetPoints()) {}

Face3D& Face3D::operator=(const Face3D& face) {
    if (this != &face) {
        ModifyPoint(0, face.GetPoint(0));
        ModifyPoint(1, face.GetPoint(1));
        ModifyPoint(2, face.GetPoint(2));
    }
    return *this;
}

bool Face3D::operator==(const Face3D& face) const {
    return GetPoint(0) == face.GetPoint(0) &&
           GetPoint(1) == face.GetPoint(1) &&
           GetPoint(2) == face.GetPoint(2);
}

bool Face3D::operator!=(const Face3D& face) const {
    return !(*this == face);
}

Line3D Face3D::PerpendicularLine() const {
    Vector vector1 = GetPoint(0).ToVector();
    Vector vector2 = GetPoint(1).ToVector();
    Vector vector3 = GetPoint(2).ToVector();
    Vector vector4 = vector2 - vector1;
    Vector vector5 = vector3 - vector1;
    Vector normal = vector4.Cross(vector5);
    Point3D point = GetPoint(0);
    try {
        Line3D line(point, Point3D((point.ToVector() + normal).GetData()));
        return line;
    }
    catch (exception& e) {
        throw e;
    }
}

bool Face3D::IsParallel(const Face3D& face) const {
    Line3D line1 = PerpendicularLine();
    Line3D line2 = face.PerpendicularLine();
    return line1.IsParallel(line2) && !IsCoincident(face);
}

bool Face3D::IsPerpendicular(const Face3D& face) const {
    Line3D line1 = PerpendicularLine();
    Line3D line2 = face.PerpendicularLine();
    return line1.IsPerpendicular(line2);
}

bool Face3D::IsCoincident(const Face3D& face) const {
    return face.IsPointOnFace(GetPoint(0)) && 
           face.IsPointOnFace(GetPoint(1)) && 
           face.IsPointOnFace(GetPoint(2));
}

bool Face3D::IsPointOnFace(const Point3D& point) const {
    Vector vector1 = GetPoint(0).ToVector() - point.ToVector();
    Vector vector2 = GetPoint(1).ToVector() - point.ToVector();
    Vector vector3 = GetPoint(2).ToVector() - point.ToVector();
    if (!Vector::IsLinearIndependent(
            vector<Vector>({vector1, vector2, vector3}))) {
        return true;
    }
    return false;
}

double Face3D::Angle(const Face3D& face) const {
    Line3D line1 = PerpendicularLine();
    Line3D line2 = face.PerpendicularLine();
    return line1.Angle(line2);
}

double Face3D::Distance(const Face3D& face) const {
    if (IsCoincident(face)) {
        return 0;
    }
    if (!IsParallel(face)) {
        throw invalid_argument("The two faces are not parallel");
    }
