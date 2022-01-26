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
  Vector3(real_type x = 0.0, real_type y = 0.0, real_type z = 0.0);

  // Copy constructor
  Vector3(const Vector3<real_type> &v);

  // Unit vector of same direction
  Vector3<real_type> unitize() const;

  // Dot product with another vector
  real_type dot(const Vector3<real_type> &rhs) const;

  // Cross product with another vector as the RHS
  Vector3<real_type> cross(const Vector3<real_type> &rhs) const;

  // Square braces access operator
  const real_type operator[](const int index) const;

  // Square braces assign operator
  real_type &operator[](const int index);

  // Assignment operator
  Vector3<real_type> &operator=(const Vector3<real_type> &rhs);

  // Plus equal operator
  Vector3<real_type> &operator+=(const Vector3<real_type> &rhs);

  // Add
  Vector3<real_type> operator+(const Vector3<real_type> &rhs) const;

  // Subtract
  Vector3<real_type> operator-(const Vector3<real_type> &rhs) const;

  // Negate
  Vector3<real_type> operator-() const;

  // Multiply by a constant
  Vector3<real_type> operator*(const double s) const;

  // Multiply equal operator
  Vector3<real_type> &operator*=(const double s);

  // Multiply by a constant
  Vector3<real_type> operator*(const double s) const;

  // Multiply equal operator
  Vector3<real_type> &operator*=(const double s);

  // Divide by a constant
  Vector3<real_type> operator/(const double s) const;

  // Divide equal operator
  Vector3<real_type> &operator/=(const double s);

private:
  std::vector<real_type> data(3);

  friend std::ostream &operator<<(std::ostream &os, const Vector3<real_type> &v);
  friend std::istream &operator>>(std::istream &is, Vector3<real_type> &v);
};

#include "Vector3.cpp"

#endif