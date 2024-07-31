// this is the header file for the Model3DObjImporter class
// the class Model3DObjImporter is derived from Model3DImporter and implements the import function for OBJ files
// edit logging:
// -----------------------------------------------------------
// date: 2024/7/31
// author: Huayu Chen
// edit: init Model3DObjImporter class
//       add Load function to load OBJ files
// -----------------------------------------------------------





#ifndef MODEL3DOBJIMPORTER_HPP
#define MODEL3DOBJIMPORTER_HPP

#include "model3dimporter.hpp"

class Model3DObjImporter : public Model3DImporter
{
public:
    Model3D Load(const string& path) const override;
};

















#endif // MODEL3DOBJIMPORTER_HPP