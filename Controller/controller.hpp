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
// reason: to support various operations on the model and interactions with 
//         the viewer, we need a controller class to manage the model and viewer
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
// date: 2024/8/2
// author: Huayu Chen
// edit: add some error catch
//       add GetInstance function
// reason: to support handling some error
//         and to support singleton pattern
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
        NOT_OBJ_PATH,
        NOT_EXIST_PATH,
        IMPORT_SUCCESS,
        EXPORT_SUCCESS,
        DELETE_FACE_SUCCESS,
        ADD_FACE_SUCCESS,
        MODIFY_FACE_POINT_SUCCESS,
        DELETE_LINE_SUCCESS,
        ADD_LINE_SUCCESS,
        MODIFY_LINE_POINT_SUCCESS,
        UNKNOWN,
        EXPORT_FAILED,
        IMPORT_FAILED,
        DISPLAY_ALL_FACES,
        DISPLAY_FACE_POINTS,
        DISPLAY_ALL_LINES,
        DISPLAY_LINE_POINTS,
        DISPLAY_STATISTICS,
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
    static Controller* GetInstance();
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

    
    static Controller* m_instance;
    Controller() {} // 私有构造函数
    Controller(const Controller&) = delete; // 删除拷贝构造函数
    void operator=(const Controller&) = delete; // 删除拷贝赋值运算符

    void Import3DModel(const string& path);
    //
    void Export3DModel(const string& path);
    //word里面2.几那些功能最好每一个写一个函数

    void DeleteFace(unsigned int FaceIndex);
    void AddFace(const Face3D& face);

    void ModifyFacePoint(unsigned int FaceIndex, unsigned int PointIndex, 
                        const Point3D& point);

    void AddLine(const Line3D& line);
    void DeleteLine(unsigned int LineIndex);

    void ModifyLinePoint(unsigned int LineIndex, unsigned int PointIndex, 
                        const Point3D& point);
    //
    // support only one model 
    shared_ptr<Model3D> m_model;
    //
    //`




};
















#endif // CONTROLLER_HPP