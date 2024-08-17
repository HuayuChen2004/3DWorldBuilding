



#include "model3dobjexporter.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>


using namespace std;

Model3DObjExporter::Model3DObjExporter() {}

Model3DObjExporter::~Model3DObjExporter() {}

void Model3DObjExporter::Save(const string& path, const Model3D& model) const {

    ofstream file(path);
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

    file << "# OBJ file" << endl;
    file << "g " << model.GetName() << endl;

    vector<Point3D> vertices = ListDistinctVertices(model);

    for (const Point3D& vertex : vertices) {
        file << "v  " << to_string(vertex.X) << " " << 
            to_string(vertex.Y) << " " << to_string(vertex.Z) << endl;
    }

    for (const shared_ptr<Face3D>& face : model.GetFaces()) {
        file << "f ";
        for (const Point3D& vertex : face->GetPoints()) {
            auto it = find(vertices.begin(), vertices.end(), vertex);
            if (it == vertices.end()) {
                throw runtime_error("Failed to export the 3D model.");
            }
            file << " " << distance(vertices.begin(), it) + 1 << " ";
        }
        file << endl;
    }
    for (const shared_ptr<Line3D>& line : model.GetLines()) {
        file << "l ";
        for (const Point3D& vertex : line->GetPoints()) {
            auto it = find(vertices.begin(), vertices.end(), vertex);
            if (it == vertices.end()) {
                throw runtime_error("Failed to export the 3D model.");
            }
            file << " " << distance(vertices.begin(), it) + 1 << " ";
        }
        file << endl;
    }

    file.close();
}

vector<Point3D> Model3DObjExporter::ListDistinctVertices(
                        const Model3D& model) const {
    vector<Point3D> vertices;
    for (const shared_ptr<Face3D>& face : model.GetFaces()) {
        for (const Point3D& vertex : face->GetPoints()) {
            if (find(vertices.begin(), vertices.end(), vertex) == vertices.end()) {
                vertices.push_back(vertex);
            }
        }
    }
    for (const shared_ptr<Line3D>& line : model.GetLines()) {
        for (const Point3D& vertex : line->GetPoints()) {
            if (find(vertices.begin(), vertices.end(), vertex) == vertices.end()) {
                vertices.push_back(vertex);
            }
        }
    }
    return vertices;
}

