// This file contains the implementation of the Vector class.
// This class is used to store a vector of double values.

#include "vector.hpp"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cmath>


using namespace std;

const double pi = 3.14159265358979323846;



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

double Vector::Norm(unsigned int p) const {
    double result = 0;
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result += pow(fabs(data[i]), p);
    }
    return pow(result, 1.0 / p);
}

bool Vector::IsLinearIndependent(const vector<Vector>& vectors) {
    unsigned int n = vectors.size();
    unsigned int dimension = vectors[0].Dim;
    if (n > dimension) {
        return false;
    }
    vector<vector<double>> matrix(dimension, vector<double>(n));
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            matrix[j][i] = vectors[i][j];
        }
    }
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < i; j++) {
            for (unsigned int k = 0; k < dimension; k++) {
                if (matrix[k][i] == 0) {
                    if (matrix[k][j] != 0) {
                        return true;
                    }
                }
                else if (matrix[k][j] == 0) {
                    if (matrix[k][i] != 0) {
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

void Vector::ModifyData(const vector<double>& coords) {
    if (coords.size() != m_uiDim) {
        throw invalid_argument("New data must have the same dimension");
    }
    data = coords;
}

ostream& operator<<(ostream& os, const Vector& vec) {
    os << "(";
    for (unsigned int i = 0; i < vec.m_uiDim - 1; i++) {
        os << vec.data[i] << ", ";
    }
    os << vec.data[vec.m_uiDim - 1] << ")";
    return os;
}

bool Vector::operator==(const Vector& vec) const {
    if (m_uiDim != vec.m_uiDim) {
        return false;
    }
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (data[i] != vec.data[i]) {
            return false;
        }
    }
    return true;
}

bool Vector::operator!=(const Vector& vec) const {
    return !(*this == vec);
}

Vector Vector::operator/(double scalar) const {
    if (scalar == 0) {
        throw invalid_argument("Division by zero");
    }
    return *this * (1 / scalar);
}

Vector& Vector::operator+=(const Vector& vec) {
    *this = *this + vec;
    return *this;
}

Vector& Vector::operator-=(const Vector& vec) {
    *this = *this - vec;
    return *this;
}

Vector& Vector::operator*=(double scalar) {
    *this = *this * scalar;
    return *this;
}

Vector& Vector::operator/=(double scalar) {
    *this = *this / scalar;
    return *this;
}

Vector Vector::Normalize(unsigned int p) const {
    return *this / Norm(p);
}

double Vector::Distance(const Vector& vec) const {
    return (*this - vec).Length();
}

Vector Vector::ProjectTo(const Vector& vec) const {
    return vec * (Dot(vec) / vec.Dot(vec));
}

bool Vector::IsZero() const {
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (data[i] != 0) {
            return false;
        }
    }
    return true;
}

bool Vector::IsUnit() const {
    return fabs(Length() - 1) < 1e-6;
}

Vector Vector::InsertDimension(unsigned int dim, double value) const {
    if (dim > m_uiDim) {
        throw invalid_argument("Index out of range");
    }
    vector<double> result(m_uiDim + 1);
    for (unsigned int i = 0; i < dim; i++) {
        result[i] = data[i];
    }
    result[dim] = value;
    for (unsigned int i = dim + 1; i < m_uiDim + 1; i++) {
        result[i] = data[i - 1];
    }
    return Vector(result);
}

Vector Vector::RemoveDimension(unsigned int dim) const {
    if (dim >= m_uiDim) {
        throw invalid_argument("Index out of range");
    }
    vector<double> result(m_uiDim - 1);
    for (unsigned int i = 0; i < dim; i++) {
        result[i] = data[i];
    }
    for (unsigned int i = dim + 1; i < m_uiDim; i++) {
        result[i - 1] = data[i];
    }
    return Vector(result);
}

Vector Vector::Lerp(const Vector& vec, double t) const {
    return *this * (1 - t) + vec * t;
}

vector<double>::iterator Vector::begin() {
    return data.begin();
}

vector<double>::iterator Vector::end() {
    return data.end();
}

vector<double>::const_iterator Vector::begin() const {
    return data.begin();
}

vector<double>::const_iterator Vector::end() const {
    return data.end();
}

Vector Vector::Slice(unsigned int start, unsigned int end) const {
    if (start >= end || start >= m_uiDim || end > m_uiDim) {
        throw invalid_argument("Invalid slice range");
    }
    vector<double> result(end - start);
    for (unsigned int i = start; i < end; i++) {
        result[i - start] = data[i];
    }
    return Vector(result);
}

Vector Vector::Slice(unsigned int start) const {
    return Slice(start, m_uiDim);
}

Vector Vector::Reverse() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = data[m_uiDim - 1 - i];
    }
    return Vector(result);
}

