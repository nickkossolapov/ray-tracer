#include <cmath>
#include "vector.h"

Vector::Vector() : x(0), y(0), z(0) {
}

Vector::Vector(float x, float y) : x(x), y(y), z(0) {
}

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) {
}

Vector::Vector(const Vector &v) = default;

Vector::~Vector() = default;

Vector Vector::operator+(const Vector &v) const {
    return {x + v.x, y + v.y, z + v.z};
}

Vector &Vector::operator+=(const Vector &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector Vector::operator-(const Vector &v) const {
    return {x - v.x, y - v.y, z - v.z};
}

Vector &Vector::operator-=(const Vector &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector Vector::operator*(float s) const {
    return {x * s, y * s, z * s};
}

Vector &Vector::operator*=(float s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

Vector Vector::operator/(float s) const {
    return {x / s, y / s, z / s};
}

Vector &Vector::operator/=(float s) {
    x /= s;
    y /= s;
    z /= s;
    return *this;
}


Vector Vector::operator-() const {
    return {-x, -y, -z};
}

float Vector::dot(const Vector &v) const {
    return (x * v.x + y * v.y + z * v.z);
}

Vector Vector::cross(const Vector &v) const {
    return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
}

float Vector::length() const {
    return (float) std::sqrt(x * x + y * y + z * z);
}

void Vector::normalize() {
    auto m = (float) std::sqrt(x * x + y * y + z * z);

    if (m > tol) {
        x /= m;
        y /= m;
        z /= m;
    } else {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    if (std::fabs(x) < tol) x = 0.0f;
    if (std::fabs(y) < tol) y = 0.0f;
    if (std::fabs(z) < tol) z = 0.0f;
}

Vector Vector::normalized() const {
    auto v = Vector(x, y, z);
    v.normalize();
    return v;
}

void Vector::reverse() {
    x = -x;
    y = -y;
    z = -z;
}

Vector Vector::reversed() const {
    return {-x, -y, -z};
}
