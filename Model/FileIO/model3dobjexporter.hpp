// This is the header file for the Model3DObjExporter class.
// The class Model3DObjExporter is derived from Model3DExporter and implements the export function for OBJ files.
// edit logging
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
#include <string>

using namespace std;

class Model3DExporter;

class Model3DObjExporter : public Model3DExporter
{
public:
    Model3DObjExporter();
    virtual ~Model3DObjExporter();

    void Save(const string& path, const Model3D& model);


};

#endif // MODEL3DOBJEXPORTER_HPP