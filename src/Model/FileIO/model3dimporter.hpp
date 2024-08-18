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

#ifndef IMPORTER_HPP
#define IMPORTER_HPP

#include <string>
#include <vector>
#include "../Model3D/model3d.hpp"
#include "../Element3D/face3d.hpp"
#include "../Element3D/line3d.hpp"

using namespace std;

// notes on the class Model3DImporter
// -----------------------------------------------------------
// [class name] : Model3DImporter
// [function] : import 3D models from files
// [notes on interface] :
// 1. The Model3DImporter class is a class that imports 3D models from files.
// 2. The Model3DImporter class is an abstract class, so it needs to be derived
// 3. The LoadFaces and LoadLines functions are pure virtual functions that need
//    to be implemented by derived classes.
// 4. The Load function is a virtual function that loads a 3D model from a file.
// [author] : Huayu Chen
// [date] : 2024/7/31
// -----------------------------------------------------------

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