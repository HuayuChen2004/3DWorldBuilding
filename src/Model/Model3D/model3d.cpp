// [file name] : model3d.cpp
// [function] : implement the Model3D class
// [author] : Huayu Chen
// [date] : 2024/8/6

// [edit history] :
// -----------------------------------------------------------
// date: 2024/8/6
// author: Huayu Chen
// edit: add implementation of the Model3D class
// reason: to support storing 3D models
// -----------------------------------------------------------


#include "model3d.hpp"
#include <string>
#include <vector>
#include <iostream> // debugging

using namespace std;

// -----------------------------------------------------------
// [name] : Model3D
// [function] : constructor for Model3D class
// [input] : a vector of Face3D objects, a vector of Line3D objects, and a string for name
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/6
// -----------------------------------------------------------
Model3D::Model3D(vector<Face3D> faces, vector<Line3D> lines, const string& name) {
    Faces = vector<shared_ptr<Face3D>>(faces.size());
    // make shared pointers to the faces
    for (size_t i = 0; i < faces.size(); i++) {
        Faces[i] = make_shared<Face3D>(faces[i]);
    }
    // make shared pointers to the lines
    Lines = vector<shared_ptr<Line3D>>(lines.size());
    for (size_t i = 0; i < lines.size(); i++) {
        Lines[i] = make_shared<Line3D>(lines[i]);
    }
    // set the name
    Name = name;
}

// -----------------------------------------------------------
// [name] : Model3D
// [function] : default constructor for Model3D class
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/6
// -----------------------------------------------------------
Model3D::Model3D() {
    // initialize the faces, lines, and name vectors
    Faces = vector<shared_ptr<Face3D>>();
    Lines = vector<shared_ptr<Line3D>>();
    Name = "";
}

// -----------------------------------------------------------
// [name] : Model3D
// [function] : copy constructor for Model3D class
// [input] : a constant reference to another Model3D object
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/6
// -----------------------------------------------------------
Model3D::Model3D(const Model3D& model) {
    // copy the faces 
    Faces = vector<shared_ptr<Face3D>>(model.Faces.size());
    for (size_t i = 0; i < model.Faces.size(); i++) {
        Faces[i] = make_shared<Face3D>(*model.Faces[i]);
    }
    // copy the lines
    Lines = vector<shared_ptr<Line3D>>(model.Lines.size());
    for (size_t i = 0; i < model.Lines.size(); i++) {
        Lines[i] = make_shared<Line3D>(*model.Lines[i]);
    }
    // copy the name
    Name = model.Name;
}

// -----------------------------------------------------------
// [name] : ~Model3D
// [function] : destructor for Model3D class
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/6
// -----------------------------------------------------------
Model3D::~Model3D() {
    Faces.clear();
    Lines.clear();
}

// -----------------------------------------------------------
// [name] : operator=
// [function] : assignment operator for Model3D class
// [input] : a constant reference to another Model3D object
// [output] : a reference to the current Model3D object
// [author] : Huayu Chen
// [date] : 2024/8/6
// -----------------------------------------------------------
Model3D& Model3D::operator=(const Model3D& model) {
    // check if the current object is the same as the input object
    if (this == &model) {
        return *this;
    }
    // make shared pointers to the faces
    Faces = vector<shared_ptr<Face3D>>(model.Faces.size());
    for (size_t i = 0; i < model.Faces.size(); i++) {
        Faces[i] = make_shared<Face3D>(*model.Faces[i]);
    }
    // make shared pointers to the lines
    Lines = vector<shared_ptr<Line3D>>(model.Lines.size());
    for (size_t i = 0; i < model.Lines.size(); i++) {
        Lines[i] = make_shared<Line3D>(*model.Lines[i]);
    }
    // copy the name
    Name = model.Name;
    return *this;
}

// -----------------------------------------------------------
// [name] : DeleteFace
// [function] : deletes a face at a specified index
// [input] : an unsigned integer representing the index
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/6
// -----------------------------------------------------------
void Model3D::DeleteFace(unsigned int index) {
    // check if the index is out of range
    if (index >= Faces.size()) {
        throw invalid_argument("Index out of range");
    }
    // delete the face at the specified index
    Faces.erase(Faces.begin() + index);
}

// -----------------------------------------------------------
// [name] : DeleteLine
// [function] : deletes a line at a specified index
// [input] : an unsigned integer representing the index
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/6
// -----------------------------------------------------------
void Model3D::DeleteLine(unsigned int index) {
    // check if the index is out of range
    if (index >= Lines.size()) {
        throw invalid_argument("Index out of range");
    }
    // delete the line at the specified index
    Lines.erase(Lines.begin() + index);
}

// -----------------------------------------------------------
// [name] : AddFace
// [function] : adds a new face to the model
// [input] : a constant reference to a Face3D object
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/6
// -----------------------------------------------------------
void Model3D::AddFace(const Face3D& face) {
    // check if there are faces that are the same
    for (const shared_ptr<Face3D>& f : Faces) {
        // if the face already exists, throw an exception
        if (Face3D::IsSameFace(*f, face)) {
            throw invalid_argument("Face already exists");
        }
    }
    Faces.push_back(make_shared<Face3D>(face));
}

