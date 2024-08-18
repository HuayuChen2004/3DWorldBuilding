// [file name] : model3dobjexporter.cpp
// [function] : implement the Model3DObjExporter class
// [author] : Huayu Chen
// [date] : 2024/8/5

// [edit history] :
// -----------------------------------------------------------
// date: 2024/8/5
// author: Huayu Chen
// edit: add implementation of the Model3DObjExporter class
// reason: to support exporting 3D models to OBJ files
// -----------------------------------------------------------



#include "model3dobjexporter.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>


using namespace std;

// -----------------------------------------------------------
// [name] : Model3DObjExporter
// [function] : Constructor for Model3DObjExporter class
// [input] : None
// [output] : None
// [author] : Huayu Chen
// [date] : 2024/8/5
// -----------------------------------------------------------
Model3DObjExporter::Model3DObjExporter() {}

// -----------------------------------------------------------
// [name] : ~Model3DObjExporter
// [function] : Destructor for Model3DObjExporter class
// [input] : None
// [output] : None
// [author] : Huayu Chen
// [date] : 2024/8/5
// -----------------------------------------------------------
Model3DObjExporter::~Model3DObjExporter() {}

// -----------------------------------------------------------
// [name] : Save
// [function] : Saves a Model3D object to a file in OBJ format
// [input] : a string representing the file path, a Model3D object
// [output] : None
// [author] : Huayu Chen
// [date] : 2024/8/5
// -----------------------------------------------------------
void Model3DObjExporter::Save(const string& path, const Model3D& model) const {

    ofstream file(path);
    // Check if the file is opened successfully
    if (!file.is_open()) {
        throw runtime_error("Failed to open file");
    }
    // Check if the path is empty
    if (path.empty())
    {
        throw invalid_argument("Path should not be empty.");
    }
    // Check if the path is valid
    if (path.find(".obj") == string::npos)
    {
        throw invalid_argument("Path is not a valid OBJ file.");
    }
    // Write the OBJ file header
    file << "# OBJ file" << endl;
    file << "g " << model.GetName() << endl;
    // List all distinct vertices
    vector<Point3D> vertices = ListDistinctVertices(model);
    // Write the vertices to the file
    for (const Point3D& vertex : vertices) {
        file << "v  " << to_string(vertex.X) << " " << 
            to_string(vertex.Y) << " " << to_string(vertex.Z) << endl;
    }
    // Write the faces to the file
    for (const shared_ptr<Face3D>& face : model.GetFaces()) {
        file << "f ";
        for (const Point3D& vertex : face->GetPoints()) {
            auto it = find(vertices.begin(), vertices.end(), vertex);
            // Check if the vertex is in the list
            if (it == vertices.end()) {
                throw runtime_error("Failed to export the 3D model.");
            }
            file << " " << distance(vertices.begin(), it) + 1 << " ";
        }
        file << endl;
    }
    // Write the lines to the file
    for (const shared_ptr<Line3D>& line : model.GetLines()) {
        file << "l ";
        for (const Point3D& vertex : line->GetPoints()) {
            auto it = find(vertices.begin(), vertices.end(), vertex);
            // Check if the vertex is in the list
            if (it == vertices.end()) {
                throw runtime_error("Failed to export the 3D model.");
            }
            file << " " << distance(vertices.begin(), it) + 1 << " ";
        }
        file << endl;
    }
    file.close();
}

// -----------------------------------------------------------
// [name] : ListDistinctVertices
// [function] : Lists all distinct vertices in a Model3D object
// [input] : a Model3D object
// [output] : a vector of Point3D objects representing distinct vertices
// [author] : Huayu Chen
// [date] : 2024/8/5
// -----------------------------------------------------------
vector<Point3D> Model3DObjExporter::ListDistinctVertices(
                        const Model3D& model) const {
    vector<Point3D> vertices;
    // List all vertices in the faces
    for (const shared_ptr<Face3D>& face : model.GetFaces()) {
        for (const Point3D& vertex : face->GetPoints()) {
            if (find(vertices.begin(), vertices.end(), vertex) 
                            == vertices.end()) {
                vertices.push_back(vertex);
            }
        }
    }
    // List all vertices in the lines
    for (const shared_ptr<Line3D>& line : model.GetLines()) {
        for (const Point3D& vertex : line->GetPoints()) {
            if (find(vertices.begin(), vertices.end(), vertex) 
                            == vertices.end()) {
                vertices.push_back(vertex);
            }
        }
    }
    return vertices;
}

