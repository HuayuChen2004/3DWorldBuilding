// [file name] : model3dimporter.cpp
// [function] : implement the Model3DImporter class
// [author] : Huayu Chen
// [date] : 2024/8/5

// [edit history] :
// -----------------------------------------------------------
// date: 2024/8/5
// author: Huayu Chen
// edit: add implementation of the Model3DImporter class
// reason: to support importing 3D models
// -----------------------------------------------------------
// This is the implementation of the Model3DImporter class.
// This class is used to import 3D models.
#include "model3dimporter.hpp"

using namespace std;

Model3DImporter::Model3DImporter() {}

Model3DImporter::~Model3DImporter() {}

Model3D Model3DImporter::Load(const string& path) const {
    vector<Face3D> faces = LoadFaces(path);
    vector<Line3D> lines = LoadLines(path);
    return Model3D(faces, lines);
}