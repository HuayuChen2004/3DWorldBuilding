// this is the header file for the Model3DExporter class
// the class Model3DExporter is a class that exports 3D models to files
// edit logging: 
// -----------------------------------------------------------
// date: 2024/7/31
// author: Huayu Chen
// edit: init Model3DExporter class
//       add Save function to export 3D models to files
// reason: to support exporting 3D models to files
// -----------------------------------------------------------
//
//
//
//
//
//
//

#ifndef EXPORTER_HPP
#define EXPORTER_HPP
//
//
//

//
#include <string>
#include "../Model3D/model3d.hpp"

//
using namespace std;
//
//
//
//
//
//
//

//
class Model3DExporter
{
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
public:
    //
    //
    Model3DExporter();
    virtual ~Model3DExporter();
    //
    //
    //
    virtual void Save(const string& path, const Model3D& model) const = 0;
    //
    //
    //
    //
    //
    //
    //
    //

};








#endif // EXPORTER_HPP