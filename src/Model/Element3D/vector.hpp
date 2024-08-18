// [file name] : vector.hpp
// [function] : declare the Vector class
// [author] : Huayu Chen
// [date] : 2024/7/20

// [edit history] :
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

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

// notes about the class Vector
// -----------------------------------------------------------
// [class name] : Vector
// [function] : represent a n-dim vector
// [notes on interface] :
// 1. the vector is defined by a vector of doubles
// 2. the vector has some common mathematical operations such as addition,
//    subtraction, dot product, cross product, and normalization
// 3. the vector has some common statistical operations such as max, min,
//    sum, product, mean, variance, standard deviation, median, mode, and so on
// 4. the vector has some common mathematical functions such as log, exp, pow,
//    sqrt, cbrt, sin, cos, tan, asin, acos, atan, sinh, cosh, and so on
// 5. the vector can be sliced and reversed
// 6. the vector can be concatenated and repeated
// 7. the vector can be modified using various operations
// 8. the vector can be printed to the console
// [author] : Huayu Chen
// [date] : 2024/8/8
// -----------------------------------------------------------

class Vector
{
private:
    // stores the vector's data as a vector of doubles
    vector<double> data;
    // stores the number of dimensions of the vector
    unsigned int m_uiDim;

public:
    // default constructor that initializes the vector with a single dimension
    Vector();
    // constructor that initializes the vector with a vector of doubles
    Vector(const vector<double>& data);
    // copy constructor that initializes the vector from another vector
    Vector(const Vector& vec);
    // virtual destructor
    virtual ~Vector();

    // returns the vector's data (read-only)
    vector<double> GetData() const;
    // modifies the vector's data
    void ModifyData(const vector<double>& data);

    // returns the value at the given index (read-only)
    double operator[](unsigned int index) const;
    // returns the value at the given index (modifiable)
    double& operator[](unsigned int index);
    // adds two vectors and returns the result
    Vector operator+(const Vector& vec) const;
    // subtracts one vector from another and returns the result
    Vector operator-(const Vector& vec) const;
    // calculates the dot product of two vectors
    double operator*(const Vector& vec) const;
    // multiplies the vector by a scalar and returns the result
    Vector operator*(double scalar) const;
    // divides the vector by a scalar and returns the result
    Vector operator/(double scalar) const;
    // assigns one vector to another
    Vector& operator=(const Vector& vec);
    // adds another vector to this vector and updates this vector
    Vector& operator+=(const Vector& vec);
    // subtracts another vector from this vector and updates this vector
    Vector& operator-=(const Vector& vec);
    // multiplies this vector by a scalar and updates this vector
    Vector& operator*=(double scalar);
    // divides this vector by a scalar and updates this vector
    Vector& operator/=(double scalar);
    // checks if two vectors are equal
    bool operator==(const Vector& vec) const;
    // checks if two vectors are not equal
    bool operator!=(const Vector& vec) const;

    // calculates the p-norm of the vector
    double Norm(unsigned int p = 2) const;
    // calculates the length (Euclidean norm) of the vector
    double Length() const;
    // calculates the dot product of this vector and another vector
    double Dot(const Vector& vec) const;
    // normalizes the vector using the p-norm
    Vector Normalize(unsigned int p = 2) const;
    // calculates the cross product of this vector and another vector
    Vector Cross(const Vector& vec) const;
    // calculates the angle between this vector and another vector
    double AngleFrom(const Vector& vec) const;
    // calculates the distance between this vector and another vector
    double Distance(const Vector& vec) const;
    // checks if this vector is parallel to another vector
    bool IsParallel(const Vector& vec) const;
    // checks if this vector is orthogonal to another vector
    bool IsOrthogonal(const Vector& vec) const;
    // projects this vector onto another vector
    Vector ProjectTo(const Vector& vec) const;
    // checks if the vector is a zero vector
    bool IsZero() const;
    // checks if the vector is a unit vector
    bool IsUnit() const;

    // inserts a dimension into the vector at the specified index
    Vector InsertDimension(unsigned int dim, double value = 0.0) const;
    // removes a dimension from the vector at the specified index
    Vector RemoveDimension(unsigned int dim) const;
    // linearly interpolates between this vector and another vector
    Vector Lerp(const Vector& vec, double t) const;

