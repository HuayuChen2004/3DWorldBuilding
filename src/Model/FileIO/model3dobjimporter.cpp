// this is the implementation of the Model3DObjImporter class
// edit logging:
// -----------------------------------------------------------
// date: 2024/8/5
// author: Huayu Chen
// edit: add implementation of the Model3DObjImporter class
// reason: to support importing OBJ files
// -----------------------------------------------------------

#include "model3dobjimporter.hpp"
#include <fstream>

using namespace std;

Model3DObjImporter::Model3DObjImporter() {}

Model3DObjImporter::~Model3DObjImporter() {}


Model3D Model3DObjImporter::Load(const string& path) const {
    // check if the file is an obj file
    if (path.substr(path.find_last_of(".") + 1) != "obj") {
        throw invalid_argument("File is not an obj file");
    }

    // load the faces and lines from the obj file
    try {
        vector<Face3D> faces = LoadFaces(path);
        vector<Line3D> lines = LoadLines(path);
        string name = LoadName(path);
        return Model3D(faces, lines, name);
    } catch (const exception& e) {
        throw runtime_error(string("Failed to load the obj file: ") + e.what());
    }
}

vector<Point3D> Model3DObjImporter::LoadVertices(const string& path) const {
    vector<Point3D> vertices;
    ifstream file(path);
    if (!file.is_open()) {
        throw invalid_argument("Failed to open the file");
    }

    string line;
    while (getline(file, line)) {
        if (line.substr(0, 2) == "v ") {
            double x, y, z;
            if (sscanf(line.c_str(), "v  %lf  %lf  %lf", &x, &y, &z) != 3) {
                throw invalid_argument("Failed to parse the vertex");
            }
            vertices.push_back(Point3D(x, y, z));
        }
    }

    return vertices;
}

vector<Face3D> Model3DObjImporter::LoadFaces(const string& path) const {
    vector<Face3D> faces;
    ifstream file(path);
    if (!file.is_open()) {
        throw invalid_argument("Failed to open the file");
    }

    vector<Point3D> vertices = LoadVertices(path);
    string line;
    while (getline(file, line)) {
        if (line.substr(0, 2) == "f ") {
            int vertexIndex1, vertexIndex2, vertexIndex3;
            if (sscanf(line.c_str(), "f  %d  %d  %d", &vertexIndex1, &vertexIndex2, &vertexIndex3) != 3) {
                throw invalid_argument("Failed to parse the face");
            }
            faces.push_back(Face3D(vertices[vertexIndex1 - 1], vertices[vertexIndex2 - 1], vertices[vertexIndex3 - 1]));
        }
    }

    return faces;
}

vector<Line3D> Model3DObjImporter::LoadLines(const string& path) const {
    vector<Line3D> lines;
    ifstream file(path);
    if (!file.is_open()) {
        throw invalid_argument("Failed to open the file");
    }

    vector<Point3D> vertices = LoadVertices(path);
    string line;
    while (getline(file, line)) {
        if (line.substr(0, 2) == "l ") {
            int vertexIndex1, vertexIndex2;
            if (sscanf(line.c_str(), "l  %d  %d", &vertexIndex1, &vertexIndex2) != 2) {
                throw invalid_argument("Failed to parse the line");
            }
            lines.push_back(Line3D(vertices[vertexIndex1 - 1], vertices[vertexIndex2 - 1]));
        }
    }

    return lines;
}

string Model3DObjImporter::LoadName(const string& path) const {
    ifstream file(path);
    if (!file.is_open()) {
        throw invalid_argument("Failed to open the file");
    }

    string line;
    while (getline(file, line)) {
        if (line.substr(0, 2) == "g ") {
            return line.substr(2);
        }
    }

    return "";
}