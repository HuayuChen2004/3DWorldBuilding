// [file name] : vector.cpp
// [function] : implement the Vector class
// [author] : Huayu Chen
// [date] : 2024/8/5

// [edit history] :
// -----------------------------------------------------------
// date: 2024/8/5
// author: Huayu Chen
// edit: add implementation of the Vector class
// reason: to support storing the vector in the 3D space
// -----------------------------------------------------------

#include "vector.hpp"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cmath>


using namespace std;

const double PI = 3.14159265358979323846;

// -----------------------------------------------------------
// [name] : Vector
// [function] : constructor of the Vector class
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector::Vector() {
    m_uiDim = 1;
    data = {0};
}

// -----------------------------------------------------------
// [name] : Vector
// [function] : constructor of the Vector class
// [input] : a vector of double
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector::Vector(const vector<double>& coords) {
    m_uiDim = coords.size();
    data = coords;
}

// -----------------------------------------------------------
// [name] : Vector
// [function] : copy constructor of the Vector class
// [input] : a Vector object
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector::Vector(const Vector& vec) {
    m_uiDim = vec.m_uiDim;
    data = vec.data;
}

// -----------------------------------------------------------
// [name] : operator=
// [function] : assignment operator of the Vector class
// [input] : a Vector object
// [output] : reference to the current Vector object
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector& Vector::operator=(const Vector& vec) {
    m_uiDim = vec.m_uiDim;
    data = vec.data;
    return *this;
}

// -----------------------------------------------------------
// [name] : ~Vector
// [function] : destructor of the Vector class
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector::~Vector() {}

// -----------------------------------------------------------
// [name] : operator[]
// [function] : subscript operator for non-const Vector objects
// [input] : an unsigned integer index
// [output] : reference to the element at the specified index
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double& Vector::operator[](unsigned int index) {
    // check if the index is out of range
    if (index >= m_uiDim) {
        throw invalid_argument("Index out of range");
    }
    return data[index];
}

// -----------------------------------------------------------
// [name] : operator[]
// [function] : subscript operator for const Vector objects
// [input] : an unsigned integer index
// [output] : the element at the specified index
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::operator[](unsigned int index) const {
    // check if the index is out of range
    if (index >= m_uiDim) {
        throw invalid_argument("Index out of range");
    }
    return data[index];
}

// -----------------------------------------------------------
// [name] : operator+
// [function] : addition operator for Vector objects
// [input] : a Vector object
// [output] : a new Vector object that is the sum of the two vectors
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::operator+(const Vector& vec) const {
    // check if the dimensions of the two vectors are the same
    if (m_uiDim != vec.m_uiDim) {
        throw invalid_argument("Vectors must have the same dimension");
    }
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = data[i] + vec.data[i];
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : operator-
// [function] : subtraction operator for Vector objects
// [input] : a Vector object
// [output] : a new Vector object that is the difference of the two vectors
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::operator-(const Vector& vec) const {
    // check if the dimensions of the two vectors are the same
    if (m_uiDim != vec.m_uiDim) {
        throw invalid_argument("Vectors must have the same dimension");
    }
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = data[i] - vec.data[i];
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : operator*
// [function] : scalar multiplication operator for Vector objects
// [input] : a double scalar
// [output] : a new Vector object that is the product of the vector and 
//           the scalar
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::operator*(double scalar) const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = data[i] * scalar;
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Dot
// [function] : computes the dot product of two Vector objects
// [input] : a Vector object
// [output] : a double that is the dot product of the two vectors
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Dot(const Vector& vec) const {
    // check if the dimensions of the two vectors are the same
    if (m_uiDim != vec.m_uiDim) {
        throw invalid_argument("Vectors must have the same dimension");
    }
    double result = 0;
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result += data[i] * vec.data[i];
    }
    return result;
}

// -----------------------------------------------------------
// [name] : Cross
// [function] : computes the cross product of two 3D Vector objects
// [input] : a Vector object
// [output] : a new Vector object that is the cross product of the two vectors
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Cross(const Vector& vec) const {
    // check if the dimensions of the two vectors are 3
    if (m_uiDim != 3 || vec.m_uiDim != 3) {
        throw invalid_argument("Cross product is defined only for 3D vectors");
    }
    double x = data[1] * vec.data[2] - data[2] * vec.data[1];
    double y = data[2] * vec.data[0] - data[0] * vec.data[2];
    double z = data[0] * vec.data[1] - data[1] * vec.data[0];
    return Vector({x, y, z});
}

// -----------------------------------------------------------
// [name] : Length
// [function] : computes the length of the Vector object
// [input] : none
// [output] : a double that is the length of the vector
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Length() const {
    // compute the square of the length
    double result = 0;
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result += data[i] * data[i];
    }
    return sqrt(result);
}

// -----------------------------------------------------------
// [name] : IsParallel
// [function] : checks if two Vector objects are parallel
// [input] : a Vector object
// [output] : a boolean indicating whether the vectors are parallel
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
bool Vector::IsParallel(const Vector& vec) const {
    // check if the dimensions of the two vectors are the same
    if (m_uiDim != vec.m_uiDim) {
        throw invalid_argument("Vectors must have the same dimension");
    }
    double scalar = data[0] / vec.data[0];
    for (unsigned int i = 1; i < m_uiDim; i++) {
        // check if the ratio of the corresponding components is the same
        if (fabs(data[i] / vec.data[i] - scalar) > 1e-6) {
            return false;
        }
    }
    return true;
}

// -----------------------------------------------------------
// [name] : IsOrthogonal
// [function] : checks if two Vector objects are orthogonal
// [input] : a Vector object
// [output] : a boolean indicating whether the vectors are orthogonal
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
bool Vector::IsOrthogonal(const Vector& vec) const {
    // check if the dimensions of the two vectors are the same
    if (m_uiDim != vec.m_uiDim) {
        throw invalid_argument("Vectors must have the same dimension");
    }
    return fabs(Dot(vec)) < 1e-6;
}

// -----------------------------------------------------------
// [name] : AngleFrom
// [function] : calculates the angle between two Vector objects
// [input] : a Vector object
// [output] : a double representing the angle in radians
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::AngleFrom(const Vector& vec) const {
    // check if the dimensions of the two vectors are the same
    if (m_uiDim != vec.m_uiDim) {
        throw invalid_argument("Vectors must have the same dimension");
    }
    // compute the cosine of the angle
    double cosAngle = Dot(vec) / (Length() * vec.Length());
    return acos(cosAngle);
}

// -----------------------------------------------------------
// [name] : GetData
// [function] : retrieves the data of the Vector object
// [input] : none
// [output] : a vector of doubles containing the vector's data
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
vector<double> Vector::GetData() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = data[i];
    }
    return result;
}

// -----------------------------------------------------------
// [name] : Norm
// [function] : calculates the p-norm of the Vector object
// [input] : an unsigned integer representing the norm type
// [output] : a double representing the norm
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Norm(unsigned int p) const {
    // p is the order of the norm
    // check if p is greater than 0
    if (p == 0) {
        throw invalid_argument("p must be greater than 0");
    }
    double result = 0;
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result += pow(fabs(data[i]), p);
    }
    return pow(result, 1.0 / p);
}