    // returns an iterator to the beginning of the vector's data
    vector<double>::iterator begin();
    // returns an iterator to the end of the vector's data
    vector<double>::iterator end();
    // returns a constant iterator to the beginning of the vector's data
    vector<double>::const_iterator begin() const;
    // returns a constant iterator to the end of the vector's data
    vector<double>::const_iterator end() const;
    
    // slices the vector from the start index to the end index
    Vector Slice(unsigned int start, unsigned int end) const;
    // slices the vector from the start index to the end of the vector
    Vector Slice(unsigned int start) const;

    // reverses the order of the elements in the vector
    Vector Reverse() const;
    // returns the opposite (negated) vector
    Vector Opposite() const;
    // returns the absolute value of each element in the vector
    Vector Abs() const;
    // rounds each element in the vector to the nearest integer
    Vector Round() const;
    // returns the ceiling of each element in the vector
    Vector Ceil() const;
    // returns the floor of each element in the vector
    Vector Floor() const;
    // clamps each element in the vector to the specified range
    Vector Clamp(double min, double max) const;

    // reflects the vector across the specified normal vector
    Vector Reflection(const Vector& normal) const;
    // refracts the vector across the specified normal vector using the given refractive indices
    Vector Refraction(const Vector& normal, double n1, double n2) const;

    // returns the maximum value in the vector
    double Max() const;
    // returns the minimum value in the vector
    double Min() const;
    // returns the sum of all elements in the vector
    double Sum() const;
    // returns the product of corresponding elements in this vector and another vector
    double Product(const Vector& vec) const;
    // returns the mean (average) of all elements in the vector
    double Mean() const;
    // returns the variance of the elements in the vector
    double Variance() const;
    // returns the standard deviation of the elements in the vector
    double StandardDeviation() const;
    // returns the median of the elements in the vector
    double Median() const;
    // returns the mode of the elements in the vector
    double Mode() const;
    // returns the inversion of each element in the vector
    Vector Inversion() const;
    // returns the natural logarithm of each element in the vector
    Vector Log() const;
    // returns the exponential of each element in the vector
    Vector Exp() const;
    // raises each element in the vector to the specified power
    Vector Pow(double p) const;
    // returns the square root of each element in the vector
    Vector Sqrt() const;
    // returns the cube root of each element in the vector
    Vector Cbrt() const;
    // returns the sine of each element in the vector
    Vector Sin() const;
    // returns the cosine of each element in the vector
    Vector Cos() const;
    // returns the tangent of each element in the vector
    Vector Tan() const;
    // returns the arcsine of each element in the vector
    Vector Asin() const;
    // returns the arccosine of each element in the vector
    Vector Acos() const;
    // returns the arctangent of each element in the vector
    Vector Atan() const;
    // returns the hyperbolic sine of each element in the vector
    Vector Sinh() const;
    // returns the hyperbolic cosine of each element in the vector
    Vector Cosh() const;
    // returns the hyperbolic tangent of each element in the vector
    Vector Tanh() const;
    // returns the hyperbolic arcsine of each element in the vector
    Vector Asinh() const;
    // returns the hyperbolic arccosine of each element in the vector
    Vector Acosh() const;
    // returns the hyperbolic arctangent of each element in the vector
    Vector Atanh() const;
    // converts each element in the vector from degrees to radians
    Vector DegreeToRadian() const;
    // converts each element in the vector from radians to degrees
    Vector RadianToDegree() const;
    // applies a custom function to each element in the vector
    Vector Map(double (*func)(double)) const;
    // counts the occurrences of a specified value in the vector
    unsigned int Count(double value) const;
    // sorts the elements in the vector in ascending order
    Vector Sort() const;
    // removes duplicate elements from the vector
    Vector Unique() const;
    // filters the vector based on a custom function
    Vector Filter(double (*func)(double)) const;
    // replaces occurrences of an old value with a new value in the vector
    Vector Replace(double oldValue, double newValue) const;
    // rounds each element in the vector to the nearest multiple of the specified step
    Vector Round(double step) const;
    // returns the ceiling of each element in the vector based on the specified step
    Vector Ceil(double step) const;
    // returns the floor of each element in the vector based on the specified step
    Vector Floor(double step) const;
    // clamps each element in the vector to the specified range, considering the specified step
    Vector Clamp(double min, double max, double step) const;
    // returns the index of the maximum value in the vector
    unsigned int ArgMax() const;
    // returns the index of the minimum value in the vector
    unsigned int ArgMin() const;
    // concatenates this vector with another vector and returns the result
    Vector Concatenate(const Vector& vec) const;
    // repeats the vector n times and returns the result
    Vector Repeat(unsigned int n) const;
    // finds the index of the first occurrence of a specified value in the vector
    unsigned int Find(double value) const;
    // converts the vector to a string representation
    string ToString() const;

