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

// -----------------------------------------------------------
// [name] : Model3DImporter
// [function] : constructor for Model3DImporter class
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/5
// -----------------------------------------------------------
Model3DImporter::Model3DImporter() {}

// -----------------------------------------------------------
// [name] : ~Model3DImporter
// [function] : destructor for Model3DImporter class
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/5
// -----------------------------------------------------------
Model3DImporter::~Model3DImporter() {}

// -----------------------------------------------------------
// [name] : Load
// [function] : loads a 3D model from a given file path
// [input] : a string representing the file path
// [output] : a Model3D object containing the loaded faces and lines
// [author] : Huayu Chen
// [date] : 2024/8/5
// -----------------------------------------------------------
Model3D Model3DImporter::Load(const string& path) const {
    vector<Face3D> faces = LoadFaces(path);
    vector<Line3D> lines = LoadLines(path);
    return Model3D(faces, lines);
}