// -----------------------------------------------------------
// [name] : IsLinearIndependent
// [function] : checks if a set of Vector objects are linearly independent
// [input] : a vector of Vector objects
// [output] : a boolean indicating whether the vectors are linearly independent
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
bool Vector::IsLinearIndependent(const vector<Vector>& vectors) {
    unsigned int n = vectors.size();
    // check if the number of vectors is greater than the dimension
    // of the vectors
    unsigned int dimension = vectors[0].Dim;
    if (n > dimension) {
        return false;
    }
    // create a matrix with the vectors as columns
    // and check if the matrix is invertible
    vector<vector<double>> matrix(dimension, vector<double>(n));
    // transpose the vectors to form the columns of the matrix
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            matrix[j][i] = vectors[i][j];
        }
    }
    // check if the matrix is invertible
    // by checking if the columns are linearly independent
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < i; j++) {
            for (unsigned int k = 0; k < dimension; k++) {
                // check if the columns are linearly dependent
                if (fabs(matrix[k][i]) < 1e-6) {
                    if (fabs(matrix[k][j]) >= 1e-6) {
                        return true;
                    }
                }
                else if (fabs(matrix[k][j]) < 1e-6) {
                    if (fabs(matrix[k][i]) >= 1e-6) {
                        return true;
                    }
                }
                else if (matrix[k][i] / matrix[k][j] != matrix[k][i]) {
                    return true;
                }
            }
        }
    }
    return false;
}

// -----------------------------------------------------------
// [name] : ModifyData
// [function] : modifies the data of the Vector object
// [input] : a vector of doubles containing new data
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
void Vector::ModifyData(const vector<double>& coords) {
    // check if the new data has the same dimension as the current data
    if (coords.size() != m_uiDim) {
        throw invalid_argument("New data must have the same dimension");
    }
    data = coords;
}

// -----------------------------------------------------------
// [name] : operator<<
// [function] : overloads the << operator for Vector objects
// [input] : an ostream object and a Vector object
// [output] : an ostream object
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
ostream& operator<<(ostream& os, const Vector& vec) {
    // output the vector in the form (x1, x2, ..., xn)
    os << "(";
    for (unsigned int i = 0; i < vec.m_uiDim - 1; i++) {
        os << vec.data[i] << ", ";
    }
    os << vec.data[vec.m_uiDim - 1] << ")";
    return os;
}

// -----------------------------------------------------------
// [name] : operator==
// [function] : checks if two Vector objects are equal
// [input] : a Vector object
// [output] : a boolean indicating whether the vectors are equal
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
bool Vector::operator==(const Vector& vec) const {
    // check if the dimensions of the two vectors are the same
    if (m_uiDim != vec.m_uiDim) {
        return false;
    }
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (fabs(data[i] - vec.data[i]) > 1e-6) {
            return false;
        }
    }
    return true;
}

// -----------------------------------------------------------
// [name] : operator!=
// [function] : checks if two Vector objects are not equal
// [input] : a Vector object
// [output] : a boolean indicating whether the vectors are not equal
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
bool Vector::operator!=(const Vector& vec) const {
    return !(*this == vec);
}

// -----------------------------------------------------------
// [name] : operator/
// [function] : divides the Vector object by a scalar
// [input] : a double representing the scalar
// [output] : a new Vector object
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::operator/(double scalar) const {
    // check if the scalar is zero
    if (fabs(scalar) < 1e-6) {
        throw invalid_argument("Division by zero");
    }
    return *this * (1 / scalar);
}

// -----------------------------------------------------------
// [name] : operator+=
// [function] : adds a Vector object to the current Vector object
// [input] : a Vector object
// [output] : a reference to the current Vector object
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector& Vector::operator+=(const Vector& vec) {
    *this = *this + vec;
    return *this;
}

// -----------------------------------------------------------
// [name] : operator-=
// [function] : subtracts a Vector object from the current Vector object
// [input] : a Vector object
// [output] : a reference to the current Vector object
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector& Vector::operator-=(const Vector& vec) {
    *this = *this - vec;
    return *this;
}

// -----------------------------------------------------------
// [name] : operator*=
// [function] : multiplies the current vector by a scalar and assigns the 
//             result to the current vector
// [input] : a double scalar
// [output] : a reference to the current vector
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector& Vector::operator*=(double scalar) {
    *this = *this * scalar;
    return *this;
}

// -----------------------------------------------------------
// [name] : operator/=
// [function] : divides the current vector by a scalar and assigns the result 
//             to the current vector
// [input] : a double scalar
// [output] : a reference to the current vector
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector& Vector::operator/=(double scalar) {
    *this = *this / scalar;
    return *this;
}

// -----------------------------------------------------------
// [name] : Normalize
// [function] : normalizes the vector to a given p-norm
// [input] : an unsigned integer p representing the norm type
// [output] : a normalized Vector object
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Normalize(unsigned int p) const {
    return *this / Norm(p);
}

// -----------------------------------------------------------
// [name] : Distance
// [function] : calculates the distance between the current vector 
//             and another vector
// [input] : a Vector object
// [output] : a double representing the distance
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Distance(const Vector& vec) const {
    return (*this - vec).Length();
}

// -----------------------------------------------------------
// [name] : ProjectTo
// [function] : projects the current vector onto another vector
// [input] : a Vector object
// [output] : a Vector object representing the projection
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::ProjectTo(const Vector& vec) const {
    return vec * (Dot(vec) / vec.Dot(vec));
}

// -----------------------------------------------------------
// [name] : IsZero
// [function] : checks if the vector is a zero vector
// [input] : none
// [output] : a boolean indicating whether the vector is zero
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
bool Vector::IsZero() const {
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (fabs(data[i]) >= 1e-6) {
            return false;
        }
    }
    return true;
}

// -----------------------------------------------------------
// [name] : IsUnit
// [function] : checks if the vector is a unit vector
// [input] : none
// [output] : a boolean indicating whether the vector is a unit vector
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
bool Vector::IsUnit() const {
    return fabs(Length() - 1) < 1e-6;
}

