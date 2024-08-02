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
// date: 2024/8/1
// author: Huayu Chen
// edit: add HandleArguments function
//       init Argument and Response classes
// reason: to support handling arguments from the viewer
//         and returning responses to the viewer
// -----------------------------------------------------------
// date: 2024/8/2
// author: Huayu Chen
// edit: init Response class
// reason: to support handling some errors
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
public:
    enum class ArgumentKey {
        IMPORT_3D_MODEL,
        EXPORT_3D_MODEL,
        DISPLAY_ALL_FACES,
        DELETE_FACE,
        ADD_FACE,
        DISPLAY_FACE_POINTS,
        MODIFY_FACE_POINT,
        DISPLAY_ALL_LINES,
        ADD_LINE,
        DELETE_LINE,
        DISPLAY_LINE_POINTS,
        MODIFY_LINE_POINT,
        DISPLAY_STATISTICS,
        UNKNOWN
    };
    Argument();
    Argument(ArgumentKey key, vector<string> values);
    Argument& operator=(const Argument& argument);
    virtual ~Argument();
    ArgumentKey GetKey() const;
    string GetValue() const;
private:
    ArgumentKey m_key;
    string m_value;

};
//
//
//
class Response
{
public:
    enum class ResponseKey {
        EMPTY_PATH,
        INVALID_PATH
    };
    Response(ResponseKey key, vector<string> values);
    Response& operator=(const Response& response);
    virtual ~Response();
    ResponseKey GetKey() const;
    string GetValue() const;
private:
    ResponseKey m_key;
    string m_value;
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