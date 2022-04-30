#ifndef RENDERER_MATH_VECTOR3_H_
#define RENDERER_MATH_VECTOR3_H_

#include <vector>
#include <istream>
#include <ostream>
#include <cassert>

template <typename real_type>
class Vector3
{
public:
  // Constructor with default float values of zero, forces parameter to accept
  // 0.0, implicitly selecting real types
  Vector3(const real_type x = 0.0, const real_type y = 0.0,
          const real_type z = 0.0);

  Vector3(const std::string& str);

  // Copy constructor
  template <typename other>
  Vector3(const Vector3<other>& v)
    : data(3)
  {
    data[0] = v[0];
    data[1] = v[1];
    data[2] = v[2];
  }

  void set(const real_type x, const real_type y, const real_type z);

  const double magnitude() const;

  const double angle(const Vector3& v) const;

  // Unit vector of same direction
  Vector3<real_type> unitize() const;

  // Dot product with another vector
  const double dot(const Vector3& rhs) const
  {
    return data[0] * rhs[0] + data[1] * rhs[1] + data[2] * rhs[2];
  }

  // Cross product with another vector as the RHS
  Vector3<real_type> cross(const Vector3& rhs) const;

  // Square braces access operator
  const real_type operator[](const int index) const
  {
    assert(index >= 0 && index < 3);
    return data[index];
  }

  // Square braces assign operator
  real_type& operator[](const int index)
  {
    assert(index >= 0 && index < 3);
    return data[index];
  }

  // Assignment operator: Vector3
  Vector3<real_type>& operator=(const Vector3& rhs)
  {
    data[0] = rhs[0];
    data[1] = rhs[1];
    data[2] = rhs[2];
    return *this;
  }

  // Assignment operator: String
  Vector3<real_type>& operator=(const std::string& str);

  // Add
  Vector3<real_type> operator+(const Vector3& rhs) const;

  // Plus equal operator
  Vector3<real_type>& operator+=(const Vector3& rhs);

  // Subtract
  Vector3<real_type> operator-(const Vector3& rhs) const;

  // Minus equal operator
  Vector3<real_type>& operator-=(const Vector3& rhs);

  // Negate
  Vector3<real_type> operator-() const;

  // Component-wise multiplication
  Vector3<real_type> operator*(const Vector3& v) const;

  // Multiply by a constant
  Vector3<real_type> operator*(const double s) const;

  // Component-wise multiply equal
  Vector3<real_type>& operator*=(const Vector3& v);

  // Multiply equal operator
  Vector3<real_type>& operator*=(const double s);

  // Divide by a constant
  Vector3<real_type> operator/(const double s) const;

  // Divide equal operator
  Vector3<real_type>& operator/=(const double s);

private:
  std::vector<real_type> data;
};

using Vec3d = Vector3<double>;
using Vec3f = Vector3<float>;

#include "Vector3.cpp"

#endif