// -----------------------------------------------------------
// [name] : InsertDimension
// [function] : inserts a new dimension with a specified value into the vector
// [input] : an unsigned integer representing the dimension index 
//           and a double value
// [output] : a Vector object with the new dimension inserted
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::InsertDimension(unsigned int dim, double value) const {
    // check if the index is out of range
    if (dim > m_uiDim) {
        throw invalid_argument("Index out of range");
    }
    // create a new vector with the new dimension inserted
    vector<double> result(m_uiDim + 1);
    for (unsigned int i = 0; i < dim; i++) {
        result[i] = data[i];
    }
    // insert the new dimension with the specified value
    result[dim] = value;
    for (unsigned int i = dim + 1; i < m_uiDim + 1; i++) {
        result[i] = data[i - 1];
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : RemoveDimension
// [function] : removes a dimension from the vector
// [input] : an unsigned integer representing the dimension index
// [output] : a Vector object with the specified dimension removed
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::RemoveDimension(unsigned int dim) const {
    // check if the index is out of range
    if (dim >= m_uiDim) {
        throw invalid_argument("Index out of range");
    }
    // create a new vector with the specified dimension removed
    vector<double> result(m_uiDim - 1);
    for (unsigned int i = 0; i < dim; i++) {
        result[i] = data[i];
    }
    // remove the specified dimension
    for (unsigned int i = dim + 1; i < m_uiDim; i++) {
        result[i - 1] = data[i];
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Lerp
// [function] : performs linear interpolation between the current 
//             vector and another vector
// [input] : a Vector object and a double t representing the 
//             linear interpolation factor
// [output] : a Vector object representing the result of the linear 
//             interpolation
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Lerp(const Vector& vec, double t) const {
    return *this * (1 - t) + vec * t;
}

// -----------------------------------------------------------
// [name] : begin
// [function] : returns an iterator to the beginning of the vector
// [input] : none
// [output] : an iterator to the beginning of the vector
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
vector<double>::iterator Vector::begin() {
    return data.begin();
}

// -----------------------------------------------------------
// [name] : end
// [function] : returns an iterator to the end of the vector
// [input] : none
// [output] : an iterator to the end of the vector
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
vector<double>::iterator Vector::end() {
    return data.end();
}

// -----------------------------------------------------------
// [name] : begin (const version)
// [function] : returns a const iterator to the beginning of the vector
// [input] : none
// [output] : a const iterator to the beginning of the vector
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
vector<double>::const_iterator Vector::begin() const {
    return data.begin();
}

// -----------------------------------------------------------
// [name] : end (const version)
// [function] : returns a const iterator to the end of the vector
// [input] : none
// [output] : a const iterator to the end of the vector
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
vector<double>::const_iterator Vector::end() const {
    return data.end();
}

// -----------------------------------------------------------
// [name] : Slice
// [function] : returns a slice of the vector from a start index to an end index
// [input] : two unsigned integers representing the start and end indices
// [output] : a Vector object representing the slice
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Slice(unsigned int start, unsigned int end) const {
    // check if the indices are valid
    if (start >= end || start >= m_uiDim || end > m_uiDim) {
        throw invalid_argument("Invalid slice range");
    }
    // create a new vector with the slice
    // end is exclusive, so we need to add 1 to the end index
    vector<double> result(end - start);
    for (unsigned int i = start; i < end; i++) {
        result[i - start] = data[i];
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Slice
// [function] : returns a slice of the vector from a start index to 
//              the end of the vector
// [input] : an unsigned integer representing the start index
// [output] : a Vector object representing the slice
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Slice(unsigned int start) const {
    // if end is not specified, slice to the end of the vector
    return Slice(start, m_uiDim);
}

// -----------------------------------------------------------
// [name] : Reverse
// [function] : returns a new vector with the elements in reverse order
// [input] : none
// [output] : a Vector object with the elements in reverse order
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Reverse() const {
    vector<double> result(m_uiDim);
    // reverse the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = data[m_uiDim - 1 - i];
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Opposite
// [function] : returns a new vector with all elements negated
// [input] : none
// [output] : a Vector object with all elements negated
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Opposite() const {
    vector<double> result(m_uiDim);
    // negate all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = -data[i];
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Abs
// [function] : returns a new vector with the absolute values of the elements
// [input] : none
// [output] : a Vector object with the absolute values of the elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Abs() const {
    vector<double> result(m_uiDim);
    // take the absolute value of all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = fabs(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Round
// [function] : returns a new vector with the elements rounded 
//             to the nearest integer
// [input] : none
// [output] : a Vector object with the elements rounded to the nearest integer
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Round() const {
    vector<double> result(m_uiDim);
    // round all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = round(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Ceil
// [function] : returns a new vector with the elements rounded up 
//              to the nearest integer
// [input] : none
// [output] : a Vector object with the elements rounded up 
//            to the nearest integer
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Ceil() const {
    vector<double> result(m_uiDim);
    // round all the elements of the vector up
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = ceil(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Floor
// [function] : returns a new Vector object with each element floored
// [input] : none
// [output] : a new Vector object with floored elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Floor() const {
    vector<double> result(m_uiDim);
    // floor all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = floor(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Clamp
// [function] : returns a new Vector object with each element clamped 
//              to a range between min_value and max_value
// [input] : min_value, max_value
// [output] : a new Vector object with clamped elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Clamp(double min_value, double max_value) const {
    vector<double> result(m_uiDim);
    // clamp all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = max(min_value, min(max_value, data[i]));
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Reflection
// [function] : returns the reflection of the Vector object off a 
//              given surface normal to another Vector object
// [input] : a Vector object representing the normal
// [output] : a new Vector object representing the reflection
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Reflection(const Vector& normal) const {
    // compute the reflection of the vector off the surface normal
    return (*this - normal * 2 * Dot(normal)).Normalize();
}

// -----------------------------------------------------------
// [name] : Refraction
// [function] : returns the refraction of the Vector 
//              object through a surface with given indices of refraction
// [input] : a Vector object representing the normal, n1, n2 
//           (indices of refraction)
// [output] : a new Vector object representing the refraction
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Refraction(const Vector& normal, double n1, double n2) const {
    // compute the refraction of the vector through the surface 
    // with the given indices of refraction
    double cosi = Dot(normal);
    double etai = n1 / n2;
    double eta = etai;
    double k = 1 - etai * etai * (1 - cosi * cosi);
    // check if the refraction is total internal reflection
    if (k < 0) {
        return Vector::Zeros(m_uiDim);
    }
    // compute the refraction vector
    Vector result = (*this * eta + normal * (eta * cosi - sqrt(k))).Normalize();
    return result;
}

// -----------------------------------------------------------
// [name] : Max
// [function] : returns the maximum element of the Vector object
// [input] : none
// [output] : a double representing the maximum element
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Max() const {
    double result = data[0];
    // find the maximum element of the vector
    for (unsigned int i = 1; i < m_uiDim; i++) {
        result = max(result, data[i]);
    }
    return result;
}

// -----------------------------------------------------------
// [name] : Min
// [function] : returns the minimum element of the Vector object
// [input] : none
// [output] : a double representing the minimum element
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Min() const {
    double result = data[0];
    // find the minimum element of the vector
    for (unsigned int i = 1; i < m_uiDim; i++) {
        result = min(result, data[i]);
    }
    return result;
}

// -----------------------------------------------------------
// [name] : Sum
// [function] : returns the sum of all elements of the Vector object
// [input] : none
// [output] : a double representing the sum of elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Sum() const {
    double result = 0;
    // compute the sum of all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result += data[i];
    }
    return result;
}

// -----------------------------------------------------------
// [name] : Product
// [function] : returns the product of corresponding elements 
//              of two Vector objects
// [input] : a Vector object
// [output] : a double representing the product of elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Product(const Vector& vec) const {
    double result = 1;
    // compute the product of corresponding elements of the two vectors
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result *= data[i] * vec.data[i];
    }
    return result;
}

// -----------------------------------------------------------
// [name] : Mean
// [function] : returns the mean of all elements of the Vector object
// [input] : none
// [output] : a double representing the mean of elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Mean() const {
    return Sum() / m_uiDim;
}

// -----------------------------------------------------------
// [name] : Variance
// [function] : returns the variance of all elements of the Vector object
// [input] : none
// [output] : a double representing the variance of elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Variance() const {
    double mean = Mean();
    double result = 0;
    // compute the variance of all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result += pow(data[i] - mean, 2);
    }
    return result / m_uiDim;
}

// -----------------------------------------------------------
// [name] : StandardDeviation
// [function] : returns the standard deviation of all elements 
//              of the Vector object
// [input] : none
// [output] : a double representing the standard deviation of elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::StandardDeviation() const {
    return sqrt(Variance());
}

// -----------------------------------------------------------
// [name] : Median
// [function] : returns the median of all elements of the Vector object
// [input] : none
// [output] : a double representing the median of elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Median() const {
    vector<double> sorted = data;
    sort(sorted.begin(), sorted.end());
    // compute the median of all the elements of the vector
    // if the number of elements is even, 
    // take the average of the middle two elements
    // otherwise, take the middle element as the median
    if (m_uiDim % 2 == 0) {
        return (sorted[m_uiDim / 2 - 1] + sorted[m_uiDim / 2]) / 2;
    } else {
        return sorted[m_uiDim / 2];
    }
}

// -----------------------------------------------------------
// [name] : Mode
// [function] : returns the mode of all elements of the Vector object
// [input] : none
// [output] : a double representing the mode of elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Mode() const {
    // compute the mode of all the elements of the vector
    // by counting the frequency of each element
    // and returning the element with the highest frequency
    // if there is no mode, return 0
    if (m_uiDim == 0) {
        return 0;
    }
    vector<double> sorted = data;
    // sort the elements of the vector
    sort(sorted.begin(), sorted.end());
    unsigned int count = 1;
    double mode = sorted[0];
    // find the element with the highest frequency
    // by iterating through the sorted elements and counting the frequency
    for (unsigned int i = 1; i < m_uiDim; i++) {
        if (sorted[i] == sorted[i - 1]) {
            count++;
        } else {
            if (count > m_uiDim / 2) {
                return mode;
            }
            mode = sorted[i - 1];
            count = 1;
        }
    }
    // if count is greater than half the number of elements, return the mode
    if (count > m_uiDim / 2) {
        return mode;
    }
    return 0;
}

// -----------------------------------------------------------
// [name] : Inversion
// [function] : returns a new Vector object with each element inverted
// [input] : none
// [output] : a new Vector object with inverted elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Inversion() const {
    vector<double> result(m_uiDim);
    // invert all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        // check if the element is zero
        if (fabs(data[i]) < 1e-6) {
            throw invalid_argument("Division by zero");
        }
        result[i] = 1 / data[i];
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Log
// [function] : returns a new Vector object with each element logged
// [input] : none
// [output] : a new Vector object with logged elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Log() const {
    vector<double> result(m_uiDim);
    // log all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        // check if the element is non-positive
        if (data[i] <= 0) {
            throw invalid_argument("Logarithm of non-positive number");
        }
        result[i] = log(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Exp
// [function] : returns a new Vector object with each element exponentiated
// [input] : none
// [output] : a new Vector object with exponentiated elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Exp() const {
    vector<double> result(m_uiDim);
    // exponentiate all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = exp(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Pow
// [function] : returns a new Vector object with each 
//              element raised to the power of p
// [input] : a double p
// [output] : a new Vector object with elements raised to the power of p
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Pow(double p) const {
    vector<double> result(m_uiDim);
    // raise all the elements of the vector to the power of p
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = pow(data[i], p);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Sqrt
// [function] : returns a new Vector object with each element square rooted
// [input] : none
// [output] : a new Vector object with square rooted elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Sqrt() const {
    vector<double> result(m_uiDim);
    // square root all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        // check if the element is negative
        // square root of a negative number is not defined
        if (data[i] < 0) {
            throw invalid_argument("Square root of negative number");
        }
        result[i] = sqrt(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Cbrt
// [function] : returns a new Vector object with each element cube rooted
// [input] : none
// [output] : a new Vector object with cube rooted elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Cbrt() const {
    vector<double> result(m_uiDim);
    // cube root all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = cbrt(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Sin
// [function] : returns a new Vector object with each element sine
// [input] : none
// [output] : a new Vector object with sine elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Sin() const {
    vector<double> result(m_uiDim);
    // compute the sine of all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = sin(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Cos
// [function] : returns a new Vector object with each element cosine
// [input] : none
// [output] : a new Vector object with cosine elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Cos() const {
    vector<double> result(m_uiDim);
    // compute the cosine of all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = cos(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Tan
// [function] : returns a new Vector object with each element tangent
// [input] : none
// [output] : a new Vector object with tangent elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Tan() const {
    vector<double> result(m_uiDim);
    // compute the tangent of all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = tan(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Asin
// [function] : returns a new Vector object with each element arc sine
// [input] : none
// [output] : a new Vector object with arc sine elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Asin() const {
    vector<double> result(m_uiDim);
    // compute the arc sine of all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        // check if the element is outside of [-1, 1]
        if (data[i] < -1 || data[i] > 1) {
            throw invalid_argument("Arc sine of number outside of [-1, 1]");
        }
        result[i] = asin(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Acos
// [function] : returns a new Vector object with each element arc cosine
// [input] : none
// [output] : a new Vector object with arc cosine elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Acos() const {
    vector<double> result(m_uiDim);
    // compute the arc cosine of all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        // check if the element is outside of [-1, 1]
        if (data[i] < -1 || data[i] > 1) {
            throw invalid_argument("Arc cosine of number outside of [-1, 1]");
        }
        result[i] = acos(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Atan
// [function] : returns a new Vector object with each element arc tangent
// [input] : none
// [output] : a new Vector object with arc tangent elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Atan() const {
    vector<double> result(m_uiDim);
    // compute the arc tangent of all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = atan(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Sinh
// [function] : returns a new Vector object with each element hyperbolic sine
// [input] : none
// [output] : a new Vector object with hyperbolic sine elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Sinh() const {
    vector<double> result(m_uiDim);
    // compute the hyperbolic sine of all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = sinh(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Cosh
// [function] : computes the hyperbolic cosine of each element in the vector
// [input] : none
// [output] : a new Vector object with hyperbolic cosine values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Cosh() const {
    vector<double> result(m_uiDim);
    // compute the hyperbolic cosine of all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = cosh(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Asinh
// [function] : computes the inverse hyperbolic 
//              sine of each element in the vector
// [input] : none
// [output] : a new Vector object with inverse hyperbolic sine values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Asinh() const {
    vector<double> result(m_uiDim);
    // compute the inverse hyperbolic sine of all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = asinh(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Acosh
// [function] : computes the inverse hyperbolic cosine 
//              of each element in the vector
// [input] : none
// [output] : a new Vector object with inverse hyperbolic cosine values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Acosh() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (data[i] < 1) {
            throw invalid_argument(
                "Arc hyperbolic cosine of number less than 1");
        }
        result[i] = acosh(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Atanh
// [function] : computes the inverse hyperbolic tangent of each element 
//              in the vector
// [input] : none
// [output] : a new Vector object with inverse hyperbolic tangent values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Atanh() const {
    vector<double> result(m_uiDim);
    // compute the inverse hyperbolic tangent of all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        // check if the element is outside of (-1, 1)
        // inverse hyperbolic tangent is not defined outside of (-1, 1)
        if (data[i] <= -1 || data[i] >= 1) {
            throw invalid_argument(
                "Arc hyperbolic tangent of number outside of (-1, 1)");
        }
        result[i] = atanh(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : DegreeToRadian
// [function] : converts each element from degrees to radians
// [input] : none
// [output] : a new Vector object with radian values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::DegreeToRadian() const {
    return *this * PI / 180;
}

// -----------------------------------------------------------
// [name] : RadianToDegree
// [function] : converts each element from radians to degrees
// [input] : none
// [output] : a new Vector object with degree values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::RadianToDegree() const {
    return *this * 180 / PI;
}

// -----------------------------------------------------------
// [name] : Map
// [function] : applies a given function to each element in the vector
// [input] : a function pointer
// [output] : a new Vector object with the mapped values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Map(double (*func)(double)) const {
    vector<double> result(m_uiDim);
    // apply the function to all the elements of the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = func(data[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Count
// [function] : counts the occurrences of a specific value in the vector
// [input] : a double value
// [output] : an unsigned int representing the count
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
unsigned int Vector::Count(double value) const {
    unsigned int result = 0;
    // count the occurrences of the value in the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (data[i] == value) {
            result++;
        }
    }
    return result;
}

// -----------------------------------------------------------
// [name] : Sort
// [function] : sorts the elements of the vector in ascending order
// [input] : none
// [output] : a new Vector object with sorted values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Sort() const {
    vector<double> result = data;
    // sort the elements of the vector in ascending order
    sort(result.begin(), result.end());
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Unique
// [function] : removes duplicate elements from the vector
// [input] : none
// [output] : a new Vector object with unique values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Unique() const {
    vector<double> result;
    // remove duplicate elements from the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (find(result.begin(), result.end(), data[i]) == result.end()) {
            result.push_back(data[i]);
        }
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Filter
// [function] : filters the vector based on a given function
// [input] : a function pointer
// [output] : a new Vector object with filtered values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Filter(double (*func)(double)) const {
    vector<double> result;
    // filter the elements of the vector based on the function
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (func(data[i])) {
            result.push_back(data[i]);
        }
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Replace
// [function] : replaces all occurrences of a value with another value
// [input] : two double values (old and new)
// [output] : a new Vector object with replaced values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Replace(double oldValue, double newValue) const {
    vector<double> result = data;
    // replace all occurrences of the old value with the new value
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (fabs(result[i] - oldValue) < 1e-6) {
            result[i] = newValue;
        }
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Round
// [function] : rounds each element to the nearest multiple of a given step
// [input] : a double step value
// [output] : a new Vector object with rounded values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Round(double step) const {
    vector<double> result(m_uiDim);
    // round all the elements of the vector to the nearest multiple of the step
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = round(data[i] / step) * step;
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Ceil
// [function] : rounds each element up to the nearest multiple of a given step
// [input] : a double step value
// [output] : a new Vector object with ceiled values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Ceil(double step) const {
    vector<double> result(m_uiDim);
    // round all the elements of the vector up to the nearest multiple
    // of the step
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = ceil(data[i] / step) * step;
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Floor
// [function] : rounds each element down to the nearest multiple of a given step
// [input] : a double step value
// [output] : a new Vector object with floored values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Floor(double step) const {
    vector<double> result(m_uiDim);
    // floor all the elements of the vector to the nearest multiple of the step
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = floor(data[i] / step) * step;
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Clamp
// [function] : clamps each element between a min and max value, rounded 
//              up to a given step
// [input] : two double values (min and max) and a double step value
// [output] : a new Vector object with clamped values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Clamp(double min_value, double max_value, double step) const {
    vector<double> result(m_uiDim);
    // clamp all the elements of the vector between the min and max values
    // rounded up to the nearest multiple of the step
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = max(min_value, min(max_value, 
                round(data[i] / step) * step));
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : ArgMax
// [function] : finds the index of the maximum element in the vector
// [input] : none
// [output] : an unsigned int representing the index of the maximum element
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
unsigned int Vector::ArgMax() const {
    unsigned int result = 0;
    // find the index of the maximum element of the vector
    for (unsigned int i = 1; i < m_uiDim; i++) {
        if (data[i] > data[result]) {
            result = i;
        }
    }
    return result;
}

// -----------------------------------------------------------
// [name] : ArgMin
// [function] : finds the index of the minimum element in the vector
// [input] : none
// [output] : an unsigned int representing the index of the minimum element
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
unsigned int Vector::ArgMin() const {
    unsigned int result = 0;
    // find the index of the minimum element of the vector
    for (unsigned int i = 1; i < m_uiDim; i++) {
        if (data[i] < data[result]) {
            result = i;
        }
    }
    return result;
}

// -----------------------------------------------------------
// [name] : Concatenate
// [function] : concatenates another Vector object to the current vector
// [input] : a Vector object
// [output] : a new Vector object with concatenated values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Concatenate(const Vector& vec) const {
    vector<double> result(m_uiDim + vec.m_uiDim);
    // concatenate the two vectors
    // by copying the elements of the current vector and the other vector
    // to the new vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = data[i];
    }
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[m_uiDim + i] = vec.data[i];
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Repeat
// [function] : repeats the vector a specified number of times
// [input] : an unsigned int representing the number of repetitions
// [output] : a new Vector object with repeated values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Repeat(unsigned int n) const {
    vector<double> result(m_uiDim * n);
    // repeat the vector n times
    // by copying the elements of the vector to the new vector
    // n times
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < m_uiDim; j++) {
            result[i * m_uiDim + j] = data[j];
        }
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Zeros
// [function] : creates a new vector with all elements set to zero
// [input] : an unsigned int representing the dimension of the vector
// [output] : a new Vector object with zero values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Zeros(unsigned int dim) {
    return Vector(vector<double>(dim, 0));
}

