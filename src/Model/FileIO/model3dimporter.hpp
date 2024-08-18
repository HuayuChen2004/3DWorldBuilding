// [file name] : model3dimporter.hpp
// [function] : declare the Model3DImporter class
// [author] : Huayu Chen
// [date] : 2024/7/31

// [edit history] :
// -----------------------------------------------------------
// date: 2024/7/31
// author: Huayu Chen
// edit: init model3dimporter class
//       add Load function
// reason: to support importing 3D models from files
// -----------------------------------------------------------
//

// this is the header file of the model3dimporter class
// the class model3dimporter is a class that imports 3D models from files
// the class model3dimporter is a base class for other model3d importers
// the class model3dimporter has a virtual function Load that 
// loads a model3d from a file
#ifndef IMPORTER_HPP
#define IMPORTER_HPP

#include <string>
#include <vector>
#include "../Model3D/model3d.hpp"
#include "../Element3D/face3d.hpp"
#include "../Element3D/line3d.hpp"

using namespace std;


class Model3DImporter
{

public:
    // default constructor
    Model3DImporter();
    // virtual destructor
    virtual ~Model3DImporter();

    // load a 3D model from a file
    virtual Model3D Load(const string& path) const;
    // load faces from a file
    // this function needs to be implemented by derived classes
    virtual vector<Face3D> LoadFaces(const string& path) const = 0;
    // load points from a file
    // this function needs to be implemented by derived classes
    virtual vector<Line3D> LoadLines(const string& path) const = 0;

};

#endif // IMPORTER_HPP