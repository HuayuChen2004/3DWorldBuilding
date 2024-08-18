// [file name] : model3dobjexporter.hpp
// [function] : declare the Model3DObjExporter class
// [author] : Huayu Chen
// [date] : 2024/7/31

// [edit history] :
// -----------------------------------------------------------
// date: 2024/7/31
// author: Huayu Chen
// edit: init Model3DObjExporter class
//       add Save function to save OBJ files
// reason: to support exporting 3D models to OBJ files
// -----------------------------------------------------------

#ifndef MODEL3DOBJEXPORTER_HPP
#define MODEL3DOBJEXPORTER_HPP

#include "model3dexporter.hpp"
#include "../Model3D/model3d.hpp"
#include <vector>
#include <string>

using namespace std;

// notes on the class Model3DObjExporter
// -----------------------------------------------------------
// [class name] : Model3DObjExporter
// [function] : export 3D models to OBJ files
// [notes on interface] :
// 1. The Model3DObjExporter class is a class that exports 3D models to OBJ 
//    files. It is derived from the Model3DExporter class.
// 2. The Save function takes a path and a Model3D object as input and exports 
//    the 3D model to a file in OBJ format.
// [author] : Huayu Chen
// [date] : 2024/7/31
// -----------------------------------------------------------

class Model3DObjExporter : public Model3DExporter
{
public:
    // default constructor
    Model3DObjExporter();
    // virtual destructor
    virtual ~Model3DObjExporter();

    // export the 3D model to a file in OBJ format
    void Save(const string& path, const Model3D& model) const override;
    
private:
    // list distinct vertices in the model
    vector<Point3D> ListDistinctVertices(const Model3D& model) const;

};

#endif // MODEL3DOBJEXPORTER_HPP