Vector Vector::Opposite() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = -data[i];
    }
    return Vector(result);
}

Vector Vector::Abs() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = fabs(data[i]);
    }
    return Vector(result);
}

Vector Vector::Round() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = round(data[i]);
    }
    return Vector(result);
}

Vector Vector::Ceil() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = ceil(data[i]);
    }
    return Vector(result);
}

Vector Vector::Floor() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = floor(data[i]);
    }
    return Vector(result);
}

Vector Vector::Clamp(double min_value, double max_value) const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = max(min_value, min(max_value, data[i]));
    }
    return Vector(result);
}

Vector Vector::Reflection(const Vector& normal) const {
    return (*this - normal * 2 * Dot(normal)).Normalize();
}

Vector Vector::Refraction(const Vector& normal, double n1, double n2) const {
    double cosi = Dot(normal);
    double etai = n1 / n2;
    double eta = etai;
    double k = 1 - etai * etai * (1 - cosi * cosi);
    if (k < 0) {
        return Vector::Zeros(m_uiDim);
    }
    Vector result = (*this * eta + normal * (eta * cosi - sqrt(k))).Normalize();
    return result;
}

double Vector::Max() const {
    double result = data[0];
    for (unsigned int i = 1; i < m_uiDim; i++) {
        result = max(result, data[i]);
    }
    return result;
}

double Vector::Min() const {
    double result = data[0];
    for (unsigned int i = 1; i < m_uiDim; i++) {
        result = min(result, data[i]);
    }
    return result;
}

double Vector::Sum() const {
    double result = 0;
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result += data[i];
    }
    return result;
}

double Vector::Product(const Vector& vec) const {
    double result = 1;
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result *= data[i] * vec.data[i];
    }
    return result;
}

double Vector::Mean() const {
    return Sum() / m_uiDim;
}

double Vector::Variance() const {
    double mean = Mean();
    double result = 0;
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result += pow(data[i] - mean, 2);
    }
    return result / m_uiDim;
}

double Vector::StandardDeviation() const {
    return sqrt(Variance());
}

double Vector::Median() const {
    vector<double> sorted = data;
    sort(sorted.begin(), sorted.end());
    if (m_uiDim % 2 == 0) {
        return (sorted[m_uiDim / 2 - 1] + sorted[m_uiDim / 2]) / 2;
    } else {
        return sorted[m_uiDim / 2];
    }
}

double Vector::Mode() const {
    vector<double> sorted = data;
    sort(sorted.begin(), sorted.end());
    unsigned int count = 1;
    double mode = sorted[0];
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
    if (count > m_uiDim / 2) {
        return mode;
    }
    return 0;
}

Vector Vector::Inversion() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (data[i] == 0) {
            throw invalid_argument("Division by zero");
        }
        result[i] = 1 / data[i];
    }
    return Vector(result);
}

Vector Vector::Log() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (data[i] <= 0) {
            throw invalid_argument("Logarithm of non-positive number");
        }
        result[i] = log(data[i]);
    }
    return Vector(result);
}

Vector Vector::Exp() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = exp(data[i]);
    }
    return Vector(result);
}

Vector Vector::Pow(double p) const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = pow(data[i], p);
    }
    return Vector(result);
}