// -----------------------------------------------------------
// [name] : Ones
// [function] : creates a new vector with all elements set to one
// [input] : an unsigned int representing the dimension of the vector
// [output] : a new Vector object with one values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Ones(unsigned int dim) {
    return Vector(vector<double>(dim, 1));
}

// -----------------------------------------------------------
// [name] : Find
// [function] : finds the index of the first occurrence of a value in the vector
// [input] : a double value
// [output] : an unsigned int representing the index of the value
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
unsigned int Vector::Find(double value) const {
    // find the index of the value in the vector
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (data[i] == value) {
            return i;
        }
    }
    return m_uiDim;
}

// -----------------------------------------------------------
// [name] : ToString
// [function] : converts the vector to a string representation
// [input] : none
// [output] : a string representing the vector
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
string Vector::ToString() const {
    // convert the vector to a string
    // by concatenating the elements with commas
    // and enclosing them in parentheses
    string result = "(";
    for (unsigned int i = 0; i < m_uiDim - 1; i++) {
        result += to_string(data[i]) + ", ";
    }
    result += to_string(data[m_uiDim - 1]) + ")";
    return result;
}

// static methods

// -----------------------------------------------------------
// [name] : Norm
// [function] : computes the p-norm of a given vector
// [input] : a Vector object and an unsigned int representing the p-value
// [output] : a double representing the norm
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Norm(const Vector& vec, unsigned int p) {
    return vec.Norm(p);
}

