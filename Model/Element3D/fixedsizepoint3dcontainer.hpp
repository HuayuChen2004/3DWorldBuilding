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


#ifndef FIXEDSIZEPOINT3DCONTAINER_HPP
#define FIXEDSIZEPOINT3DCONTAINER_HPP

#include <vector>
#include "point3d.hpp"

using namespace std;

class FixedSizePoint3DContainer
{
public:
    FixedSizePoint3DContainer(unsigned int size);
    vector<Point3D> GetPoints() const;
    Point3D GetPoint(unsigned int index) const;
    void ModifyPoint(unsigned int index, const Point3D& point);
    string ToString() const;
    ostream& operator<<(ostream& os) const;

private:
    vector<Point3D> m_points;
};

#endif // FIXEDSIZEPOINT3DCONTAINER_HPP