Vector Vector::Sqrt() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (data[i] < 0) {
            throw invalid_argument("Square root of negative number");
        }
        result[i] = sqrt(data[i]);
    }
    return Vector(result);
}

Vector Vector::Cbrt() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (data[i] < 0) {
            throw invalid_argument("Cube root of negative number");
        }
        result[i] = cbrt(data[i]);
    }
    return Vector(result);
}

Vector Vector::Sin() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = sin(data[i]);
    }
    return Vector(result);
}

Vector Vector::Cos() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = cos(data[i]);
    }
    return Vector(result);
}

Vector Vector::Tan() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = tan(data[i]);
    }
    return Vector(result);
}

Vector Vector::Asin() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (data[i] < -1 || data[i] > 1) {
            throw invalid_argument("Arc sine of number outside of [-1, 1]");
        }
        result[i] = asin(data[i]);
    }
    return Vector(result);
}

Vector Vector::Acos() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (data[i] < -1 || data[i] > 1) {
            throw invalid_argument("Arc cosine of number outside of [-1, 1]");
        }
        result[i] = acos(data[i]);
    }
    return Vector(result);
}

Vector Vector::Atan() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = atan(data[i]);
    }
    return Vector(result);
}

Vector Vector::Sinh() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = sinh(data[i]);
    }
    return Vector(result);
}

Vector Vector::Cosh() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = cosh(data[i]);
    }
    return Vector(result);
}

Vector Vector::Asinh() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = asinh(data[i]);
    }
    return Vector(result);
}

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

Vector Vector::Atanh() const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (data[i] <= -1 || data[i] >= 1) {
            throw invalid_argument(
                "Arc hyperbolic tangent of number outside of (-1, 1)");
        }
        result[i] = atanh(data[i]);
    }
    return Vector(result);
}

Vector Vector::DegreeToRadian() const {
    return *this * pi / 180;
}

Vector Vector::RadianToDegree() const {
    return *this * 180 / pi;
}

Vector Vector::Map(double (*func)(double)) const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = func(data[i]);
    }
    return Vector(result);
}

unsigned int Vector::Count(double value) const {
    unsigned int result = 0;
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (data[i] == value) {
            result++;
        }
    }
    return result;
}

Vector Vector::Sort() const {
    vector<double> result = data;
    sort(result.begin(), result.end());
    return Vector(result);
}

Vector Vector::Unique() const {
    vector<double> result;
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (find(result.begin(), result.end(), data[i]) == result.end()) {
            result.push_back(data[i]);
        }
    }
    return Vector(result);
}

Vector Vector::Filter(double (*func)(double)) const {
    vector<double> result;
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (func(data[i])) {
            result.push_back(data[i]);
        }
    }
    return Vector(result);
}

Vector Vector::Replace(double oldValue, double newValue) const {
    vector<double> result = data;
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (data[i] == oldValue) {
            result[i] = newValue;
        }
    }
    return Vector(result);
}

Vector Vector::Round(double step) const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = round(data[i] / step) * step;
    }
    return Vector(result);
}

Vector Vector::Ceil(double step) const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = ceil(data[i] / step) * step;
    }
    return Vector(result);
}

Vector Vector::Floor(double step) const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = floor(data[i] / step) * step;
    }
    return Vector(result);
}

Vector Vector::Clamp(double min_value, double max_value, double step) const {
    vector<double> result(m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = max(min_value, min(max_value, 
                round(data[i] / step) * step));
    }
    return Vector(result);
}

unsigned int Vector::ArgMax() const {
    unsigned int result = 0;
    for (unsigned int i = 1; i < m_uiDim; i++) {
        if (data[i] > data[result]) {
            result = i;
        }
    }
    return result;
}

unsigned int Vector::ArgMin() const {
    unsigned int result = 0;
    for (unsigned int i = 1; i < m_uiDim; i++) {
        if (data[i] < data[result]) {
            result = i;
        }
    }
    return result;
}

