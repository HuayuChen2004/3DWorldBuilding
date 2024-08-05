// this is the header file for the Model3DObjImporter class
// the class Model3DObjImporter is derived from Model3DImporter and implements 
// the import function for OBJ files
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
#include "../Element3D/face3d.hpp"
#include "../Element3D/line3d.hpp"

class Model3DObjImporter : public Model3DImporter
{
public:
    Model3DObjImporter();
    virtual ~Model3DObjImporter();
    Model3D Load(const string& path) const override;
    vector<Point3D> LoadVertices(const string& path) const;
    vector<Face3D> LoadFaces(const string& path) const;
    vector<Line3D> LoadLines(const string& path) const;
    
private:
    // vector<Point3D> LoadVertices(const string& path) const;
    
    string LoadName(const string& path) const;
};

















#endif // MODEL3DOBJIMPORTER_HPP