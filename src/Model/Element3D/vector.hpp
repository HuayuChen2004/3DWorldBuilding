// the vector class is a class that represents a n-dim vector
// it is the base for the point class
// a point can be seen as a vector that starts at the origin
// and a point should be able to be initiated with a vector
// some vector operations can also be used on points
// edit logging:
// -----------------------------------------------------------
// date: 2024/7/20
// author: Huayu Chen
// edit: init vector class
//       add vector operations
//       add some common math functions
//       add some common statistics functions
// reason: to support various operations on vectors
//         so that the vector class can be used in many places
//         and can be extended to support more operations
// -----------------------------------------------------------





// -----------------------------------------------------------
// code below

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;




class Vector
{
private:
    vector<double> data;
    unsigned int m_uiDim;
public:
    Vector(const vector<double>& data);
    Vector(const Vector& vec);
    virtual ~Vector();

    vector<double> GetData() const;
    void ModifyData(const vector<double>& data);

    double operator[](unsigned int index) const;
    double& operator[](unsigned int index);
    Vector operator+(const Vector& vec) const;
    Vector operator-(const Vector& vec) const;
    double operator*(const Vector& vec) const;
    Vector operator*(double scalar) const;
    Vector operator/(double scalar) const;
    Vector& operator=(const Vector& vec);
    Vector& operator+=(const Vector& vec);
    Vector& operator-=(const Vector& vec);
    Vector& operator*=(double scalar);
    Vector& operator/=(double scalar);
    bool operator==(const Vector& vec) const;
    bool operator!=(const Vector& vec) const;

    double Norm(unsigned int p = 2) const;
    double Length() const;
    double Dot(const Vector& vec) const;
    Vector Normalize(unsigned int p = 2) const;
    Vector Cross(const Vector& vec) const;
    double AngleFrom(const Vector& vec) const;
    double Distance(const Vector& vec) const;
    bool IsParallel(const Vector& vec) const;
    bool IsOrthogonal(const Vector& vec) const;
    Vector Project(const Vector& vec) const;
    Vector Reject(const Vector& vec) const;
    Vector Rotate(const Vector& axis, double angle) const;
    bool IsZero() const;
    bool IsUnit() const;

    Vector InsertDimension(unsigned int dim, double value = 0.0) const;
    Vector RemoveDimension(unsigned int dim) const;
    Vector Lerp(const Vector& vec, double t) const;

    vector<double>::iterator begin();
    vector<double>::iterator end();
    vector<double>::const_iterator begin() const;
    vector<double>::const_iterator end() const;
    
    Vector Slice(unsigned int start, unsigned int end) const;
    Vector Slice(unsigned int start) const;

    Vector Reverse() const;
    Vector Opposite() const;
    Vector Abs() const;
    Vector Round() const;
    Vector Ceil() const;
    Vector Floor() const;
    Vector Clamp(double min, double max) const;

    Vector Reflection(const Vector& normal) const;
    Vector Refraction(const Vector& normal, double n1, double n2) const;

    double Max() const;
    double Min() const;
    double Sum() const;
    double Product() const;
    double Mean() const;
    double Variance() const;
    double StandardDeviation() const;
    double Median() const;
    double Mode() const;
    Vector Inversion() const;
    Vector Log() const;
    Vector Exp() const;
    Vector Pow(double p) const;
    Vector Sqrt() const;
    Vector Cbrt() const;
    Vector Sin() const;
    Vector Cos() const;
    Vector Tan() const;
    Vector Asin() const;
    Vector Acos() const;
    Vector Atan() const;
    Vector Sinh() const;
    Vector Cosh() const;
    Vector Tanh() const;
    Vector Asinh() const;
    Vector Acosh() const;
    Vector Atanh() const;
    Vector DegreeToRadian() const;
    Vector RadianToDegree() const;
    Vector Map(double (*func)(double)) const;
    unsigned int Count(double value) const;
    Vector Sort() const;
    Vector Unique() const;
    Vector Filter(double (*func)(double)) const;
    Vector Replace(double oldValue, double newValue) const;
    Vector Round(double step) const;
    Vector Ceil(double step) const;
    Vector Floor(double step) const;
    Vector Clamp(double min, double max, double step) const;
    unsigned int ArgMax() const;
    unsigned int ArgMin() const;
    Vector Transpose() const;
    Vector Concatenate(const Vector& vec) const;
    Vector Repeat(unsigned int n) const;
    unsigned int Find(double value) const;
    string ToString() const;