    // static method that calculates the p-norm of a vector
    static double Norm(const Vector& vec, unsigned int p = 2);
    // static method that calculates the length (Euclidean norm) of a vector
    static double Length(const Vector& vec);

    // static method that calculates the dot product of two vectors
    static double Dot(const Vector& vec1, const Vector& vec2);
    // static method that calculates the angle between two vectors
    static double Angle(const Vector& vec1, const Vector& vec2);
    // static method that normalizes a vector using the p-norm
    static Vector Normalize(const Vector& vec, unsigned int p = 2);
    // static method that projects one vector onto another
    static Vector Project(const Vector& vec1, const Vector& vec2);
    // static method that reflects a vector across a normal vector
    static Vector Reflection(const Vector& vec, const Vector& normal);
    // static method that refracts a vector across a normal vector using the given refractive indices
    static Vector Refraction(const Vector& vec, const Vector& normal, double n1, double n2);
    // static method that returns the inversion of each element in a vector
    static Vector Inversion(const Vector& vec);
    // static method that returns the natural logarithm of each element in a vector
    static Vector Log(const Vector& vec);
    // static method that returns the exponential of each element in a vector
    static Vector Exp(const Vector& vec);
    // static method that raises each element in a vector to a specified power
    static Vector Pow(const Vector& vec, double power);
    // static method that returns the square root of each element in a vector
    static Vector Sqrt(const Vector& vec);
    // static method that returns the cube root of each element in a vector
    static Vector Cbrt(const Vector& vec);
    // static method that returns the sine of each element in a vector
    static Vector Sin(const Vector& vec);
    // static method that returns the cosine of each element in a vector
    static Vector Cos(const Vector& vec);
    // static method that returns the tangent of each element in a vector
    static Vector Tan(const Vector& vec);
    // static method that returns the arcsine of each element in a vector
    static Vector Asin(const Vector& vec);
    // static method that returns the arccosine of each element in a vector
    static Vector Acos(const Vector& vec);
    // static method that returns the arctangent of each element in a vector
    static Vector Atan(const Vector& vec);
    // static method that returns the hyperbolic sine of each element in a vector
    static Vector Sinh(const Vector& vec);
    // static method that returns the hyperbolic cosine of each element in a vector
    static Vector Cosh(const Vector& vec);
    // static method that returns the hyperbolic tangent of each element in a vector
    static Vector Tanh(const Vector& vec);
    // static method that returns the hyperbolic arcsine of each element in a vector
    static Vector Asinh(const Vector& vec);
    // static method that returns the hyperbolic arccosine of each element in a vector
    static Vector Acosh(const Vector& vec);
    // static method that returns the hyperbolic arctangent of each element in a vector
    static Vector Atanh(const Vector& vec);
    // static method that converts each element in a vector from degrees to radians
    static Vector DegreeToRadian(const Vector& vec);
    // static method that converts each element in a vector from radians to degrees
    static Vector RadianToDegree(const Vector& vec);

    // static method that calculates the distance between two vectors
    static double Distance(const Vector& vec1, const Vector& vec2);
    // static method that calculates the cross product of two vectors
    static Vector Cross(const Vector& vec1, const Vector& vec2);
    // static method that linearly interpolates between two vectors
    static Vector Lerp(const Vector& vec1, const Vector& vec2, double t);
    // static method that generates a random vector with the specified dimension and range
    static Vector Random(unsigned int dim, double min, double max);
    // static method that generates a random unit vector with the specified dimension
    static Vector RandomUnit(unsigned int dim);
    // static method that generates a random vector with a normal distribution
    static Vector RandomNormal(unsigned int dim, double mean, double std);

