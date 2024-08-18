// [file name] : fixedsizepoint3dcontainer.hpp
// [function] : declare the FixedSizePoint3DContainer class
// [author] : Huayu Chen
// [date] : 2024/8/2

// [edit history] :
// -----------------------------------------------------------
// date: 2024/8/2
// author: Huayu Chen
// edit: init FixedSizePoint3DContainer class
// reason: to support storing a fixed number of 3D points in a container
//         and provide basic functions to operate on the container
// -----------------------------------------------------------
// date: 2024/8/3
// author: Huayu Chen
// edit: add ToString function
//      add operator<< function
// reason: to support converting the container to a string 
//         for display and output to a stream
// -----------------------------------------------------------

#ifndef FIXEDSIZEPOINT3DCONTAINER_HPP
#define FIXEDSIZEPOINT3DCONTAINER_HPP

#include <vector>
#include <string>
#include <ostream>

#include "point3d.hpp"

using namespace std;

// notes for the FixedSizePoint3DContainer class
// -----------------------------------------------------------
// [class name] : FixedSizePoint3DContainer
// [function] : store a fixed number of 3D points in a container
// [notes on interface] :
// 1. since the container is fixed size, the number of points in the container
//    is determined by the size of the vector passed to the constructor, and 
//    cannot be changed, so there is no function to add or delete points.
// 2. there are constant getters to get the points and a point by index, and 
//    a function to modify a point by index.
// 3. there is a function to convert the container to a vector of strings, 
//    each string represents a point.
// 4. the container can be output to a stream.
// [author] : Huayu Chen
// [date] : 2024/8/2
// -----------------------------------------------------------


class FixedSizePoint3DContainer
{
public:
    // constructor, init with a vector of points
    FixedSizePoint3DContainer(const vector<Point3D>& points);
    // copy constructor
    FixedSizePoint3DContainer(const FixedSizePoint3DContainer& container);
    // getter of points
    vector<Point3D> GetPoints() const;
    // getter of a point by index
    Point3D GetPoint(unsigned int index) const;
    // modify a point by index
    void ModifyPoint(unsigned int index, const Point3D& point);
    // convert the container to a vector of strings
    vector<string> ToStrings() const;
    // support output to a stream
    ostream& operator<<(ostream& os) const;
    // check if two containers are the same
    bool operator==(const FixedSizePoint3DContainer& container) const;
    // check if two containers are different
    bool operator!=(const FixedSizePoint3DContainer& container) const;
    // check if a point is in the container
    bool IsPoint3DInContainer(const Point3D& point) const;
    // virtual destructor
    virtual ~FixedSizePoint3DContainer();
    // getter of size
    const unsigned int& Size{m_uiSize};
    // support output to a stream
    friend ostream& operator<<(ostream& os, 
                            const FixedSizePoint3DContainer& container);


private:
    // private member variables, a vector of points 
    // and the size of the container
    vector<Point3D> m_points;
    unsigned int m_uiSize;

    // convert a vector of strings to a vector of points
    static vector<Point3D> StringsToPoints(const vector<string>& pointStrings);
    // convert a string to a point
    static Point3D StringToPoint(const string& pointString);
};

#endif // FIXEDSIZEPOINT3DCONTAINER_HPP