// -----------------------------------------------------------
// [name] : Dot
// [function] : computes the dot product of two vectors
// [input] : two Vector objects
// [output] : a double representing the dot product
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Dot(const Vector& vec1, const Vector& vec2) {
    return vec1.Dot(vec2);
}

// -----------------------------------------------------------
// [name] : Angle
// [function] : computes the angle between two vectors
// [input] : two Vector objects
// [output] : a double representing the angle in radians
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Angle(const Vector& vec1, const Vector& vec2) {
    return vec1.AngleFrom(vec2);
}

// -----------------------------------------------------------
// [name] : Normalize
// [function] : normalizes a Vector object to a specified precision
// [input] : a Vector object, an unsigned integer representing precision
// [output] : a normalized Vector object
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Normalize(const Vector& vec, unsigned int p) {
    return vec.Normalize(p);
}

// -----------------------------------------------------------
// [name] : Cross
// [function] : computes the cross product of two Vector objects
// [input] : two Vector objects
// [output] : a Vector object representing the cross product
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Cross(const Vector& vec1, const Vector& vec2) {
    return vec1.Cross(vec2);
}

// -----------------------------------------------------------
// [name] : Lerp
// [function] : performs linear interpolation between two Vector objects
// [input] : two Vector objects, a double representing the interpolation factor
// [output] : a Vector object representing the result of the interpolation
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Lerp(const Vector& vec1, const Vector& vec2, double t) {
    return vec1.Lerp(vec2, t);
}

