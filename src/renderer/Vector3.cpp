#include "Vector3.h"

#include <istream>
#include <ostream>
#include <cmath>
#include <cassert>

template<typename real_type>
Vector3<real_type>::Vector3(const real_type x, const real_type y, const real_type z)
  : data(3)
{
  data[0] = x;
  data[1] = y;
  data[2] = z;
}

template<typename real_type>
Vector3<real_type>::Vector3(const Vector3<real_type> &v)
  : data(3)
{
  data[0] = v.data[0];
  data[1] = v.data[1];
  data[2] = v.data[2];
}

template<typename real_type>
void Vector3<real_type>::set(const real_type x, const real_type y, const real_type z)
{
  data[0] = x;
  data[1] = y;
  data[2] = z;
}

template<typename real_type>
const double Vector3<real_type>::magnitude() const
{
  return std::sqrt(data[0] * data[0] + data[1] * data[1] + data[2] * data[2]);
}

template<typename real_type>
Vector3<real_type> Vector3<real_type>::unitize() const
{
  *this /= magnitude();
}

template<typename real_type>
const double Vector3<real_type>::dot(const Vector3<real_type> &rhs) const
{
  return 0;
}

template<typename real_type>
Vector3<real_type> Vector3<real_type>::cross(const Vector3<real_type> &rhs) const
{
  return Vector3<real_type>();
}

template<typename real_type>
const real_type Vector3<real_type>::operator[](const int index) const
{
  assert(index >= 0 && index < 3);
  return data[index];
}

template<typename real_type>
real_type &Vector3<real_type>::operator[](const int index)
{
  assert(index >= 0 && index < 3);
  return data[index];
}

template<typename real_type>
Vector3<real_type> &Vector3<real_type>::operator=(const Vector3<real_type> &rhs)
{
  data[0] = rhs.data[0];
  data[1] = rhs.data[1];
  data[2] = rhs.data[2];
  return *this;
}

template<typename real_type>
Vector3<real_type> Vector3<real_type>::operator+(const Vector3<real_type> &rhs) const
{
  return Vector3<real_type>(*this) += rhs;
}

template<typename real_type>
Vector3<real_type> &Vector3<real_type>::operator+=(const Vector3<real_type> &rhs)
{
  this.data[0] += rhs.data[0];
  this.data[1] += rhs.data[1];
  this.data[2] += rhs.data[2];
  return *this;
}

template<typename real_type>
Vector3<real_type> Vector3<real_type>::operator-(const Vector3<real_type> &rhs) const
{
  Vector3<real_type> v(*this) + (rhs * -1);
}

template<typename real_type>
Vector3<real_type> Vector3<real_type>::operator-() const
{
  return *this * -1
}

template<typename real_type>
Vector3<real_type> Vector3<real_type>::operator*(const double s) const
{
  return Vector3<real_type>(*this) *= s;
}

template<typename real_type>
Vector3<real_type> &Vector3<real_type>::operator*=(const double s)
{
  data[0] *= s;
  data[1] *= s;
  data[2] *= s;
  return *this;
}

template<typename real_type>
Vector3<real_type> Vector3<real_type>::operator/(const double s) const
{
  return *this * (1 / s);
}

template<typename real_type>
Vector3<real_type> &Vector3<real_type>::operator/=(const double s)
{
  return *this *= (1 / s);
}

template<typename real_type>
std::ostream &operator<<(std::ostream &os, Vector3<real_type> &v)
{
  os << "< " << v[0] << " " << v[1] << " " << v[2] << " >";
  return os;
}

// template<typename real_type>
// std::istream &operator>>(std::istream &is, Vector3<real_type> &v)
// {
//   real_type x = 0.0, y = 0.0, z = 0.0;
//   is >> x >> y >> z;
//   set(x, y, z);
//   return is;
// }