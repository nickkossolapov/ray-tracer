#ifndef VECTOR_H
#define VECTOR_H

class Vector {
public:
    Vector();

    Vector(float x, float y);

    Vector(float x, float y, float z);

    Vector(const Vector &v);

    ~Vector();

    float x, y, z;

    Vector operator+(const Vector &v) const;

    Vector &operator+=(const Vector &v);

    Vector operator-(const Vector &v) const;

    Vector &operator-=(const Vector &v);

    Vector operator*(float s) const;

    Vector &operator*=(float s);

    Vector operator/(float s) const;

    Vector &operator/=(float s);

    Vector operator-() const;

    float dot(const Vector &v) const;

    Vector cross(const Vector &v) const;

    float length() const;

    void normalize();

    Vector normalized() const;

    void reverse();

    Vector reversed() const;

private:
    constexpr static float tol = 1e-6f;
};

#endif //VECTOR_H