Vector Vector::Concatenate(const Vector& vec) const {
    vector<double> result(m_uiDim + vec.m_uiDim);
    for (unsigned int i = 0; i < m_uiDim; i++) {
        result[i] = data[i];
    }
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[m_uiDim + i] = vec.data[i];
    }
    return Vector(result);
}

Vector Vector::Repeat(unsigned int n) const {
    vector<double> result(m_uiDim * n);
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < m_uiDim; j++) {
            result[i * m_uiDim + j] = data[j];
        }
    }
    return Vector(result);
}

Vector Vector::Zeros(unsigned int dim) {
    return Vector(vector<double>(dim, 0));
}

Vector Vector::Ones(unsigned int dim) {
    return Vector(vector<double>(dim, 1));
}

unsigned int Vector::Find(double value) const {
    for (unsigned int i = 0; i < m_uiDim; i++) {
        if (data[i] == value) {
            return i;
        }
    }
    return m_uiDim;
}

string Vector::ToString() const {
    string result = "(";
    for (unsigned int i = 0; i < m_uiDim - 1; i++) {
        result += to_string(data[i]) + ", ";
    }
    result += to_string(data[m_uiDim - 1]) + ")";
    return result;
}

// static methods

double Vector::Norm(const Vector& vec, unsigned int p) {
    return vec.Norm(p);
}

double Vector::Dot(const Vector& vec1, const Vector& vec2) {
    return vec1.Dot(vec2);
}

double Vector::Angle(const Vector& vec1, const Vector& vec2) {
    return vec1.AngleFrom(vec2);
}

Vector Vector::Normalize(const Vector& vec, unsigned int p) {
    return vec.Normalize(p);
}

Vector Vector::Cross(const Vector& vec1, const Vector& vec2) {
    return vec1.Cross(vec2);
}

Vector Vector::Lerp(const Vector& vec1, const Vector& vec2, double t) {
    return vec1.Lerp(vec2, t);
}

Vector Vector::Random(unsigned int dim, double min, double max) {
    vector<double> result(dim);
    for (unsigned int i = 0; i < dim; i++) {
        result[i] = min + (max - min) * rand() / RAND_MAX;
    }
    return Vector(result);
}

Vector Vector::RandomUnit(unsigned int dim) {
    vector<double> result(dim);
    double length = 0;
    for (unsigned int i = 0; i < dim; i++) {
        result[i] = rand() / RAND_MAX;
        length += result[i] * result[i];
    }
    length = sqrt(length);
    for (unsigned int i = 0; i < dim; i++) {
        result[i] /= length;
    }
    return Vector(result);
}

Vector Vector::Project(const Vector& vec1, const Vector& vec2) {
    return vec1.ProjectTo(vec2);
}

Vector Vector::Reflection(const Vector& vec, const Vector& normal) {
    return vec.Reflection(normal);
}

Vector Vector::Refraction(const Vector& vec, const Vector& normal, 
                    double n1, double n2) {
    return vec.Refraction(normal, n1, n2);
}

Vector Vector::Inversion(const Vector& vec) {
    return vec.Inversion();
}

Vector Vector::Log(const Vector& vec) {
    return vec.Log();
}

Vector Vector::Exp(const Vector& vec) {
    return vec.Exp();
}

Vector Vector::Pow(const Vector& vec, double power) {
    return vec.Pow(power);
}

Vector Vector::Sqrt(const Vector& vec) {
    return vec.Sqrt();
}

Vector Vector::Cbrt(const Vector& vec) {
    return vec.Cbrt();
}

Vector Vector::Sin(const Vector& vec) {
    return vec.Sin();
}

Vector Vector::Cos(const Vector& vec) {
    return vec.Cos();
}

Vector Vector::Tan(const Vector& vec) {
    return vec.Tan();
}

Vector Vector::Asin(const Vector& vec) {
    return vec.Asin();
}

Vector Vector::Acos(const Vector& vec) {
    return vec.Acos();
}

