#pragma once

#include <gmpxx.h>

#include <iosfwd>

#include "../integer.h"
#include "integer_ring.h"

namespace poly {

class Rational;

/**
 * Implements a wrapper for lp_integer_t from libpoly.
 */
class Integer
{
  /** The actual integer. */
  lp_integer_t mInt;

 public:
  Integer();
  Integer(int i);
  Integer(long i);
  Integer(IntegerRing& ir, long i);
  Integer(const char* x, int base);
  Integer(IntegerRing& ir, const char* x, int base);
  Integer(const Integer& i);
  Integer(IntegerRing& ir, const Integer& i);
  Integer(const Rational& r);
  Integer(IntegerRing& ir, const Rational& r);
  Integer(const lp_integer_t& i);
  Integer(IntegerRing& ir, const lp_integer_t& i);
  Integer(const mpz_class& m);
  Integer(IntegerRing& ir, const mpz_class& m);
  explicit Integer(const lp_integer_t* i);
  Integer(IntegerRing& ir, const lp_integer_t* i);

  /** Custom destructor. */
  ~Integer();
  /** Assign from the given Integer. */
  Integer& operator=(const Integer& i);
  Integer& assign(IntegerRing& ir, const Integer& i);
  /** Assign from the given integer. */
  Integer& operator=(long i);
  Integer& assign(IntegerRing& ir, long i);

  /** Get a non-const pointer to the internal lp_integer_t. Handle with care! */
  lp_integer_t* get_internal();
  /** Get a const pointer to the internal lp_integer_t. */
  const lp_integer_t* get_internal() const;
};

static_assert(sizeof(Integer) == sizeof(lp_integer_t), "Please check the size of Integer.");
namespace detail {
  inline lp_integer_t* cast_to(Integer* i) {
    return reinterpret_cast<lp_integer_t*>(i);
  }
  inline const lp_integer_t* cast_to(const Integer* i) {
    return reinterpret_cast<const lp_integer_t*>(i);
  }
  inline Integer* cast_from(lp_integer_t* i) {
    return reinterpret_cast<Integer*>(i);
  }
  inline const Integer* cast_from(const lp_integer_t* i) {
    return reinterpret_cast<const Integer*>(i);
  }
}

/** Stream the given Integer to an output stream. */
std::ostream& operator<<(std::ostream& os, const Integer& i);

std::size_t bit_size(const Integer& i);

bool operator==(const Integer& lhs, const Integer& rhs);
bool operator!=(const Integer& lhs, const Integer& rhs);
bool operator<(const Integer& lhs, const Integer& rhs);
bool operator<=(const Integer& lhs, const Integer& rhs);
bool operator>(const Integer& lhs, const Integer& rhs);
bool operator>=(const Integer& lhs, const Integer& rhs);

int compare(IntegerRing& ir, const Integer& lhs, const Integer& rhs);
int compare(IntegerRing& ir, const Integer& lhs, long rhs);
int compare(IntegerRing& ir, long lhs, const Integer& rhs);

bool divides(const Integer& lhs, const Integer& rhs);
bool divides(IntegerRing& ir, const Integer& lhs, const Integer& rhs);

void swap(Integer& lhs, Integer& rhs);

Integer& operator++(Integer& i);
Integer& operator--(Integer& i);
Integer operator++(Integer& i, int);
Integer operator--(Integer& i, int);
Integer& increment(IntegerRing& ir, Integer& i);
Integer& decrement(IntegerRing& ir, Integer& i);

Integer operator+(const Integer& lhs, const Integer& rhs);
Integer& operator+=(Integer& lhs, const Integer& rhs);
Integer add(IntegerRing& ir, const Integer& lhs, const Integer& rhs);
Integer& add_assign(IntegerRing& ir, Integer& lhs, const Integer& rhs);

Integer operator-(const Integer& lhs, const Integer& rhs);
Integer& operator-=(Integer& lhs, const Integer& rhs);
Integer sub(IntegerRing& ir, const Integer& lhs, const Integer& rhs);
Integer& sub_assign(IntegerRing& ir, Integer& lhs, const Integer& rhs);

Integer operator-(const Integer& i);
Integer neg(IntegerRing& ir, const Integer& i);

Integer abs(const Integer& i);
Integer abs(IntegerRing& ir, const Integer& i);

Integer inverse(IntegerRing& ir, const Integer& i);

Integer operator*(const Integer& lhs, const Integer& rhs);
Integer operator*(const Integer& lhs, long rhs);
Integer operator*(long lhs, const Integer& rhs);
Integer& operator*=(Integer& lhs, const Integer& rhs);
Integer& operator*=(Integer& lhs, long rhs);
Integer mul(IntegerRing& ir, const Integer& lhs, const Integer& rhs);
Integer mul(IntegerRing& ir, const Integer& lhs, long rhs);
Integer mul(IntegerRing& ir, long lhs, const Integer& rhs);
Integer& mul_assign(IntegerRing& ir, Integer& lhs, const Integer& rhs);
Integer& mul_assign(IntegerRing& ir, Integer& lhs, long rhs);

Integer mul_pow2(const Integer& lhs, unsigned rhs);
Integer mul_pow2(IntegerRing& ir, const Integer& lhs, unsigned rhs);

Integer pow(const Integer& lhs, unsigned rhs);
Integer pow(IntegerRing& ir, const Integer& lhs, unsigned rhs);

Integer sqrt(const Integer& i);

Integer& add_mul(Integer& lhs, const Integer& a, const Integer& b);
Integer& add_mul(IntegerRing& ir,
                 Integer& lhs,
                 const Integer& a,
                 const Integer& b);
Integer& add_mul(Integer& lhs, const Integer& a, int b);
Integer& add_mul(IntegerRing& ir, Integer& lhs, const Integer& a, int b);

Integer& sub_mul(Integer& lhs, const Integer& a, const Integer& b);
Integer& sub_mul(IntegerRing& ir,
                 Integer& lhs,
                 const Integer& a,
                 const Integer& b);

Integer operator/(const Integer& lhs, const Integer& rhs);
Integer& operator/=(Integer& lhs, const Integer& rhs);

Integer operator%(const Integer& lhs, const Integer& rhs);
Integer& operator%=(Integer& lhs, const Integer& rhs);

Integer div_exact(const Integer& lhs, const Integer& rhs);
Integer div_exact(IntegerRing& ir, const Integer& lhs, const Integer& rhs);

Integer div_rem(Integer& rem, const Integer& lhs, const Integer& rhs);

Integer div_rem_pow2(Integer& rem, const Integer& lhs, unsigned rhs);

long to_int(const Integer& i);
double to_double(const Integer& i);

bool is_prime(const Integer& i);
bool is_zero(const Integer& i);
bool is_zero(IntegerRing& ir, const Integer& i);
bool is_in_ring(IntegerRing& ir, const Integer& i);

std::size_t hash(const Integer& i);

int sgn(const Integer& i);
int sgn(IntegerRing& ir, const Integer& i);

Integer gcd(const Integer& a, const Integer& b);
Integer lcm(const Integer& a, const Integer& b);

}  // namespace poly

namespace std {
template <>
struct hash<poly::Integer>
{
  std::size_t operator()(const poly::Integer& i) const { return poly::hash(i); }
};
}  // namespace std
