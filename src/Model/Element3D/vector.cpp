// This file contains the implementation of the Vector class.
// This class is used to store a vector of double values.

#include "vector.hpp"
#include <vector>
#include <stdexcept>


using namespace std;

Vector::Vector(const vector<double>& coords) {
    m_uiDim = coords.size();
    data = coords;
}

Vector::Vector(const Vector& vec) {
    m_uiDim = vec.m_uiDim;
    data = vec.data;
}

Vector& Vector::operator=(const Vector& vec) {
    m_uiDim = vec.m_uiDim;
    data = vec.data;
    return *this;
}

Vector::~Vector() {}


double& Vector::operator[](unsigned int index) {
    if (index >= m_uiDim) {
        throw invalid_argument("Index out of range");
    }
    return data[index];
}

double Vector::operator[](unsigned int index) const {
    if (index >= m_uiDim) {
        throw invalid_argument("Index out of range");
    }
    return data[index];
}

Vector Vector::operator+(const Vector& vec) const {
    if (m_uiDim != vec.m_uiDim) {
        throw invalid_argument("Vectors must have the same dimension");
    }
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = data[i] + vec.data[i];
    }
    return Vector(result);
}

Vector Vector::operator-(const Vector& vec) const {
    if (m_uiDim != vec.m_uiDim) {
        throw invalid_argument("Vectors must have the same dimension");
    }
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = data[i] - vec.data[i];
    }
    return Vector(result);
}

Vector Vector::operator*(double scalar) const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = data[i] * scalar;
    }
    return Vector(result);
}

double Vector::Dot(const Vector& vec) const {
    if (m_uiDim != vec.m_uiDim) {
        throw invalid_argument("Vectors must have the same dimension");
    }
    double result = 0;
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result += data[i] * vec.data[i];
    }
    return result;
}

Vector Vector::Cross(const Vector& vec) const {
    if (m_uiDim != 3 || vec.m_uiDim != 3) {
        throw invalid_argument("Cross product is defined only for 3D vectors");
    }
    double x = data[1] * vec.data[2] - data[2] * vec.data[1];
    double y = data[2] * vec.data[0] - data[0] * vec.data[2];
    double z = data[0] * vec.data[1] - data[1] * vec.data[0];
    return Vector({x, y, z});
}

double Vector::Length() const {
    double result = 0;
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result += data[i] * data[i];
    }
    return sqrt(result);
}

bool Vector::IsParallel(const Vector& vec) const {
    if (m_uiDim != vec.m_uiDim) {
        throw invalid_argument("Vectors must have the same dimension");
    }
    double scalar = data[0] / vec.data[0];
    for (unsigned int i = 1; i < m_uiDim; i++) {
        if (fabs(data[i] / vec.data[i] - scalar) > 1e-6) {
            return false;
        }
    }
    return true;
}

bool Vector::IsOrthogonal(const Vector& vec) const {
    if (m_uiDim != vec.m_uiDim) {
        throw invalid_argument("Vectors must have the same dimension");
    }
    return Dot(vec) == 0;
}

double Vector::AngleFrom(const Vector& vec) const {
    if (m_uiDim != vec.m_uiDim) {
        throw invalid_argument("Vectors must have the same dimension");
    }
    double cosAngle = Dot(vec) / (Length() * vec.Length());
    return acos(cosAngle);
}

vector<double> Vector::GetData() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = data[i];
    }
    return result;
}