    static double Norm(const Vector& vec, unsigned int p = 2);
    static double Length(const Vector& vec);

    static double Dot(const Vector& vec1, const Vector& vec2);
    static double Angle(const Vector& vec1, const Vector& vec2);
    static Vector Normalize(const Vector& vec, unsigned int p = 2);
    static Vector Project(const Vector& vec1, const Vector& vec2);
    static Vector Reject(const Vector& vec1, const Vector& vec2);
    static Vector Rotate(const Vector& vec, const Vector& axis, double angle);
    static Vector Reflection(const Vector& vec, const Vector& normal);
    static Vector Refraction(const Vector& vec, const Vector& normal, double n1, double n2);
    static Vector Inversion(const Vector& vec);
    static Vector Log(const Vector& vec);
    static Vector Exp(const Vector& vec);
    static Vector Pow(const Vector& vec, double power);
    static Vector Sqrt(const Vector& vec);
    static Vector Cbrt(const Vector& vec);
    static Vector Sin(const Vector& vec);
    static Vector Cos(const Vector& vec);
    static Vector Tan(const Vector& vec);
    static Vector Asin(const Vector& vec);
    static Vector Acos(const Vector& vec);
    static Vector Atan(const Vector& vec);
    static Vector Sinh(const Vector& vec);
    static Vector Cosh(const Vector& vec);
    static Vector Tanh(const Vector& vec);
    static Vector Asinh(const Vector& vec);
    static Vector Acosh(const Vector& vec);
    static Vector Atanh(const Vector& vec);
    static Vector DegreeToRadian(const Vector& vec);
    static Vector RadianToDegree(const Vector& vec);

    static double Distance(const Vector& vec1, const Vector& vec2);
    static double Distance2(const Vector& vec1, const Vector& vec2);
    static Vector Cross(const Vector& vec1, const Vector& vec2);
    static Vector Lerp(const Vector& vec1, const Vector& vec2, double t);
    static Vector Random(unsigned int dim, double min, double max);
    static Vector RandomUnit(unsigned int dim);
    static Vector RandomNormal(unsigned int dim, double mean, double std);

    static Vector Zeros(unsigned int dim);
    static Vector Ones(unsigned int dim);
    static Vector Constant(unsigned int dim, double value);
    static Vector Range(unsigned int dim, double start, double end, double step = 1.0);
    static Vector Linspace(unsigned int dim, double start, double end, unsigned int num);
    static Vector Meshgrid(const Vector& x, const Vector& y);
    static Vector Concatenate(const vector<Vector>& vecs);
    static Vector Repeat(const Vector& vec, unsigned int n);
    static Vector Transpose(const Vector& vec);
    static Vector Filter(const Vector& vec, double (*func)(double));
    static Vector Replace(const Vector& vec, double oldValue, double newValue);
    static Vector Round(const Vector& vec, double step);
    static Vector Ceil(const Vector& vec, double step);
    static Vector Floor(const Vector& vec, double step);
    static Vector Clamp(const Vector& vec, double min, double max, double step);
    static unsigned int ArgMax(const Vector& vec);
    static unsigned int ArgMin(const Vector& vec);
    static Vector Sort(const Vector& vec);
    static Vector Unique(const Vector& vec);
    static unsigned int Count(const Vector& vec, double value);
    static unsigned int Find(const Vector& vec, double value);
    static double Max(const Vector& vec);
    static double Min(const Vector& vec);
    static double Sum(const Vector& vec);
    static double Product(const Vector& vec);
    static double Mean(const Vector& vec);
    static double Variance(const Vector& vec);
    static double StandardDeviation(const Vector& vec);
    static double Median(const Vector& vec);
    static double Mode(const Vector& vec);
    static Vector Abs(const Vector& vec);
    static Vector Round(const Vector& vec);
    static Vector Ceil(const Vector& vec);
    static Vector Floor(const Vector& vec);
    static Vector Clamp(const Vector& vec, double min, double max);
    static Vector Map(const Vector& vec, double (*func)(double));
    static bool IsLinearIndependent(const vector<Vector>& vecs);

    static const unsigned int MAX_DIM {999u};
    static const unsigned int MIN_DIM {1u};
    const unsigned int& Dim {m_uiDim};


    friend ostream& operator<<(ostream& os, const Vector& vec);
};

#endif // VECTOR_HPP