#pragma once

#include "../integer.h"

#include <iosfwd>
#include <gmpxx.h>

namespace poly {

/**
 * Implements a wrapper for lp_integer_t from libpoly.
 */
class Integer
{
  /** The actual integer. */
  lp_integer_t mInt;

 public:
  /** Construct a zero integer. */
  Integer();
  /** Construct from the given integer. */
  Integer(long i);
  /** Construct from the given string. */
  Integer(const char* x, int base);
  /** Copy from the given Integer. */
  Integer(const Integer& i);
  /** Copy from the given lp_integer_t. */
  Integer(const lp_integer_t& i);
  /** Constructs from a gmp integer. */
  Integer(const mpz_class& m);
  /** Custom destructor. */
  ~Integer();
  /** Assign from the given Integer. */
  Integer& operator=(const Integer& i);
  /** Assign from the given integer. */
  Integer& operator=(long i);

  /** Get a non-const pointer to the internal lp_integer_t. Handle with care! */
  lp_integer_t* get_internal();
  /** Get a const pointer to the internal lp_integer_t. */
  const lp_integer_t* get_internal() const;
};
/** Stream the given Integer to an output stream. */
std::ostream& operator<<(std::ostream& os, const Integer& i);

/** Compare two Integers. */
bool operator==(const Integer& lhs, const Integer& rhs);
/** Compare two Integers. */
bool operator!=(const Integer& lhs, const Integer& rhs);
/** Compare two Integers. */
bool operator<(const Integer& lhs, const Integer& rhs);
/** Compare two Integers. */
bool operator<=(const Integer& lhs, const Integer& rhs);
/** Compare two Integers. */
bool operator>(const Integer& lhs, const Integer& rhs);
/** Compare two Integers. */
bool operator>=(const Integer& lhs, const Integer& rhs);

/** Unary negation for an Integer. */
Integer operator-(const Integer& i);

/** Multiply and assign two Integers. */
Integer& operator*=(Integer& lhs, const Integer& rhs);

/** Divide and assign two Integers. Assumes the division is exact! */
Integer& operator/=(Integer& lhs, const Integer& rhs);

long to_int(const Integer& i);
double to_double(const Integer& i);

bool is_prime(const Integer& i);
bool is_zero(const Integer& i);

int sgn(const Integer& i);

/** Compute the GCD of two Integers. */
Integer gcd(const Integer& a, const Integer& b);

}  // namespace poly

