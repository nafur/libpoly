#include "polyxx/integer.h"

#include <iostream>
#include <utility>

namespace poly {

Integer::Integer() { lp_integer_construct(&mInt); }

Integer::Integer(long i) { lp_integer_construct_from_int(lp_Z, &mInt, i); }

Integer::Integer(const char* x, int base) {
  lp_integer_construct_from_string(lp_Z, &mInt, x, base);
  }

Integer::Integer(const Integer& i)
{
  lp_integer_construct_copy(lp_Z, &mInt, i.get_internal());
}

Integer::Integer(const lp_integer_t& i) {
  lp_integer_construct_copy(lp_Z, &mInt, &i);
}

Integer::Integer(const mpz_class& m)
{
  lp_integer_construct_copy(lp_Z, &mInt, m.get_mpz_t());
}

Integer::~Integer() { lp_integer_destruct(&mInt); }

Integer& Integer::operator=(const Integer& i)
{
  lp_integer_assign(lp_Z, &mInt, i.get_internal());
  return *this;
}
Integer& Integer::operator=(long i)
{
  lp_integer_assign_int(lp_Z, &mInt, i);
  return *this;
}

lp_integer_t* Integer::get_internal() { return &mInt; }

const lp_integer_t* Integer::get_internal() const { return &mInt; }

std::ostream& operator<<(std::ostream& os, const Integer& i)
{
  return os << lp_integer_to_string(i.get_internal());
}

bool operator==(const Integer& lhs, const Integer& rhs)
{
  return lp_integer_cmp(lp_Z, lhs.get_internal(), rhs.get_internal()) == 0;
}
bool operator!=(const Integer& lhs, const Integer& rhs)
{
  return lp_integer_cmp(lp_Z, lhs.get_internal(), rhs.get_internal()) != 0;
}
bool operator<(const Integer& lhs, const Integer& rhs)
{
  return lp_integer_cmp(lp_Z, lhs.get_internal(), rhs.get_internal()) < 0;
}
bool operator<=(const Integer& lhs, const Integer& rhs)
{
  return lp_integer_cmp(lp_Z, lhs.get_internal(), rhs.get_internal()) <= 0;
}
bool operator>(const Integer& lhs, const Integer& rhs)
{
  return lp_integer_cmp(lp_Z, lhs.get_internal(), rhs.get_internal()) > 0;
}
bool operator>=(const Integer& lhs, const Integer& rhs)
{
  return lp_integer_cmp(lp_Z, lhs.get_internal(), rhs.get_internal()) >= 0;
}

Integer operator-(const Integer& i)
{
  Integer res;
  lp_integer_neg(lp_Z, res.get_internal(), i.get_internal());
  return res;
}

Integer& operator*=(Integer& lhs, const Integer& rhs)
{
  lp_integer_mul(lp_Z, lhs.get_internal(), lhs.get_internal(), rhs.get_internal());
  return lhs;
}

Integer& operator/=(Integer& lhs, const Integer& rhs)
{
  lp_integer_div_exact(lp_Z, lhs.get_internal(), lhs.get_internal(), rhs.get_internal());
  return lhs;
}

long to_int(const Integer& i) {
  return lp_integer_to_int(i.get_internal());
}

double to_double(const Integer& i) {
  return lp_integer_to_double(i.get_internal());
}

bool is_prime(const Integer& i) {
  return lp_integer_is_prime(i.get_internal());
}

bool is_zero(const Integer& i) {
  return lp_integer_is_zero(lp_Z, i.get_internal());
}

int sgn(const Integer& i) {
  return lp_integer_sgn(lp_Z, i.get_internal());
}

Integer gcd(const Integer& a, const Integer& b)
{
  Integer res;
  lp_integer_gcd_Z(res.get_internal(), a.get_internal(), b.get_internal());
  return res;
}

}  // namespace poly
