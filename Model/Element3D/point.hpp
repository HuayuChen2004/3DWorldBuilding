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
//
//
//更改记录
//
//
//
//
//
//


#ifndef POINT_HPP
#define POINT_HPP

#include <vector>
using namespace std;

//
//
//
//
//
//
//
//
//更改记录
//
//
//
//
//
//
//
//
//

class Point
{
//
//
public:
    //
    //
    const unsigned int& Dim {m_uiDim};
    //
    double operator[](unsigned int index) const;
    //
    double& operator[](unsigned int index);
    //
    //
    //
    double At(unsigned int index) const;
    //
    // 啥内积外积模等等
    //
    //
    static double Distance(const Point& p1, const Point& p2);
    //
    static double Length(const Point& p);
    //
    static const unsigned int MAX_DIM {999u};
    //
    static const unsigned int MIN_DIM {1u};
    //
    double DistanceFrom(const Point& p) const;
    //
    //
    bool operator==(const Point& p) const;
    //
    //加减乘除等等
    //
    //





//
//
private:
    //
    //
    unsigned int m_uiDim;
    //
    vector<double> m_vdCoords;


};




#endif // POINT_HPP