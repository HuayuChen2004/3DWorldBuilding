// [file name] : controller.hpp
// [function] : declare the class controller
// [author] : Huayu Chen
// [date] : 2024/7/31

// [edit history] :
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

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include "../Model/Element3D/face3d.hpp"
#include "../Model/Element3D/point3d.hpp"
#include "../Model/Element3D/line3d.hpp"
#include "../Model/Model3D/model3d.hpp"
#include "../Message/argument.hpp"
#include "../Message/response.hpp"

using namespace std;

// notes on the class controller
// -----------------------------------------------------------
// [class name] : Controller
// [function] : control the operations on the 3D model
//              and interact with the viewer
// [notes on interface] : 
// 1. The controller class in this program 
//    is a class with only one instance, so the constructor is private
//    and the only way to get an instance of the controller is to call the 
//    static GetInstance() function.
// 2. The operations on the model are encapsulated in the HandleArguments 
//    function. Supported operations can be found in the Argument class.
// [author] : Huayu Chen
// [date] : 2024/7/31
// -----------------------------------------------------------

class Controller
{
public:
    // get instance of controller
    // singleton pattern, only one instance of controller is allowed
    static Controller* GetInstance();
    // handle the arguments passed from the viewer
    // and return the response to the viewer
    Response HandleArguments(vector<Argument> arguments);

private:
    // singleton pattern, the only instance
    static Controller* m_instance;
    // private constructor, since it is a singleton pattern
    Controller() {} 
    // delete copy constructor and assignment operator
    Controller(const Controller&) = delete; 
    void operator=(const Controller&) = delete; 
    // functions to operate the model
    // function 1: import 3D model from a file
    void Import3DModel(const string& path);
    // function 2: export 3D model to a file
    void Export3DModel(const string& path);
    // function 3: delete a face from the model
    void DeleteFace(unsigned int FaceIndex);
    // function 4: add a face to the model
    void AddFace(const Face3D& face);
    // function 5: modify a point of a face
    void ModifyFacePoint(unsigned int FaceIndex, unsigned int PointIndex, 
                        const Point3D& point);
    // function 6: add a line to the model
    void AddLine(const Line3D& line);
    // function 7: delete a line from the model
    void DeleteLine(unsigned int LineIndex);
    // function 8: modify a point of a line
    void ModifyLinePoint(unsigned int LineIndex, unsigned int PointIndex, 
                        const Point3D& point);
    // other functions about displaying the model is implemented in the viewer
    // support operations on only one model 
    shared_ptr<Model3D> m_model;
};

#endif // CONTROLLER_HPP