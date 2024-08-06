#include "Model/Element3D/point3d.hpp"
#include "Model/FileIO/model3dobjimporter.hpp"
#include <iostream>
using namespace std;



int main() {
    // Point3D point(1, 2, 3);
    // cout << point << endl;
    // cout << "Hello, World!" << endl;
    Model3DObjImporter importer;
    vector<Point3D> vertices = importer.LoadVertices(
        "D:/coding/cpp/oop/hw/cube.obj"
    );
    for (const Point3D& vertex : vertices) {
        cout << vertex << endl;
    }
    return 0;
}