Vector Vector::Atan(const Vector& vec) {
    return vec.Atan();
}

Vector Vector::Sinh(const Vector& vec) {
    return vec.Sinh();
}

Vector Vector::Cosh(const Vector& vec) {
    return vec.Cosh();
}

Vector Vector::Asinh(const Vector& vec) {
    return vec.Asinh();
}

Vector Vector::Acosh(const Vector& vec) {
    return vec.Acosh();
}

Vector Vector::Atanh(const Vector& vec) {
    return vec.Atanh();
}

Vector Vector::DegreeToRadian(const Vector& vec) {
    return vec.DegreeToRadian();
}

Vector Vector::RadianToDegree(const Vector& vec) {
    return vec.RadianToDegree();
}

double Vector::Distance(const Vector& vec1, const Vector& vec2) {
    return vec1.Distance(vec2);
}

Vector Vector::RandomNormal(unsigned int dim, double mean, double std) {
    vector<double> result(dim);
    for (unsigned int i = 0; i < dim; i++) {
        result[i] = mean + std * rand() / RAND_MAX;
    }
    return Vector(result);
}

Vector Vector::Constant(unsigned int dim, double value) {
    return Vector(vector<double>(dim, value));
}

Vector Vector::Range(unsigned int dim, double start, double end, double step) {
    if (start > end) {
        throw invalid_argument("Invalid range");
    }
    vector<double> result;
    for (double i = start; i < end; i += step) {
        result.push_back(i);
    }
    return Vector(result);
}

Vector Vector::Linspace(unsigned int dim, double start, double end, unsigned int num) {
    if (num == 0) {
        throw invalid_argument("Number of points must be positive");
    }
    vector<double> result(num);
    for (unsigned int i = 0; i < num; i++) {
        result[i] = start + (end - start) * i / (num - 1);
    }
    return Vector(result);
}

Vector Vector::Concatenate(const vector<Vector>& vecs) {
    vector<double> result;
    for (unsigned int i = 0; i < vecs.size(); i++) {
        for (unsigned int j = 0; j < vecs[i].m_uiDim; j++) {
            result.push_back(vecs[i][j]);
        }
    }
    return Vector(result);
}

Vector Vector::Repeat(const Vector& vec, unsigned int n) {
    vector<double> result(vec.m_uiDim * n);
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < vec.m_uiDim; j++) {
            result[i * vec.m_uiDim + j] = vec[j];
        }
    }
    return Vector(result);
}

Vector Vector::Filter(const Vector& vec, double (*func)(double)) {
    vector<double> result;
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        if (func(vec[i])) {
            result.push_back(vec[i]);
        }
    }
    return Vector(result);
}

Vector Vector::Replace(const Vector& vec, double oldValue, double newValue) {
    vector<double> result = vec.data;
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        if (vec[i] == oldValue) {
            result[i] = newValue;
        }
    }
    return Vector(result);
}

Vector Vector::Round(const Vector& vec, double step) {
    vector<double> result(vec.m_uiDim);
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = round(vec[i] / step) * step;
    }
    return Vector(result);
}

Vector Vector::Ceil(const Vector& vec, double step) {
    vector<double> result(vec.m_uiDim);
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = ceil(vec[i] / step) * step;
    }
    return Vector(result);
}

Vector Vector::Floor(const Vector& vec, double step) {
    vector<double> result(vec.m_uiDim);
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = floor(vec[i] / step) * step;
    }
    return Vector(result);
}

Vector Vector::Clamp(const Vector& vec, double min_value, double max_value, double step) {
    vector<double> result(vec.m_uiDim);
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = max(min_value, min(max_value, 
                round(vec[i] / step) * step));
    }
    return Vector(result);
}

unsigned int Vector::ArgMax(const Vector& vec) {
    unsigned int result = 0;
    for (unsigned int i = 1; i < vec.m_uiDim; i++) {
        if (vec[i] > vec[result]) {
            result = i;
        }
    }
    return result;
}

