// this is the header file for the line class
// a line is made up of two points
// the line class can be used to calculate the distance between two points
// the line class can also be used to calculate the intersection of two lines
// edit logging:
// -----------------------------------------------------------
// date: 2024/7/20
// author: Huayu Chen
// edit: init line class
//       add line operations
//       add some common math functions
// reason: to support various operations on lines
//         so that the line class can be used in many places
//         and can be extended to support more operations
// -----------------------------------------------------------

#ifndef LINE_HPP
#define LINE_HPP

class Point;

class Line {
public:
    Line(const Point& p1, const Point& p2);
    Line(const Line& line);
    virtual ~Line();

    double Distance(const Point& p) const;
    Point Intersection(const Line& line) const;

    Point GetP1() const;
    Point GetP2() const;

private:
    Point* m_pp1;
    Point* m_pp2;
};

#endif // LINE_HPP