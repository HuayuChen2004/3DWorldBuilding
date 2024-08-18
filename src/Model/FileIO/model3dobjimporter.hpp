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


// this is the header file for the Model3DObjImporter class
// the class Model3DObjImporter is derived from Model3DImporter and implements 
// the import function for OBJ files


#ifndef MODEL3DOBJIMPORTER_HPP
#define MODEL3DOBJIMPORTER_HPP

#include "model3dimporter.hpp"
#include "../Model3D/model3d.hpp"
#include "../Element3D/point3d.hpp"
#include "../Element3D/face3d.hpp"
#include "../Element3D/line3d.hpp"
#include <vector>
#include <string>


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