// -----------------------------------------------------------
// [name] : AddLine
// [function] : adds a new line to the model
// [input] : a constant reference to a Line3D object
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/6
// -----------------------------------------------------------
void Model3D::AddLine(const Line3D& line) {
    // check if there are lines that are the same
    for (const shared_ptr<Line3D>& l : Lines) {
        // if the line already exists, throw an exception
        if (Line3D::IsSameSegment(*l, line)) {
            throw invalid_argument("Line already exists");
        }
    }
    Lines.push_back(make_shared<Line3D>(line));
}

// -----------------------------------------------------------
// [name] : ModifyFacePoint
// [function] : Modifies a point in a face of the 3D model
// [input] : an unsigned int representing the face index, 
//           an unsigned int representing the point index, 
//           and a Point3D object representing the new point
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/6
// -----------------------------------------------------------
void Model3D::ModifyFacePoint(unsigned int FaceIndex, 
                        unsigned int PointIndex, const Point3D& new_point) {
    // check if the face index is out of range
    if (FaceIndex >= Faces.size()) {
        throw invalid_argument("Index out of range");
    }
    // modify the point in the face
    Face3D NewFace = *Faces[FaceIndex];
    NewFace.ModifyPoint(PointIndex, new_point);
    // check if the new face already exists
    if (FindFace(NewFace)) {
        throw invalid_argument("Face already exists");
    }
    // make a shared pointer to the new face
    Faces[FaceIndex] = make_shared<Face3D>(NewFace);
}

// -----------------------------------------------------------
// [name] : ModifyLinePoint
// [function] : Modifies a point in a line of the 3D model
// [input] : an unsigned int representing the line index, 
//           an unsigned int representing the point index, 
//           and a Point3D object representing the new point
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/6
// -----------------------------------------------------------
void Model3D::ModifyLinePoint(unsigned int LineIndex, 
                        unsigned int PointIndex, const Point3D& new_point) {
    // check if the line index is out of range
    if (LineIndex >= Lines.size()) {
        throw invalid_argument("Index out of range");
    }
    // modify the point in the line
    Line3D NewLine = *Lines[LineIndex];
    NewLine.ModifyPoint(PointIndex, new_point);
    // check if the new line already exists
    if (FindLine(NewLine)) {
        throw invalid_argument("Line already exists");
    }
    // make a shared pointer to the new line
    Lines[LineIndex] = make_shared<Line3D>(NewLine);
}

// -----------------------------------------------------------
// [name] : FindFace
// [function] : Checks if a face exists in the 3D model
// [input] : a Face3D object
// [output] : a boolean indicating whether the face exists
// [author] : Huayu Chen
// [date] : 2024/8/6
// -----------------------------------------------------------
bool Model3D::FindFace(const Face3D& face) const {
    // check if the face already exists
    for (const shared_ptr<Face3D>& f : Faces) {
        // if the face already exists, return true
        if (Face3D::IsSameFace(*f, face)) {
            return true;
        }
    }
    return false;
}

// -----------------------------------------------------------
// [name] : FindLine
// [function] : Checks if a line exists in the 3D model
// [input] : a Line3D object
// [output] : a boolean indicating whether the line exists
// [author] : Huayu Chen
// [date] : 2024/8/6
// -----------------------------------------------------------
bool Model3D::FindLine(const Line3D& line) const {
    // check if the line already exists
    for (const shared_ptr<Line3D>& l : Lines) {
        // if the line already exists, return true
        if (Line3D::IsSameSegment(*l, line)) {
            return true;
        }
    }
    return false;
}

// -----------------------------------------------------------
// [name] : ModifyName
// [function] : Modifies the name of the 3D model
// [input] : a string representing the new name
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/6
// -----------------------------------------------------------
void Model3D::ModifyName(const string& name) {
    Name = name;
}

// -----------------------------------------------------------
// [name] : GetFaces
// [function] : Retrieves all faces of the 3D model
// [input] : none
// [output] : a constant reference to a vector of shared pointers to Face3D objects
// [author] : Huayu Chen
// [date] : 2024/8/6
// -----------------------------------------------------------
const vector<shared_ptr<Face3D>>& Model3D::GetFaces() const {
    return Faces;
}

// -----------------------------------------------------------
// [name] : GetLines
// [function] : Retrieves all lines of the 3D model
// [input] : none
// [output] : a constant reference to a vector of shared pointers to Line3D objects
// [author] : Huayu Chen
// [date] : 2024/8/6
// -----------------------------------------------------------
const vector<shared_ptr<Line3D>>& Model3D::GetLines() const {
    return Lines;
}

// -----------------------------------------------------------
// [name] : GetName
// [function] : Retrieves the name of the 3D model
// [input] : none
// [output] : a string representing the name
// [author] : Huayu Chen
// [date] : 2024/8/6
// -----------------------------------------------------------
string Model3D::GetName() const {
    return Name;
}

// -----------------------------------------------------------
// [name] : GetPoints
// [function] : Retrieves all points of the 3D model
// [input] : none
// [output] : a vector of Point3D objects
// [author] : Huayu Chen
// [date] : 2024/8/6
// -----------------------------------------------------------
vector<Point3D> Model3D::GetPoints() const {
    vector<Point3D> Points;
    // get all points from the faces
    for (const shared_ptr<Face3D>& face : Faces) {
        for (const Point3D& point : face->GetPoints()) {
            Points.push_back(point);
        }
    }
    // get all points from the lines
    for (const shared_ptr<Line3D>& line : Lines) {
        for (const Point3D& point : line->GetPoints()) {
            Points.push_back(point);
        }
    }
    return Points;
}


