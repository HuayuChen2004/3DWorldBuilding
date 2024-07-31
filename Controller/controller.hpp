// this is the header file of the controller class
// the class controller is a class that controls the 3D model
// and interacts with the viewer
// the class controller has functions to operate the model
// and functions to interact with the viewer
// edit logging:
// -----------------------------------------------------------
// date: 2024/7/31
// author: Huayu Chen
// edit: init controller class
//       add functions to operate the model
//       add functions to interact with the viewer
// reason: to support various operations on the model and interactions with the viewer
// -----------------------------------------------------------
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
//
//
//
//
//
//
//
#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP



#include <string>
#include <vector>
#include <memory>
#include "../Model/Element3D/face3d.hpp"
#include "../Model/Element3D/point3d.hpp"
#include "../Model/Element3D/line3d.hpp"
#include "../Model/Model3D/model3d.hpp"

using namespace std;
//
//
//
//
//
//
//从viewer传到controller的参数
//
class Argument
{
};
//
//
//
class Response
{
};

//
//
//
class Controller
{
public:
    //
    //
    //
    //操作model的函数
    //
    //
    void Import3DModel(const string& path);
    //
    void Export3DModel(const string& path, const Model3D& model);
    //word里面2.几那些功能最好每一个写一个函数
    void DisplayAllFaces() const;
    void DeleteFace(unsigned int FaceIndex);
    void AddFace(const Face3D& face);
    void DisplayFacePoints(unsigned int FaceIndex) const;
    void ModifyFacePoint(unsigned int FaceIndex, unsigned int PointIndex, const Point3D& point);
    void DisplayAllLines();
    void AddLine(const Line3D& line);
    void DeleteLine(unsigned int LineIndex);
    void DisplayLinePoints(unsigned int LineIndex) const;
    void ModifyLinePoint(unsigned int LineIndex, unsigned int PointIndex, const Point3D& point);
    void DisplayStatistics() const;
    //实现里面的功能
    //
    //
    //
    //
    //和viewer交互
    //
    //
    //
    //
    //
    //
    Response HandleArguments(vector<Argument> arguments);
    //
    //
    //
    //
    //
    //
    //
    //
    //
private:
    //
    //
    vector<shared_ptr<Model3D>> m_vpModels;
    //
    //`




};
















#endif // CONTROLLER_HPP