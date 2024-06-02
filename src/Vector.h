#pragma once
#include <cmath>
#include <iostream>

namespace EED
{

    template <typename T>
    class Vector3
    {
    public:
        // Constructors
        Vector3() : x(0.0), y(0.0), z(0.0) {}
        Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

        // Copy constructor
        Vector3(const Vector3 &other) : x(other.x), y(other.y), z(other.z) {}

        // Destructor
        ~Vector3() {}

        // Accessors
        T getX() const { return x; }
        T getY() const { return y; }
        T getZ() const { return z; }

        // Vector addition
        Vector3 operator+(const Vector3 &other) const
        {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }

        // Vector subtraction
        Vector3 operator-(const Vector3 &other) const
        {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }

        // Scalar multiplication
        Vector3 operator*(T scalar) const
        {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }

        // Scalar division
        Vector3 operator/(T scalar) const
        {
            return Vector3(x / scalar, y / scalar, z / scalar);
        }

        // Dot product
        T dot(const Vector3 &other) const
        {
            return x * other.x + y * other.y + z * other.z;
        }

        // Cross product
        Vector3 cross(const Vector3 &other) const
        {
            return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
        }

        T lengthSq() const
        {
            return x * x + y * y + z * z;
        }

        // Magnitude
        T length() const
        {
            return sqrt(lengthSq());
        }

        // Normalize
        Vector3 normalize() const
        {
            T mag = length();
            return Vector3(x / mag, y / mag, z / mag);
        }

        friend std::ostream &operator<<(std::ostream &os, const Vector3 &v)
        {
            os.setf(std::ios::scientific);
            os << "(" << v.x << " " << v.y << " " << v.z << ")";
            os.unsetf(std::ios::scientific);
            return os;
        }

        friend std::istream &operator>>(std::istream &is, Vector3 &v)
        {
            is.ignore(1<<10, '(');
            is >> v.x >> v.y >> v.z;
            is.ignore(1<<10, ')');
            return is;
        }

    private:
        T x, y, z;

    };

    // Typedefs
    typedef Vector3<float> Vector3f;
    typedef Vector3<double> Vector3d;

} // namespace EED
