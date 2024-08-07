#include "model3d.hpp"
#include <string>
#include <vector>

using namespace std;

Model3D::Model3D(vector<Face3D> faces, vector<Line3D> lines, const string& name) {
    Faces = vector<shared_ptr<Face3D>>(faces.size());
    for (size_t i = 0; i < faces.size(); i++) {
        Faces[i] = make_shared<Face3D>(faces[i]);
    }

    Lines = vector<shared_ptr<Line3D>>(lines.size());
    for (size_t i = 0; i < lines.size(); i++) {
        Lines[i] = make_shared<Line3D>(lines[i]);
    }
    
    Name = name;
}

Model3D::~Model3D() {
    Faces.clear();
    Lines.clear();
}

Model3D& Model3D::operator=(const Model3D& model) {
    if (this == &model) {
        return *this;
    }
    
    Faces = vector<shared_ptr<Face3D>>(model.Faces.size());
    for (size_t i = 0; i < model.Faces.size(); i++) {
        Faces[i] = make_shared<Face3D>(*model.Faces[i]);
    }
    
    Lines = vector<shared_ptr<Line3D>>(model.Lines.size());
    for (size_t i = 0; i < model.Lines.size(); i++) {
        Lines[i] = make_shared<Line3D>(*model.Lines[i]);
    }
    
    Name = model.Name;
    
    return *this;
}

void Model3D::DeleteFace(unsigned int index) {
    if (index >= Faces.size()) {
        throw invalid_argument("Index out of range");
    }
    
    Faces.erase(Faces.begin() + index);
}

void Model3D::DeleteLine(unsigned int index) {
    if (index >= Lines.size()) {
        throw invalid_argument("Index out of range");
    }
    
    Lines.erase(Lines.begin() + index);
}

void Model3D::AddFace(const Face3D& face) {
    // check if there are faces that are the same
    for (const shared_ptr<Face3D>& f : Faces) {
        if (Face3D::IsSameFace(*f, face)) {
            throw invalid_argument("Face already exists");
        }
    }
    Faces.push_back(make_shared<Face3D>(face));
}

void Model3D::AddLine(const Line3D& line) {
    // check if there are lines that are the same
    for (const shared_ptr<Line3D>& l : Lines) {
        if (Line3D::IsSameSegment(*l, line)) {
            throw invalid_argument("Line already exists");
        }
    }
    Lines.push_back(make_shared<Line3D>(line));
}

void Model3D::ModifyFacePoint(unsigned int FaceIndex, 
                        unsigned int PointIndex, const Point3D& new_point) {
    if (FaceIndex >= Faces.size()) {
        throw invalid_argument("Index out of range");
    }
    Face3D NewFace = *Faces[FaceIndex];
    NewFace.ModifyPoint(PointIndex, new_point);
    if (FindFace(NewFace)) {
        throw invalid_argument("Face already exists");
    }
    Faces[FaceIndex] = make_shared<Face3D>(NewFace);
}

void Model3D::ModifyLinePoint(unsigned int LineIndex, 
                        unsigned int PointIndex, const Point3D& new_point) {
    if (LineIndex >= Lines.size()) {
        throw invalid_argument("Index out of range");
    }
    Line3D NewLine = *Lines[LineIndex];
    NewLine.ModifyPoint(PointIndex, new_point);
    if (FindLine(NewLine)) {
        throw invalid_argument("Line already exists");
    }
    Lines[LineIndex] = make_shared<Line3D>(NewLine);
}

bool Model3D::FindFace(const Face3D& face) const {
    for (const shared_ptr<Face3D>& f : Faces) {
        if (*f == face) {
            return true;
        }
    }
    return false;
}

bool Model3D::FindLine(const Line3D& line) const {
    for (const shared_ptr<Line3D>& l : Lines) {
        if (*l == line) {
            return true;
        }
    }
    return false;
}

void Model3D::ModifyName(const string& name) {
    Name = name;
}

const vector<shared_ptr<Face3D>>& Model3D::GetFaces() const {
    return Faces;
}

const vector<shared_ptr<Line3D>>& Model3D::GetLines() const {
    return Lines;
}

string Model3D::GetName() const {
    return Name;
}

vector<Point3D> Model3D::GetPoints() const {
    vector<Point3D> Points;
    for (const shared_ptr<Face3D>& face : Faces) {
        for (const Point3D& point : face->GetPoints()) {
            Points.push_back(point);
        }
    }
    for (const shared_ptr<Line3D>& line : Lines) {
        for (const Point3D& point : line->GetPoints()) {
            Points.push_back(point);
        }
    }
    return Points;
}


