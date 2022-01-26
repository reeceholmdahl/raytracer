#ifndef _VECTOR3_REECE_
#define _VECTOR3_REECE_

#include <vector>
#include <istream>
#include <ostream>

template<typename real_type>
class Vector3
{
public:
  // Constructor with default float values of zero, forces parameter to accept 0.0, implicitly selecting real types
  Vector3(const real_type x = 0.0, const real_type y = 0.0, const real_type z = 0.0);

  // Copy constructor
  Vector3(const Vector3 &v);

  void set(const real_type x, const real_type y, const real_type z);

  const double magnitude() const;

  // Unit vector of same direction
  Vector3<real_type> unitize() const;

  // Dot product with another vector
  const double dot(const Vector3 &rhs) const;

  // Cross product with another vector as the RHS
  Vector3<real_type> cross(const Vector3 &rhs) const;

  // Square braces access operator
  const real_type operator[](const int index) const;

  // Square braces assign operator
  real_type &operator[](const int index);

  // Assignment operator
  Vector3<real_type> &operator=(const Vector3<real_type> &rhs);

  // Add
  Vector3<real_type> operator+(const Vector3<real_type> &rhs) const;

  // Plus equal operator
  Vector3<real_type> &operator+=(const Vector3<real_type> &rhs);

  // Subtract
  Vector3<real_type> operator-(const Vector3<real_type> &rhs) const;

  // Negate
  Vector3<real_type> operator-() const;

  // Multiply by a constant
  Vector3<real_type> operator*(const double s) const;

  // Multiply equal operator
  Vector3<real_type> &operator*=(const double s);

  // Divide by a constant
  Vector3<real_type> operator/(const double s) const;

  // Divide equal operator
  Vector3<real_type> &operator/=(const double s);

private:
  std::vector<real_type> data;
  friend std::ostream &operator<<(std::ostream &os, Vector3<real_type> &v);
  friend std::istream &operator>>(std::istream &is, Vector3<real_type> &v);
};

using Vec3d = Vector3<double>;
using Vec3f = Vector3<float>;

#include "Vector3.cpp"

#endif