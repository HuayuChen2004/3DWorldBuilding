#include "Model/Element3D/point3d.hpp"
#include <iostream>
using namespace std;



int main() {
    Point3D point(1, 2, 3);
    cout << point << endl;
    // vector<Point3D> vertices = importer.LoadVertices("cube.obj");
    // for (const Point3D& vertex : vertices) {
    //     cout << vertex << endl;
    // }
    return 0;
}