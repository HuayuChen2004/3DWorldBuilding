// [file name] : model3dimporter.hpp
// [function] : declare the Model3DImporter class
// [author] : Huayu Chen
// [date] : 2024/7/31

// [edit history] :
// -----------------------------------------------------------
// date: 2024/7/31
// author: Huayu Chen
// edit: init model3dimporter class
//       add Load function
// reason: to support importing 3D models from files
// -----------------------------------------------------------
//
//
//
//
//
//
//
//
// this is the header file of the model3dimporter class
// the class model3dimporter is a class that imports 3D models from files
// the class model3dimporter is a base class for other model3d importers
// the class model3dimporter has a virtual function Load that 
// loads a model3d from a file
#ifndef IMPORTER_HPP
#define IMPORTER_HPP
//

//
#include <string>
#include <vector>
#include "../Model3D/model3d.hpp"
#include "../Element3D/face3d.hpp"
#include "../Element3D/line3d.hpp"

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


// 2.1三维模型导入。根据给定文件名，将以特定格式编码存储的三维模型文件，导入到内存，
// 转化为可在内存中编辑的类对象。三维模型文件格式有很多种，要求至少支持obj格式（示例模型
// 文件为cube.obj；obj文件格式说明见附录；示例和自己通过软件导出的obj模型文件可以通过
// https://3dviewer.net在线查看和交互渲染）。说明：要求“至少支持obj格式”的目的（支持导
// 入多种格式的功能，不加分），是促进类架构设计优化，从可能支持多种模型格式的角度，需要考虑导
// 入器(Importer)类的继承体系，而非单独写一个为本作业专用obj导入器。



class Model3DImporter
{
    //
    //
    //
    //
    //
public:
    Model3DImporter();
    virtual ~Model3DImporter();

    virtual Model3D Load(const string& path) const;
    virtual vector<Face3D> LoadFaces(const string& path) const = 0;
    virtual vector<Line3D> LoadLines(const string& path) const = 0;

};








#endif // IMPORTER_HPP