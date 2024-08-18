// [file name] : model3dexporter.hpp
// [function] : declare the Model3DExporter class
// [author] : Huayu Chen
// [date] : 2024/7/31

// [edit history] :
// -----------------------------------------------------------
// date: 2024/7/31
// author: Huayu Chen
// edit: init Model3DExporter class
//       add Save function to export 3D models to files
// reason: to support exporting 3D models to files
// -----------------------------------------------------------

#ifndef EXPORTER_HPP
#define EXPORTER_HPP

#include <string>
#include "../Model3D/model3d.hpp"

using namespace std;

// notes on the class Model3DExporter
// -----------------------------------------------------------
// [class name] : Model3DExporter
// [function] : export 3D models to files
// [notes on interface] :
// 1. The Model3DExporter class is a class that exports 3D models to files
// 2. The Model3DExporter class is an abstract class, so it needs to be derived
//    to implement the Save function
// 3. The Save function is a pure virtual function that needs to be implemented
//    by derived classes
// [author] : Huayu Chen
// [date] : 2024/7/31
// -----------------------------------------------------------

class Model3DExporter
{

public:
    // default constructor
    Model3DExporter();
    // virtual destructor
    virtual ~Model3DExporter();
    // export the 3D model to a file
    // this function needs to be implemented by derived classes
    virtual void Save(const string& path, const Model3D& model) const = 0;
};


#endif // EXPORTER_HPP