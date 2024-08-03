// this is the header file of Model3D class
// the class Model3D is a class that represents a 3D model 
// in a three-dimensional space
// a model3d can be initiated with a vector of faces and a vector of lines
// some operations can also be used on model3d
// edit logging:
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
//
//
//
//
//
//
//
//
//

// 2.3三维模型修改。逻辑上，一个三维模型（Model3D）包含了两类元素
// （Element3D）：面（Face3D）和线（Line3D）。Face3D描述的是空间三角形，
// 由三个顶点（Point3D）构成。空间共面多边形（闭合图形，所有点共面）和
// 空间非共面多边形（闭合图形，不需所有点共面）均拆分为多个Face3D，
// 无需单独表示，可不考虑额外的类设计。Line3D描述的是空间线段，
// 两个端点均为Point3D。

// 2.3.1 列出所有Face3D对象，显示其序号和三个顶点坐标，面积。显示格式自拟。

// 2.3.2 删除指定Face3D对象。

// 2.3.3 通过给定三顶点坐标，向模型中添加一个非重复的Face3D（模型中不能
// 存在两个完全重合的Face3D）。

// 2.3.4 列出指定Face3D对象中的所有Point3D对象，显示其序号和坐标。显示格式自拟。

// 2.3.5修改指定Face3D对象包含的任一顶点坐标。修改后，Face3D三顶点不可重合。
// 预期修改后Face3D也不可与模型中已有的任何一个Face3D完全重合，如重合则不可修改。
// 注：此为Face3D修改模式。如果存在2个Face3D对象，有顶点重合，修改一个Face3D的顶点，
// 不影响另一个Face3D的顶点。

// 2.3.6 列出所有Line3D对象，显示其序号和两个顶点坐标，长度。显示格式自拟。

// 2.3.7 删除指定Line3D对象。

// 2.3.8通过给定两顶点坐标，向模型中添加一个非重复的Line3D（模型中不能
// 存在两个完全重合的Line3D）

// 2.3.9 列出指定Line3D对象中的所有Point3D对象，显示其序号和坐标。显示格式自拟。

// 2.3.10修改指定Line3D对象任一顶点坐标。修改后，Line3D对象中两顶点不可重合。
// 预期修改后Line3D也不可与模型中已有的任何一个Line3D完全重合，如重合则不可修改。
// 注：此为Line3D修改模式。如果存在2个Line3D对象，有顶点重合，修改一个Line3D的顶点，
// 不影响另一个Line3D的顶点。

// 2.4显示统计信息：模型中Face3D总数和总面积，Line3D总数和总长度，
// Point3D总数（空间坐标重叠的顶点重复计数），包围盒体积（能框住所有Point3D的
// 最小立方体体积，立方体各边分别与三维坐标轴平行）。





#ifndef MODEL3D_HPP
#define MODEL3D_HPP

#include <vector>
#include <memory>
#include "../Element3D/face3d.hpp"
#include "../Element3D/line3d.hpp"
#include "../Element3D/point3d.hpp"

using namespace std;


class Face3D;
class Line3D;
class Point3D;

class Model3D {
public:
    Model3D(vector<Face3D> faces, vector<Line3D> lines);  
    virtual ~Model3D();
    Model3D& operator=(const Model3D& model);

    // void DisplayAllFaces() const;
    void DeleteFace(unsigned int index);
    void AddFace(const Face3D& face);
    // void DisplayFacePoints(int index) const;
    void ModifyFacePoint(unsigned int FaceIndex, 
                        unsigned int PointIndex, const Point3D& new_point);

    // void DisplayAllLines() const;
    void DeleteLine(unsigned int index);
    void AddLine(const Line3D& line);
    // void DisplayLinePoints(int index) const;
    void ModifyLinePoint(unsigned int LineIndex, 
                        unsigned int PointIndex, const Point3D& new_point);

    // void DisplayStatistics() const;
    const vector<shared_ptr<Face3D>>& GetFaces() const;
    const vector<shared_ptr<Line3D>>& GetLines() const;
    const vector<shared_ptr<Point3D>>& GetPoints() const;

private:
// use shared pointer because the elements 
// are shared among different faces and lines
    vector<shared_ptr<Face3D>> m_vpFaces;
    vector<shared_ptr<Line3D>> m_vpLines;
    vector<shared_ptr<Point3D>> m_vpPoints;
};

















#endif // MODEL3D_HPP