unsigned int Vector::ArgMin(const Vector& vec) {
    unsigned int result = 0;
    for (unsigned int i = 1; i < vec.m_uiDim; i++) {
        if (vec[i] < vec[result]) {
            result = i;
        }
    }
    return result;
}

Vector Vector::Sort(const Vector& vec) {
    vector<double> result = vec.data;
    sort(result.begin(), result.end());
    return Vector(result);
}

Vector Vector::Unique(const Vector& vec) {
    vector<double> result;
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        if (find(result.begin(), result.end(), vec[i]) == result.end()) {
            result.push_back(vec[i]);
        }
    }
    return Vector(result);
}

unsigned int Vector::Count(const Vector& vec, double value) {
    unsigned int result = 0;
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        if (vec[i] == value) {
            result++;
        }
    }
    return result;
}

unsigned int Vector::Find(const Vector& vec, double value) {
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        if (vec[i] == value) {
            return i;
        }
    }
    return vec.m_uiDim;
}

double Vector::Max(const Vector& vec) {
    double result = vec[0];
    for (unsigned int i = 1; i < vec.m_uiDim; i++) {
        result = max(result, vec[i]);
    }
    return result;
}

double Vector::Min(const Vector& vec) {
    double result = vec[0];
    for (unsigned int i = 1; i < vec.m_uiDim; i++) {
        result = min(result, vec[i]);
    }
    return result;
}

double Vector::Sum(const Vector& vec) {
    double result = 0;
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result += vec[i];
    }
    return result;
}

double Vector::Product(const Vector& vec1, const Vector& vec2) {
    double result = 1;
    for (unsigned int i = 0; i < vec1.m_uiDim; i++) {
        result *= vec1[i] * vec2[i];
    }
    return result;
}

double Vector::Mean(const Vector& vec) {
    return Sum(vec) / vec.m_uiDim;
}

double Vector::Variance(const Vector& vec) {
    double mean = Mean(vec);
    double result = 0;
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result += pow(vec[i] - mean, 2);
    }
    return result / vec.m_uiDim;
}

double Vector::StandardDeviation(const Vector& vec) {
    return sqrt(Variance(vec));
}

double Vector::Median(const Vector& vec) {
    vector<double> sorted = vec.data;
    sort(sorted.begin(), sorted.end());
    if (vec.m_uiDim % 2 == 0) {
        return (sorted[vec.m_uiDim / 2 - 1] + sorted[vec.m_uiDim / 2]) / 2;
    } else {
        return sorted[vec.m_uiDim / 2];
    }
}

double Vector::Mode(const Vector& vec) {
    vector<double> sorted = vec.data;
    sort(sorted.begin(), sorted.end());
    unsigned int count = 1;
    double mode = sorted[0];
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
    if (count > vec.m_uiDim / 2) {
        return mode;
    }
    return 0;
}

Vector Vector::Abs(const Vector& vec) {
    vector<double> result(vec.m_uiDim);
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = fabs(vec[i]);
    }
    return Vector(result);
}

Vector Vector::Round(const Vector& vec) {
    vector<double> result(vec.m_uiDim);
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = round(vec[i]);
    }
    return Vector(result);
}

Vector Vector::Ceil(const Vector& vec) {
    vector<double> result(vec.m_uiDim);
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = ceil(vec[i]);
    }
    return Vector(result);
}

Vector Vector::Floor(const Vector& vec) {
    vector<double> result(vec.m_uiDim);
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = floor(vec[i]);
    }
    return Vector(result);
}

Vector Vector::Clamp(const Vector& vec, double min_value, double max_value) {
    vector<double> result(vec.m_uiDim);
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = max(min_value, min(max_value, vec[i]));
    }
    return Vector(result);
}

Vector Vector::Map(const Vector& vec, double (*func)(double)) {
    vector<double> result(vec.m_uiDim);
    for (unsigned int i = 0; i < vec.m_uiDim; i++) {
        result[i] = func(vec[i]);
    }
    return Vector(result);
}









