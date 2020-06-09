#pragma once

#include <iosfwd>

#include "../algebraic_number.h"
#include "dyadic_interval.h"
#include "dyadic_rational.h"
#include "integer.h"
#include "upolynomial.h"

namespace poly {

/**
 * Implements a wrapper for lp_algebraic_number_t from libpoly.
 */
class AlgebraicNumber
{
  /** The actual algebraic number. */
  lp_algebraic_number_t mValue;

 public:
  /** Construct as zero. */
  AlgebraicNumber();
  /** Copy from the given AlgebraicNumber. */
  AlgebraicNumber(const AlgebraicNumber& an);
  /** Move from the given AlgebraicNumber. */
  AlgebraicNumber(AlgebraicNumber&& an);

  /** Construct from a DyadicRational */
  AlgebraicNumber(const DyadicRational& dr);

  /** Construct from a defining polynomial and an isolating interval. */
  AlgebraicNumber(UPolynomial&& poly, const DyadicInterval& di);
  /** Construct from a defining polynomial and an isolating interval. */
  AlgebraicNumber(const UPolynomial& poly, const DyadicInterval& di);
  /** Construct from a lp_algebraic_number_t, copying its contents. */
  AlgebraicNumber(const lp_algebraic_number_t& an);
  /** Custom destructor. */
  ~AlgebraicNumber();
  /** Assign from the given AlgebraicNumber. */
  AlgebraicNumber& operator=(AlgebraicNumber an);

  /** Get a non-const pointer to the internal lp_algebraic_number_t. Handle with
   * care! */
  lp_algebraic_number_t* get_internal();
  /** Get a const pointer to the internal lp_algebraic_number_t. */
  const lp_algebraic_number_t* get_internal() const;
};
/** Stream the given AlgebraicNumber to an output stream. */
std::ostream& operator<<(std::ostream& os, const AlgebraicNumber& an);

void swap(AlgebraicNumber& lhs, AlgebraicNumber& rhs);
int sgn(const AlgebraicNumber& an);

bool operator==(const AlgebraicNumber& lhs, const AlgebraicNumber& rhs);
bool operator!=(const AlgebraicNumber& lhs, const AlgebraicNumber& rhs);
bool operator<(const AlgebraicNumber& lhs, const AlgebraicNumber& rhs);
bool operator<=(const AlgebraicNumber& lhs, const AlgebraicNumber& rhs);
bool operator>(const AlgebraicNumber& lhs, const AlgebraicNumber& rhs);
bool operator>=(const AlgebraicNumber& lhs, const AlgebraicNumber& rhs);

bool operator==(const AlgebraicNumber& lhs, const Integer& rhs);
bool operator!=(const AlgebraicNumber& lhs, const Integer& rhs);
bool operator<(const AlgebraicNumber& lhs, const Integer& rhs);
bool operator<=(const AlgebraicNumber& lhs, const Integer& rhs);
bool operator>(const AlgebraicNumber& lhs, const Integer& rhs);
bool operator>=(const AlgebraicNumber& lhs, const Integer& rhs);

bool operator==(const Integer& lhs, const AlgebraicNumber& rhs);
bool operator!=(const Integer& lhs, const AlgebraicNumber& rhs);
bool operator<(const Integer& lhs, const AlgebraicNumber& rhs);
bool operator<=(const Integer& lhs, const AlgebraicNumber& rhs);
bool operator>(const Integer& lhs, const AlgebraicNumber& rhs);
bool operator>=(const Integer& lhs, const AlgebraicNumber& rhs);

bool operator==(const AlgebraicNumber& lhs, const DyadicRational& rhs);
bool operator!=(const AlgebraicNumber& lhs, const DyadicRational& rhs);
bool operator<(const AlgebraicNumber& lhs, const DyadicRational& rhs);
bool operator<=(const AlgebraicNumber& lhs, const DyadicRational& rhs);
bool operator>(const AlgebraicNumber& lhs, const DyadicRational& rhs);
bool operator>=(const AlgebraicNumber& lhs, const DyadicRational& rhs);

bool operator==(const DyadicRational& lhs, const AlgebraicNumber& rhs);
bool operator!=(const DyadicRational& lhs, const AlgebraicNumber& rhs);
bool operator<(const DyadicRational& lhs, const AlgebraicNumber& rhs);
bool operator<=(const DyadicRational& lhs, const AlgebraicNumber& rhs);
bool operator>(const DyadicRational& lhs, const AlgebraicNumber& rhs);
bool operator>=(const DyadicRational& lhs, const AlgebraicNumber& rhs);

bool operator==(const AlgebraicNumber& lhs, const Rational& rhs);
bool operator!=(const AlgebraicNumber& lhs, const Rational& rhs);
bool operator<(const AlgebraicNumber& lhs, const Rational& rhs);
bool operator<=(const AlgebraicNumber& lhs, const Rational& rhs);
bool operator>(const AlgebraicNumber& lhs, const Rational& rhs);
bool operator>=(const AlgebraicNumber& lhs, const Rational& rhs);

bool operator==(const Rational& lhs, const AlgebraicNumber& rhs);
bool operator!=(const Rational& lhs, const AlgebraicNumber& rhs);
bool operator<(const Rational& lhs, const AlgebraicNumber& rhs);
bool operator<=(const Rational& lhs, const AlgebraicNumber& rhs);
bool operator>(const Rational& lhs, const AlgebraicNumber& rhs);
bool operator>=(const Rational& lhs, const AlgebraicNumber& rhs);

double to_double(const AlgebraicNumber& an);

Rational to_rational_approximation(const AlgebraicNumber& an);

DyadicRational midpoint_dyadic(const AlgebraicNumber& an);
Rational midpoint_rational(const AlgebraicNumber& an);
void refine(AlgebraicNumber& an);
void refine_const(const AlgebraicNumber& an);

AlgebraicNumber operator+(const AlgebraicNumber& lhs,
                          const AlgebraicNumber& rhs);
AlgebraicNumber operator-(const AlgebraicNumber& lhs,
                          const AlgebraicNumber& rhs);
AlgebraicNumber operator-(const AlgebraicNumber& an);
AlgebraicNumber operator*(const AlgebraicNumber& lhs,
                          const AlgebraicNumber& rhs);
AlgebraicNumber pow(const AlgebraicNumber& lhs, unsigned n);

bool is_rational(const AlgebraicNumber& an);
bool is_integer(const AlgebraicNumber& an);

Integer ceil(const AlgebraicNumber& an);
Integer floor(const AlgebraicNumber& an);

}  // namespace poly
