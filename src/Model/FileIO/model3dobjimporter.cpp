// [file name] : model3dobjimporter.cpp
// [function] : implement the Model3DObjImporter class
// [author] : Huayu Chen
// [date] : 2024/8/5

// [edit history] :
// -----------------------------------------------------------
// date: 2024/8/5
// author: Huayu Chen
// edit: add implementation of the Model3DObjImporter class
// reason: to support importing OBJ files
// -----------------------------------------------------------

#include "model3dobjimporter.hpp"
#include <fstream>

using namespace std;

// -----------------------------------------------------------
// [name] : Model3DObjImporter
// [function] : Constructor for Model3DObjImporter class
// [input] : None
// [output] : None
// [author] : Huayu Chen
// [date] : 2024/8/5
// -----------------------------------------------------------
Model3DObjImporter::Model3DObjImporter() {}

// -----------------------------------------------------------
// [name] : ~Model3DObjImporter
// [function] : Destructor for Model3DObjImporter class
// [input] : None
// [output] : None
// [author] : Huayu Chen
// [date] : 2024/8/5
// -----------------------------------------------------------
Model3DObjImporter::~Model3DObjImporter() {}


// -----------------------------------------------------------
// [name] : Load
// [function] : Loads a 3D model from a given path
// [input] : a string representing the path to the OBJ file
// [output] : a Model3D object
// [author] : Huayu Chen
// [date] : 2024/8/5
// -----------------------------------------------------------
Model3D Model3DObjImporter::Load(const string& path) const {
    // Check if the path is empty
    if (path.empty()) {
        throw invalid_argument("Path should not be empty.");
    }

    // Check if the file is an obj file
    if (path.substr(path.find_last_of(".") + 1) != "obj") {
        throw invalid_argument("Path is not a valid OBJ file.");
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

// -----------------------------------------------------------
// [name] : LoadVertices
// [function] : Loads vertices from a given OBJ file
// [input] : a string representing the path to the OBJ file
// [output] : a vector of Point3D objects
// [author] : Huayu Chen
// [date] : 2024/8/5
// -----------------------------------------------------------
vector<Point3D> Model3DObjImporter::LoadVertices(const string& path) const {
    vector<Point3D> vertices;
    ifstream file(path);
    // Check if the file is open
    if (!file.is_open()) {
        throw invalid_argument("Failed to open the file");
    }

    string line;
    // Read the file line by line
    while (getline(file, line)) {
        // Check if the line starts with "v "
        // If it does, parse the coordinates 
        // and add a Point3D object to the vector
        if (line.substr(0, 2) == "v ") {
            double x, y, z;
            // Check if the line can be parsed
            if (sscanf(line.c_str(), "v  %lf  %lf  %lf", &x, &y, &z) != 3) {
                throw invalid_argument("Failed to parse");
            }
            vertices.push_back(Point3D(x, y, z));
        }
    }

    return vertices;
}

// -----------------------------------------------------------
// [name] : LoadFaces
// [function] : Loads faces from a given OBJ file
// [input] : a string representing the path to the OBJ file
// [output] : a vector of Face3D objects
// [author] : Huayu Chen
// [date] : 2024/8/5
// -----------------------------------------------------------
vector<Face3D> Model3DObjImporter::LoadFaces(const string& path) const {
    vector<Face3D> faces;
    ifstream file(path);
    // Check if the file is open
    if (!file.is_open()) {
        throw invalid_argument("Failed to open the file");
    }
    // Load vertices
    vector<Point3D> vertices = LoadVertices(path);
    string line;
    while (getline(file, line)) {
        if (line.substr(0, 2) == "f ") {
            int vertexIndex1, vertexIndex2, vertexIndex3;
            // Check if the line can be parsed
            if (sscanf(line.c_str(), "f  %d  %d  %d", 
                        &vertexIndex1, &vertexIndex2, &vertexIndex3) != 3) {
                throw invalid_argument("Failed to parse");
            }
            // Add a Face3D object to the vector
            // Note that OBJ files use 1-based indexing, 
            // so we subtract 1 from the indices
            faces.push_back(
                Face3D(vertices[vertexIndex1 - 1], 
                vertices[vertexIndex2 - 1], 
                vertices[vertexIndex3 - 1])
            );
        }
    }

    return faces;
}

// -----------------------------------------------------------
// [name] : LoadLines
// [function] : Loads lines from a given OBJ file
// [input] : a string representing the path to the OBJ file
// [output] : a vector of Line3D objects
// [author] : Huayu Chen
// [date] : 2024/8/5
// -----------------------------------------------------------
vector<Line3D> Model3DObjImporter::LoadLines(const string& path) const {
    vector<Line3D> lines;
    ifstream file(path);
    // Check if the file is open
    if (!file.is_open()) {
        throw invalid_argument("Failed to open the file");
    }
    // Load vertices
    vector<Point3D> vertices = LoadVertices(path);
    string line;
    // Read the file line by line
    while (getline(file, line)) {
        // Check if the line starts with "l "
        if (line.substr(0, 2) == "l ") {
            int vertexIndex1, vertexIndex2;
            // Check if the line can be parsed
            if (sscanf(line.c_str(), "l  %d  %d", 
                        &vertexIndex1, &vertexIndex2) != 2) {
                throw invalid_argument("Failed to parse");
            }
            // Add a Line3D object to the vector
            // Note that OBJ files use 1-based indexing,
            // so we subtract 1 from the indices
            lines.push_back(Line3D(vertices[vertexIndex1 - 1], 
                                    vertices[vertexIndex2 - 1]));
        }
    }

    return lines;
}

// -----------------------------------------------------------
// [name] : LoadName
// [function] : Loads the name of the model from a given OBJ file
// [input] : a string representing the path to the OBJ file
// [output] : a string representing the name of the model
// [author] : Huayu Chen
// [date] : 2024/8/5
// -----------------------------------------------------------
string Model3DObjImporter::LoadName(const string& path) const {
    ifstream file(path);
    // Check if the file is open
    if (!file.is_open()) {
        throw invalid_argument("Failed to open the file");
    }
    // Read the file line by line
    string line;
    while (getline(file, line)) {
        // Check if the line starts with "g "
        if (line.substr(0, 2) == "g ") {
            return line.substr(2);
        }
    }
    // Return an empty string if the name is not found
    return "";
}