    // static method that generates a vector of zeros with the specified dimension
    static Vector Zeros(unsigned int dim);
    // static method that generates a vector of ones with the specified dimension
    static Vector Ones(unsigned int dim);
    // static method that generates a vector with a constant value
    static Vector Constant(unsigned int dim, double value);
    // static method that generates a range vector from start to end with the specified step
    static Vector Range(unsigned int dim, double start, double end, double step = 1.0);
    // static method that generates a linearly spaced vector from start to end with the specified number of elements
    static Vector Linspace(unsigned int dim, double start, double end, unsigned int num);
    // static method that concatenates multiple vectors
    static Vector Concatenate(const vector<Vector>& vecs);
    // static method that repeats a vector n times
    static Vector Repeat(const Vector& vec, unsigned int n);
    // static method that filters a vector based on a custom function
    static Vector Filter(const Vector& vec, double (*func)(double));
    // static method that replaces occurrences of an old value with a new value in a vector
    static Vector Replace(const Vector& vec, double oldValue, double newValue);
    // static method that rounds each element in a vector to the nearest multiple of the specified step
    static Vector Round(const Vector& vec, double step);
    // static method that returns the ceiling of each element in a vector based on the specified step
    static Vector Ceil(const Vector& vec, double step);
    // static method that returns the floor of each element in a vector based on the specified step
    static Vector Floor(const Vector& vec, double step);
    // static method that clamps each element in a vector to the specified range, considering the specified step
    static Vector Clamp(const Vector& vec, double min, double max, double step);
    // static method that returns the index of the maximum value in a vector
    static unsigned int ArgMax(const Vector& vec);
    // static method that returns the index of the minimum value in a vector
    static unsigned int ArgMin(const Vector& vec);
    // static method that sorts the elements in a vector in ascending order
    static Vector Sort(const Vector& vec);
    // static method that removes duplicate elements from a vector
    static Vector Unique(const Vector& vec);
    // static method that counts the occurrences of a specified value in a vector
    static unsigned int Count(const Vector& vec, double value);
    // static method that finds the index of the first occurrence of a specified value in a vector
    static unsigned int Find(const Vector& vec, double value);
    // static method that returns the maximum value in a vector
    static double Max(const Vector& vec);
    // static method that returns the minimum value in a vector
    static double Min(const Vector& vec);
    // static method that returns the sum of all elements in a vector
    static double Sum(const Vector& vec);
    // static method that returns the product of corresponding elements in two vectors
    static double Product(const Vector& vec1, const Vector& vec2);
    // static method that returns the mean (average) of all elements in a vector
    static double Mean(const Vector& vec);
    // static method that returns the variance of the elements in a vector
    static double Variance(const Vector& vec);
    // static method that returns the standard deviation of the elements in a vector
    static double StandardDeviation(const Vector& vec);
    // static method that returns the median of the elements in a vector
    static double Median(const Vector& vec);
    // static method that returns the mode of the elements in a vector
    static double Mode(const Vector& vec);
    // static method that returns the absolute value of each element in a vector
    static Vector Abs(const Vector& vec);
    // static method that rounds each element in a vector to the nearest integer
    static Vector Round(const Vector& vec);
    // static method that returns the ceiling of each element in a vector
    static Vector Ceil(const Vector& vec);
    // static method that returns the floor of each element in a vector
    static Vector Floor(const Vector& vec);
    // static method that clamps each element in a vector to the specified range
    static Vector Clamp(const Vector& vec, double min, double max);
    // static method that applies a custom function to each element in a vector
    static Vector Map(const Vector& vec, double (*func)(double));
    // static method that checks if a set of vectors is linearly independent
    static bool IsLinearIndependent(const vector<Vector>& vecs);

    // maximum allowed dimension for the vector
    static const unsigned int MAX_DIM {999u};
    // minimum allowed dimension for the vector
    static const unsigned int MIN_DIM {1u};
    // reference to the number of dimensions of the vector (read-only)
    const unsigned int& Dim {m_uiDim};

    // friend function that allows the vector to be output to a stream
    friend ostream& operator<<(ostream& os, const Vector& vec);
};


#endif // VECTOR_HPP