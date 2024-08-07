// this is a container for a fixed number of 3D points
// it is the base class for line3d and face3d
// edit logging:
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
// 


#ifndef FIXEDSIZEPOINT3DCONTAINER_HPP
#define FIXEDSIZEPOINT3DCONTAINER_HPP

#include <vector>
#include <string>
#include <ostream>

#include "point3d.hpp"

using namespace std;

class FixedSizePoint3DContainer
{
public:
    FixedSizePoint3DContainer(const vector<Point3D>& points);
    FixedSizePoint3DContainer(const FixedSizePoint3DContainer& container);
    vector<Point3D> GetPoints() const;
    Point3D GetPoint(unsigned int index) const;
    void ModifyPoint(unsigned int index, const Point3D& point);
    vector<string> ToStrings() const;
    ostream& operator<<(ostream& os) const;
    bool operator==(const FixedSizePoint3DContainer& container) const;
    bool operator!=(const FixedSizePoint3DContainer& container) const;
    bool IsPoint3DInContainer(const Point3D& point) const;
    virtual ~FixedSizePoint3DContainer();
    static vector<Point3D> StringsToPoints(const vector<string>& pointStrings);
    const unsigned int& Size{m_uiSize};
    friend ostream& operator<<(ostream& os, 
                            const FixedSizePoint3DContainer& container);


private:
    vector<Point3D> m_points;
    unsigned int m_uiSize;

    static Point3D StringToPoint(const string& pointString);
};

#endif // FIXEDSIZEPOINT3DCONTAINER_HPP