// -----------------------------------------------------------
// [name] : Random
// [function] : generates a random Vector object within a specified range
// [input] : an unsigned integer representing dimension, two doubles 
//           representing the range
// [output] : a Vector object with random values within the specified range
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Random(unsigned int dim, double min, double max) {
    vector<double> result(dim);
    // generate random values within the specified range
    // by generating random numbers between 0 and 1 and scaling them
    // to the specified range
    for (unsigned int i = 0; i < dim; i++) {
        result[i] = min + (max - min) * rand() / RAND_MAX;
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : RandomUnit
// [function] : generates a random unit Vector object
// [input] : an unsigned integer representing dimension
// [output] : a unit Vector object with random values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::RandomUnit(unsigned int dim) {
    vector<double> result(dim);
    double length = 0;
    // generate random values between 0 and 1 and normalize them
    // to a unit vector
    for (unsigned int i = 0; i < dim; i++) {
        result[i] = rand() / RAND_MAX;
        length += result[i] * result[i];
    }
    // normalize the vector to a unit vector
    length = sqrt(length);
    for (unsigned int i = 0; i < dim; i++) {
        result[i] /= length;
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Project
// [function] : projects one Vector object onto another
// [input] : two Vector objects
// [output] : a Vector object representing the projection
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Project(const Vector& vec1, const Vector& vec2) {
    return vec1.ProjectTo(vec2);
}

// -----------------------------------------------------------
// [name] : Reflection
// [function] : computes the reflection of a Vector object off a surface
//              with a given normal
// [input] : a Vector object, a Vector object representing the normal
// [output] : a Vector object representing the reflection
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Reflection(const Vector& vec, const Vector& normal) {
    return vec.Reflection(normal);
}

// -----------------------------------------------------------
// [name] : Refraction
// [function] : computes the refraction of a Vector object through a 
//              given surface with given indices of refraction
// [input] : a Vector object, a Vector object representing the normal, 
//           two doubles representing the indices of refraction
// [output] : a Vector object representing the refraction
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Refraction(const Vector& vec, const Vector& normal, 
                    double n1, double n2) {
    return vec.Refraction(normal, n1, n2);
}

// -----------------------------------------------------------
// [name] : Inversion
// [function] : inverts a Vector object
// [input] : a Vector object
// [output] : a Vector object representing the inversion
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Inversion(const Vector& vec) {
    return vec.Inversion();
}

// -----------------------------------------------------------
// [name] : Log
// [function] : computes the natural logarithm of a Vector object
// [input] : a Vector object
// [output] : a Vector object representing the logarithm
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Log(const Vector& vec) {
    return vec.Log();
}

// -----------------------------------------------------------
// [name] : Exp
// [function] : computes the exponential of a Vector object
// [input] : a Vector object
// [output] : a Vector object representing the exponential
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Exp(const Vector& vec) {
    return vec.Exp();
}

// -----------------------------------------------------------
// [name] : Pow
// [function] : raises a Vector object to a given power
// [input] : a Vector object, a double representing the power
// [output] : a Vector object representing the result of the power operation
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Pow(const Vector& vec, double power) {
    return vec.Pow(power);
}

// -----------------------------------------------------------
// [name] : Sqrt
// [function] : computes the square root of a Vector object
// [input] : a Vector object
// [output] : a Vector object representing the square root
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Sqrt(const Vector& vec) {
    return vec.Sqrt();
}

// -----------------------------------------------------------
// [name] : Cbrt
// [function] : computes the cube root of a Vector object
// [input] : a Vector object
// [output] : a Vector object representing the cube root
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Cbrt(const Vector& vec) {
    return vec.Cbrt();
}

// -----------------------------------------------------------
// [name] : Sin
// [function] : computes the sine of a Vector object
// [input] : a Vector object
// [output] : a Vector object representing the sine
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Sin(const Vector& vec) {
    return vec.Sin();
}

// -----------------------------------------------------------
// [name] : Cos
// [function] : computes the cosine of a Vector object
// [input] : a Vector object
// [output] : a Vector object representing the cosine
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Cos(const Vector& vec) {
    return vec.Cos();
}

// -----------------------------------------------------------
// [name] : Tan
// [function] : computes the tangent of a Vector object
// [input] : a Vector object
// [output] : a Vector object representing the tangent
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Tan(const Vector& vec) {
    return vec.Tan();
}

// -----------------------------------------------------------
// [name] : Asin
// [function] : computes the arcsine of a Vector object
// [input] : a Vector object
// [output] : a Vector object representing the arcsine
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Asin(const Vector& vec) {
    return vec.Asin();
}

// -----------------------------------------------------------
// [name] : Acos
// [function] : computes the arccosine of a Vector object
// [input] : a Vector object
// [output] : a Vector object representing the arccosine
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Acos(const Vector& vec) {
    return vec.Acos();
}

// -----------------------------------------------------------
// [name] : Atan
// [function] : computes the arctangent of a Vector object
// [input] : a Vector object
// [output] : a Vector object representing the arctangent
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Atan(const Vector& vec) {
    return vec.Atan();
}

// -----------------------------------------------------------
// [name] : Sinh
// [function] : computes the hyperbolic sine of a Vector object
// [input] : a Vector object
// [output] : a Vector object representing the hyperbolic sine
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Sinh(const Vector& vec) {
    return vec.Sinh();
}

// -----------------------------------------------------------
// [name] : Cosh
// [function] : computes the hyperbolic cosine of a Vector object
// [input] : a Vector object
// [output] : a Vector object representing the hyperbolic cosine
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Cosh(const Vector& vec) {
    return vec.Cosh();
}

// -----------------------------------------------------------
// [name] : Asinh
// [function] : computes the inverse hyperbolic sine of a Vector object
// [input] : a Vector object
// [output] : a Vector object representing the inverse hyperbolic sine
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Asinh(const Vector& vec) {
    return vec.Asinh();
}

// -----------------------------------------------------------
// [name] : Acosh
// [function] : computes the inverse hyperbolic cosine of a Vector object
// [input] : a Vector object
// [output] : a Vector object representing the inverse hyperbolic cosine
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Acosh(const Vector& vec) {
    return vec.Acosh();
}

// -----------------------------------------------------------
// [name] : Atanh
// [function] : computes the inverse hyperbolic tangent of a Vector object
// [input] : a Vector object
// [output] : a Vector object representing the inverse hyperbolic tangent
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Atanh(const Vector& vec) {
    return vec.Atanh();
}

// -----------------------------------------------------------
// [name] : DegreeToRadian
// [function] : converts a Vector object from degrees to radians
// [input] : a Vector object
// [output] : a Vector object in radians
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::DegreeToRadian(const Vector& vec) {
    return vec.DegreeToRadian();
}

// -----------------------------------------------------------
// [name] : RadianToDegree
// [function] : converts a Vector object from radians to degrees
// [input] : a Vector object
// [output] : a Vector object in degrees
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::RadianToDegree(const Vector& vec) {
    return vec.RadianToDegree();
}

// -----------------------------------------------------------
// [name] : Distance
// [function] : computes the distance between two Vector objects
// [input] : two Vector objects
// [output] : a double representing the distance
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Distance(const Vector& vec1, const Vector& vec2) {
    return vec1.Distance(vec2);
}

// -----------------------------------------------------------
// [name] : RandomNormal
// [function] : generates a vector with random normal distributed values
// [input] : dimension of the vector, mean of the distribution, standard 
//           deviation of the distribution
// [output] : a Vector object with random normal distributed values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::RandomNormal(unsigned int dim, double mean, double std) {
    vector<double> result(dim);
    // generate random normal distributed values
    // by generating random numbers from a normal distribution
    // and scaling them to the specified mean and standard deviation
    for (unsigned int i = 0; i < dim; i++) {
        result[i] = mean + std * rand() / RAND_MAX;
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Constant
// [function] : generates a vector with all elements set to a constant value
// [input] : dimension of the vector, constant value
// [output] : a Vector object with all elements set to the constant value
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Constant(unsigned int dim, double value) {
    return Vector(vector<double>(dim, value));
}

// -----------------------------------------------------------
// [name] : Range
// [function] : generates a vector with elements in a specified range
// [input] : dimension of the vector, start value, end value, step value
// [output] : a Vector object with elements in the specified range
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Range(unsigned int dim, double start, double end, double step) {
    // check if the range is valid
    if (start > end) {
        throw invalid_argument("Invalid range");
    }
    vector<double> result;
    // generate the vector with elements in the specified range
    // by adding elements from the start value to the end value
    // with the specified step value
    for (double i = start; i < end; i += step) {
        result.push_back(i);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Linspace
// [function] : generates a vector with evenly spaced values over a 
//             specified interval
// [input] : dimension of the vector, start value, end value, number of points
// [output] : a Vector object with evenly spaced values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Linspace(
        unsigned int dim, double start, double end, unsigned int num) {
    // check if the number of points is valid
    if (num == 0) {
        throw invalid_argument("Number of points must be positive");
    }
    vector<double> result(num);
    // generate the vector with evenly spaced values
    for (unsigned int i = 0; i < num; i++) {
        result[i] = start + (end - start) * i / (num - 1);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Concatenate
// [function] : concatenates multiple vectors into a single vector
// [input] : a vector of Vector objects
// [output] : a Vector object containing all elements of the input vectors
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Concatenate(const vector<Vector>& vecs) {
    vector<double> result;
    // concatenate the vectors by copying the elements of each vector
    // into a single vector
    for (unsigned int i = 0; i < vecs.size(); i++) {
        for (unsigned int j = 0; j < vecs[i].m_uiDim; j++) {
            result.push_back(vecs[i][j]);
        }
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Repeat
// [function] : repeats a vector a specified number of times
// [input] : a Vector object, number of repetitions
// [output] : a Vector object with the input vector repeated
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Repeat(const Vector& vec, unsigned int n) {
    vector<double> result(vec.m_uiDim * n);
    // repeat the vector n times by copying the elements of the vector
    // into the result vector n times
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < vec.m_uiDim; j++) {
            result[i * vec.m_uiDim + j] = vec[j];
        }
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Filter
// [function] : filters elements of a vector based on a given function
// [input] : a Vector object, a function pointer
// [output] : a Vector object with elements filtered by the function
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Filter(const Vector& vec, double (*func)(double)) {
    vector<double> result;
    // filter the elements of the vector based on the function
    // by applying the function to each element and adding the element
    // to the result vector if the function returns true
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        if (func(vec[i])) {
            result.push_back(vec[i]);
        }
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Replace
// [function] : replaces all occurrences of a value in a vector with a new value
// [input] : a Vector object, old value, new value
// [output] : a Vector object with old values replaced by new values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Replace(const Vector& vec, double oldValue, double newValue) {
    vector<double> result = vec.data;
    // replace all occurrences of the old value with the new value
    // by iterating over the elements of the vector and replacing the old value
    // with the new value if it is found
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        if (fabs(result[i] - oldValue) < 1e-6) {
            result[i] = newValue;
        }
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Round
// [function] : rounds elements of a vector to the nearest multiple of 
//             a specified step
// [input] : a Vector object, step value
// [output] : a Vector object with rounded elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Round(const Vector& vec, double step) {
    vector<double> result(vec.m_uiDim);
    // round all the elements of the vector to the nearest multiple of the step
    // by iterating over the elements of the vector and rounding 
    // them to the nearest multiple of the step
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = round(vec[i] / step) * step;
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Ceil
// [function] : rounds elements of a vector up to the nearest multiple 
//             of a specified step
// [input] : a Vector object, step value
// [output] : a Vector object with elements rounded up
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Ceil(const Vector& vec, double step) {
    vector<double> result(vec.m_uiDim);
    // ceil all the elements of the vector to the nearest multiple of the step
    // by iterating over the elements of the vector and rounding 
    // them up to the nearest multiple of the step
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = ceil(vec[i] / step) * step;
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Floor
// [function] : rounds elements of a vector down to the nearest 
//             multiple of a specified step
// [input] : a Vector object, step value
// [output] : a Vector object with elements rounded down
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Floor(const Vector& vec, double step) {
    vector<double> result(vec.m_uiDim);
    // floor all the elements of the vector to the nearest multiple of the step
    // by iterating over the elements of the vector and rounding 
    // them down to the nearest multiple of the step
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = floor(vec[i] / step) * step;
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Clamp
// [function] : clamps each element of a Vector object within a 
//             specified range and step
// [input] : a Vector object, minimum value, maximum value, step value
// [output] : a new Vector object with clamped elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Clamp(
        const Vector& vec, double min_value, double max_value, double step) {
    vector<double> result(vec.m_uiDim);
    // clamp all the elements of the vector within the specified range and step
    // by iterating over the elements of the vector and clamping them
    // to the specified range and step
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = max(min_value, min(max_value, 
                round(vec[i] / step) * step));
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : ArgMax
// [function] : finds the index of the maximum element in a Vector object
// [input] : a Vector object
// [output] : an unsigned integer representing the index of the maximum element
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
unsigned int Vector::ArgMax(const Vector& vec) {
    unsigned int result = 0;
    // find the index of the maximum element of the vector
    // by iterating over the elements of the vector and comparing them
    // to the current maximum element
    for (unsigned int i = 1; i < vec.m_uiDim; i++) {
        if (vec[i] > vec[result]) {
            result = i;
        }
    }
    return result;
}

// -----------------------------------------------------------
// [name] : ArgMin
// [function] : finds the index of the minimum element in a Vector object
// [input] : a Vector object
// [output] : an unsigned integer representing the index of the minimum element
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
unsigned int Vector::ArgMin(const Vector& vec) {
    unsigned int result = 0;
    // find the index of the minimum element of the vector
    // by iterating over the elements of the vector and comparing them
    // to the current minimum element
    for (unsigned int i = 1; i < vec.m_uiDim; i++) {
        if (vec[i] < vec[result]) {
            result = i;
        }
    }
    return result;
}

// -----------------------------------------------------------
// [name] : Sort
// [function] : sorts the elements of a Vector object in ascending order
// [input] : a Vector object
// [output] : a new Vector object with sorted elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Sort(const Vector& vec) {
    vector<double> result = vec.data;
    // sort the elements of the vector in ascending order
    // by using the built-in sort function in the C++ STL
    sort(result.begin(), result.end());
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Unique
// [function] : removes duplicate elements from a Vector object
// [input] : a Vector object
// [output] : a new Vector object with unique elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Unique(const Vector& vec) {
    vector<double> result;
    // remove duplicate elements from the vector
    // by iterating over the elements of the vector and adding the elements
    // to the result vector if they are not already in the result vector
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        if (find(result.begin(), result.end(), vec[i]) == result.end()) {
            result.push_back(vec[i]);
        }
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Count
// [function] : counts the occurrences of a specific value in a Vector object
// [input] : a Vector object, a double value
// [output] : an unsigned integer representing the count of the value
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
unsigned int Vector::Count(const Vector& vec, double value) {
    unsigned int result = 0;
    // count the occurrences of the value in the vector
    // by iterating over the elements of the vector and counting the number of
    // times the value is found
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        if (vec[i] == value) {
            result++;
        }
    }
    return result;
}

// -----------------------------------------------------------
// [name] : Find
// [function] : finds the index of the first occurrence of a specific 
//             value in a Vector object
// [input] : a Vector object, a double value
// [output] : an unsigned integer representing the index of the value, 
//             or the dimension of the vector if not found
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
unsigned int Vector::Find(const Vector& vec, double value) {
    // find the index of the value in the vector
    // by iterating over the elements of the vector and returning the index
    // of the first occurrence of the value, or the dimension of the vector
    // if the value is not found
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        if (vec[i] == value) {
            return i;
        }
    }
    return vec.m_uiDim;
}

// -----------------------------------------------------------
// [name] : Max
// [function] : finds the maximum value in a Vector object
// [input] : a Vector object
// [output] : a double representing the maximum value
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Max(const Vector& vec) {
    double result = vec[0];
    // find the maximum element of the vector
    // by iterating over the elements of the vector and comparing them
    // to the current maximum element
    for (unsigned int i = 1; i < vec.m_uiDim; i++) {
        result = max(result, vec[i]);
    }
    return result;
}

// -----------------------------------------------------------
// [name] : Min
// [function] : finds the minimum value in a Vector object
// [input] : a Vector object
// [output] : a double representing the minimum value
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Min(const Vector& vec) {
    double result = vec[0];
    // find the minimum element of the vector
    // by iterating over the elements of the vector and comparing them
    // to the current minimum element
    for (unsigned int i = 1; i < vec.m_uiDim; i++) {
        result = min(result, vec[i]);
    }
    return result;
}

// -----------------------------------------------------------
// [name] : Sum
// [function] : calculates the sum of all elements in a Vector object
// [input] : a Vector object
// [output] : a double representing the sum of the elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Sum(const Vector& vec) {
    double result = 0;
    // calculate the sum of the elements of the vector
    // by iterating over the elements of the vector and adding them
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result += vec[i];
    }
    return result;
}

// -----------------------------------------------------------
// [name] : Product
// [function] : calculates the element-wise product of two Vector objects
// [input] : two Vector objects
// [output] : a double representing the product of the elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Product(const Vector& vec1, const Vector& vec2) {
    double result = 1;
    // calculate the element-wise product of the two vectors
    // by iterating over the elements of the vectors and multiplying them
    for (unsigned int i = 0; i < vec1.m_uiDim; i++) {
        result *= vec1[i] * vec2[i];
    }
    return result;
}

// -----------------------------------------------------------
// [name] : Mean
// [function] : calculates the mean of all elements in a Vector object
// [input] : a Vector object
// [output] : a double representing the mean of the elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Mean(const Vector& vec) {
    return Sum(vec) / vec.m_uiDim;
}

// -----------------------------------------------------------
// [name] : Variance
// [function] : calculates the variance of all elements in a Vector object
// [input] : a Vector object
// [output] : a double representing the variance of the elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Variance(const Vector& vec) {
    double mean = Mean(vec);
    double result = 0;
    // calculate the variance of the elements of the vector
    // by iterating over the elements of the vector and adding the squared
    // difference from the mean to the result vector
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result += pow(vec[i] - mean, 2);
    }
    return result / vec.m_uiDim;
}

// -----------------------------------------------------------
// [name] : StandardDeviation
// [function] : calculates the standard deviation of all elements in a Vector object
// [input] : a Vector object
// [output] : a double representing the standard deviation of the elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::StandardDeviation(const Vector& vec) {
    return sqrt(Variance(vec));
}

// -----------------------------------------------------------
// [name] : Median
// [function] : calculates the median of all elements in a Vector object
// [input] : a Vector object
// [output] : a double representing the median of the elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Median(const Vector& vec) {
    vector<double> sorted = vec.data;
    sort(sorted.begin(), sorted.end());
    // calculate the median of the elements of the vector
    // by finding the middle element of the sorted vector
    // if the number of elements is odd, the median is the middle element
    // if the number of elements is even, 
    // the median is the average of the two middle elements
    if (vec.m_uiDim % 2 == 0) {
        return (sorted[vec.m_uiDim / 2 - 1] + sorted[vec.m_uiDim / 2]) / 2;
    } else {
        return sorted[vec.m_uiDim / 2];
    }
}

// -----------------------------------------------------------
// [name] : Mode
// [function] : calculates the mode of a Vector object
// [input] : a Vector object
// [output] : a double representing the mode of the vector
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
double Vector::Mode(const Vector& vec) {
    vector<double> sorted = vec.data;
    // calculate the mode of the elements of the vector
    // by sorting the elements and iterating over them to find the mode
    sort(sorted.begin(), sorted.end());
    unsigned int count = 1;
    double mode = sorted[0];
    // find the mode by iterating over the sorted elements of the vector
    // and counting the number of occurrences of each element
    for (unsigned int i = 1; i < vec.m_uiDim; i++) {
        if (sorted[i] == sorted[i - 1]) {
            count++;
        } else {
            if (count > vec.m_uiDim / 2) {
                return mode;
            }
            mode = sorted[i - 1];
            count = 1;
        }
    }
    // if count is greater than half the number of elements, 
    // then return the mode
    if (count > vec.m_uiDim / 2) {
        return mode;
    }
    return 0;
}

// -----------------------------------------------------------
// [name] : Abs
// [function] : calculates the absolute value of a Vector object
// [input] : a Vector object
// [output] : a Vector object with absolute values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Abs(const Vector& vec) {
    vector<double> result(vec.m_uiDim);
    // calculate the absolute values of the elements of the vector
    // by iterating over the elements of the vector and 
    // taking the absolute value
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = fabs(vec[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Round
// [function] : rounds the elements of a Vector object
// [input] : a Vector object
// [output] : a Vector object with rounded elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Round(const Vector& vec) {
    vector<double> result(vec.m_uiDim);
    // round the elements of the vector
    // by iterating over the elements of the vector and rounding them
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = round(vec[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Ceil
// [function] : calculates the ceiling of the elements of a Vector object
// [input] : a Vector object
// [output] : a Vector object with ceiling values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Ceil(const Vector& vec) {
    vector<double> result(vec.m_uiDim);
    // calculate the ceiling of the elements of the vector
    // by iterating over the elements of the vector and taking the ceiling
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = ceil(vec[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Floor
// [function] : calculates the floor of the elements of a Vector object
// [input] : a Vector object
// [output] : a Vector object with floor values
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Floor(const Vector& vec) {
    vector<double> result(vec.m_uiDim);
    // calculate the floor of the elements of the vector
    // by iterating over the elements of the vector and taking the floor
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = floor(vec[i]);
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Clamp
// [function] : clamps the elements of a Vector object between min_value 
//             and max_value
// [input] : a Vector object, a double min_value, a double max_value
// [output] : a Vector object with clamped elements
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Clamp(const Vector& vec, double min_value, double max_value) {
    vector<double> result(vec.m_uiDim);
    // clamp the elements of the vector between the specified range
    // by iterating over the elements of the vector and clamping them
    // to the specified range
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = max(min_value, min(max_value, vec[i]));
    }
    return Vector(result);
}

// -----------------------------------------------------------
// [name] : Map
// [function] : applies a function to each element of a Vector object
// [input] : a Vector object, a function pointer
// [output] : a Vector object with elements transformed by the function
// [author] : Huayu Chen
// [date] : 2024/8/4
// -----------------------------------------------------------
Vector Vector::Map(const Vector& vec, double (*func)(double)) {
    vector<double> result(vec.m_uiDim);
    // apply the function to each element of the vector
    // by iterating over the elements of the vector and applying the function
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = func(vec[i]);
    }
    return Vector(result);
}









