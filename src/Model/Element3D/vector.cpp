// This file contains the implementation of the Vector class.
// This class is used to store a vector of double values.

#include "vector.hpp"

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

