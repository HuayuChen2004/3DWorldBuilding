// [file name] : model3dobjimporter.hpp
// [function] : declare the Model3DObjImporter class
// [author] : Huayu Chen
// [date] : 2024/7/31

// [edit history] :
// -----------------------------------------------------------
// date: 2024/7/31
// author: Huayu Chen
// edit: init Model3DObjImporter class
//       add Load function to load OBJ files
// -----------------------------------------------------------

#ifndef MODEL3DOBJIMPORTER_HPP
#define MODEL3DOBJIMPORTER_HPP

#include "model3dimporter.hpp"
#include "../Model3D/model3d.hpp"
#include "../Element3D/point3d.hpp"
#include "../Element3D/face3d.hpp"
#include "../Element3D/line3d.hpp"
#include <vector>
#include <string>

// notes on the class Model3DObjImporter
// -----------------------------------------------------------
// [class name] : Model3DObjImporter
// [function] : import 3D models from OBJ files
// [notes on interface] :
// 1. The Model3DObjImporter class is a class that imports 3D models from OBJ 
//    files. It is derived from the Model3DImporter class.
// 2. The Load function takes a path as input and loads a 3D model from a file
//    in OBJ format. It returns a Model3D object that contains the loaded model.
// 3. The LoadVertices, LoadFaces, and LoadLines functions are helper functions
//    that load vertices, faces, and lines from a file in OBJ format.
// 4. The LoadName function is a helper function that loads the name of the 
//    model from a file in OBJ format.
// [author] : Huayu Chen
// [date] : 2024/7/31
// -----------------------------------------------------------


class Model3DObjImporter : public Model3DImporter
{
public:
    // default constructor
    Model3DObjImporter();
    // virtual destructor
    virtual ~Model3DObjImporter();
    // load a 3D model from a file in OBJ format
    Model3D Load(const string& path) const override;
    // load vertices from a file
    vector<Point3D> LoadVertices(const string& path) const;
    // load faces from a file
    vector<Face3D> LoadFaces(const string& path) const;
    // load lines from a file
    vector<Line3D> LoadLines(const string& path) const;
    // load the name of the model from a file
    string LoadName(const string& path) const;
    
};

















#endif // MODEL3DOBJIMPORTER_HPP