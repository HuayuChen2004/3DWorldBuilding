// [file name] : model3d.hpp
// [function] : declare the Model3D class
// [author] : Huayu Chen
// [date] : 2024/7/30

// [edit history] :
// -----------------------------------------------------------
// date: 2024/7/30
// author: Huayu Chen
// edit: init model3d class
//       add model3d operations
// reason: to support various operations on model3d
// -----------------------------------------------------------
// date: 2024/8/2
// author: Huayu Chen
// edit: add getter of faces, lines, and points
// reason: to support getting faces, lines, and points
// -----------------------------------------------------------
// date: 2024/8/3
// author: Huayu Chen
// edit: add const to getter of faces, lines, and points
//       add unsigned int to the getter of faces, lines, and points
// reason: to make the code more readable and efficient
// -----------------------------------------------------------

#ifndef MODEL3D_HPP
#define MODEL3D_HPP

#include <vector>
#include <memory>
#include "../Element3D/face3d.hpp"
#include "../Element3D/line3d.hpp"
#include "../Element3D/point3d.hpp"
#include <string>

using namespace std;

// notes on the class Model3D
// -----------------------------------------------------------
// [class name] : Model3D
// [function] : represent a 3D model that contains faces and lines
// [notes on interface] :
// 1. the model3d is defined by a vector of faces and a vector of lines
// 2. the model3d supports some operations to modify the faces and lines
// 3. there are getter functions to get the faces, lines, and points
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------


class Model3D {
public:
    // default constructor
    Model3D();
    // constructor, initiate a model3d with faces and lines and a name
    Model3D(vector<Face3D> faces, vector<Line3D> lines, const string& name="");
    // copy constructor
    Model3D(const Model3D& model);
    // virtual destructor
    virtual ~Model3D();
    // assignment operator
    Model3D& operator=(const Model3D& model);

    // functions to modify the model3d
    // displaying functions are not provided
    // function 1: delete a face
    void DeleteFace(unsigned int index);
    // function 2: add a face
    void AddFace(const Face3D& face);
    // function 3: modify a point of a face
    void ModifyFacePoint(unsigned int FaceIndex, 
                        unsigned int PointIndex, const Point3D& new_point);
    // function 4: delete a line
    void DeleteLine(unsigned int index);
    // function 5: add a line
    void AddLine(const Line3D& line);
    // function 6: modify a point of a line
    void ModifyLinePoint(unsigned int LineIndex, 
                        unsigned int PointIndex, const Point3D& new_point);
    // function 7: modify the name of the model3d
    void ModifyName(const string& name);

    // getter of faces, lines, name, and points
    const vector<shared_ptr<Face3D>>& GetFaces() const;
    const vector<shared_ptr<Line3D>>& GetLines() const;
    string GetName() const;
    vector<Point3D> GetPoints() const;


private:
    // the name of the model3d
    string Name;
    // the faces and lines of the model3d
    vector<shared_ptr<Face3D>> Faces;
    vector<shared_ptr<Line3D>> Lines;

    // helper functions to check if a face or a line is in the model3d
    bool FindFace(const Face3D& face) const;
    bool FindLine(const Line3D& line) const;

};

#endif // MODEL3D_HPP