#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "Vector3.hpp"

template <typename real_type>
Vector3<real_type>::Vector3(const real_type x, const real_type y,
                            const real_type z)
  : data(3)
{
  data[0] = x;
  data[1] = y;
  data[2] = z;
}

template <typename real_type>
Vector3<real_type>::Vector3(const std::string& str)
  : data(3)
{
  // Vector3<real_type> v;
  // v = str;
  *this = str;
}

// template<typename real_type>
// template<typename other>
// Vector3<real_type>::Vector3(const Vector3<other> &v)
//   : data(3)
// {
//   data[0] = v[0];
//   data[1] = v[1];
//   data[2] = v[2];
// }

template <typename real_type>
void
Vector3<real_type>::set(const real_type x, const real_type y, const real_type z)
{
  data[0] = x;
  data[1] = y;
  data[2] = z;
}

template <typename real_type>
const double
Vector3<real_type>::magnitude() const
{
  return std::sqrt(dot(*this));
}

template <typename real_type>
const double
Vector3<real_type>::angle(const Vector3& v) const
{
  return std::acos(dot(v) / (magnitude() * v.magnitude()));
}

template <typename real_type>
Vector3<real_type>
Vector3<real_type>::unitize() const
{
  return Vector3<real_type>(*this) /= magnitude();
}

// template<typename real_type>
// const double Vector3<real_type>::dot(const Vector3 &rhs) const
// {
//   return data[0] * rhs[0] + data[1] * rhs[1] + data[2] * rhs[2];
// }

template <typename real_type>
Vector3<real_type>
Vector3<real_type>::cross(const Vector3& rhs) const
{
  return Vector3<real_type>(data[1] * rhs[2] - data[2] * rhs[1],
                            data[2] * rhs[0] - data[0] * rhs[2],
                            data[0] * rhs[1] - data[1] * rhs[0]);
}

// template<typename real_type>
// const real_type Vector3<real_type>::operator[](const int index) const
// {
//   assert(index >= 0 && index < 3);
//   return data[index];
// }

// template<typename real_type>
// real_type &Vector3<real_type>::operator[](const int index)
// {
//   assert(index >= 0 && index < 3);
//   return data[index];
// }

template <typename real_type>
Vector3<real_type>& Vector3<real_type>::operator=(const std::string& str)
{
  std::stringstream sstream(str);
  // std::cout << "Supplied: " << str << std::endl;
  sstream >> *this;
  // std::string test;
  // while (sstream >> test)
  // {
  //   std::cout << "Read out: " << test << std::endl;
  // }
  return *this;
}

template <typename real_type>
Vector3<real_type> Vector3<real_type>::operator+(const Vector3& rhs) const
{
  return Vector3<real_type>(*this) += rhs;
}

template <typename real_type>
Vector3<real_type>& Vector3<real_type>::operator+=(const Vector3& rhs)
{
  data[0] += rhs[0];
  data[1] += rhs[1];
  data[2] += rhs[2];
  return *this;
}

template <typename real_type>
Vector3<real_type> Vector3<real_type>::operator-(const Vector3& rhs) const
{
  return Vector3<real_type>(*this) -= rhs;
}

template <typename real_type>
Vector3<real_type>& Vector3<real_type>::operator-=(const Vector3& rhs)
{
  data[0] -= rhs[0];
  data[1] -= rhs[1];
  data[2] -= rhs[2];
  return *this;
}

template <typename real_type>
Vector3<real_type> Vector3<real_type>::operator-() const
{
  return *this * -1;
}

template <typename real_type>
Vector3<real_type> Vector3<real_type>::operator*(const Vector3& rhs) const
{
  return Vector3<real_type>(*this) *= rhs;
}

template <typename real_type>
Vector3<real_type> Vector3<real_type>::operator*(const double s) const
{
  return Vector3<real_type>(*this) *= s;
}

template <typename real_type>
Vector3<real_type>& Vector3<real_type>::operator*=(const double s)
{
  data[0] *= s;
  data[1] *= s;
  data[2] *= s;
  return *this;
}

template <typename real_type>
Vector3<real_type>& Vector3<real_type>::operator*=(const Vector3& rhs)
{
  data[0] *= rhs[0];
  data[1] *= rhs[1];
  data[2] *= rhs[2];
  return *this;
}

template <typename real_type>
Vector3<real_type> Vector3<real_type>::operator/(const double s) const
{
  return *this * (1 / s);
}

template <typename real_type>
Vector3<real_type>& Vector3<real_type>::operator/=(const double s)
{
  return * this *= (1 / s);
}

template <typename real_type>
std::ostream& operator<<(std::ostream& os, const Vector3<real_type>& v)
{
  os << "< " << v[0] << " " << v[1] << " " << v[2] << " >";
  return os;
}

template <typename real_type>
std::istream& operator>>(std::istream& is, Vector3<real_type>& v)
{
  real_type x = 0.0, y = 0.0, z = 0.0;
  is >> x >> y >> z;
  v.set(x, y, z);
  return is;
}