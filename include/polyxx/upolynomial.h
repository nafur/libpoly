#pragma once

#include <iosfwd>
#include <utility>
#include <vector>

#include "../integer.h"
#include "../upolynomial.h"
#include "dyadic_rational.h"
#include "integer.h"
#include "integer_ring.h"
#include "rational.h"
#include "variable.h"

namespace poly {

/**
 * Implements a wrapper for lp_upolynomial_t from libpoly.
 */
class UPolynomial {
  /** The actual univariate polynomial. */
  deleting_unique_ptr<lp_upolynomial_t> mPoly;

 public:
  UPolynomial(const std::vector<Integer>& coefficients);
  UPolynomial(IntegerRing& ir, const std::vector<Integer>& coefficients);
  UPolynomial(const std::vector<long>& coefficients);
  UPolynomial(IntegerRing& ir, const std::vector<long>& coefficients);

  UPolynomial(std::size_t degree, long c);
  UPolynomial(IntegerRing& ir, std::size_t degree, long c);

  UPolynomial(const UPolynomial& poly);
  UPolynomial(UPolynomial&& poly);
  UPolynomial(IntegerRing& ir, const UPolynomial& poly);

  /** Create from a lp_upolynomial_t pointer, claiming it's ownership. */
  explicit UPolynomial(lp_upolynomial_t* poly);
  explicit UPolynomial(const lp_upolynomial_t* poly);

  /** Get a non-const pointer to the internal lp_upolynomial_t. Handle with
   * care! */
  lp_upolynomial_t* get_internal();
  /** Get a const pointer to the internal lp_upolynomial_t. */
  const lp_upolynomial_t* get_internal() const;
  /** Release the lp_upolynomial_t pointer. This yields ownership of the
   * returned pointer. */
  lp_upolynomial_t* release();
};

std::size_t degree(const UPolynomial& p);

const Integer& leading_coefficient(const UPolynomial& p);
const Integer& constant_coefficient(const UPolynomial& p);

std::vector<Integer> coefficients(const UPolynomial& p);

/** Stream the given UPolynomial to an output stream. */
std::ostream& operator<<(std::ostream& os, const UPolynomial& p);

bool is_zero(const UPolynomial& p);
bool is_one(const UPolynomial& p);
bool is_monic(const UPolynomial& p);
bool is_primitive(const UPolynomial& p);

Integer evaluate_at(const UPolynomial& p, const Integer& i);
Rational evaluate_at(const UPolynomial& p, const Rational& r);
DyadicRational evaluate_at(const UPolynomial& p, const DyadicRational& i);

int sign_at(const UPolynomial& p, const Integer& i);
int sign_at(const UPolynomial& p, const Rational& r);
int sign_at(const UPolynomial& p, const DyadicRational& i);

bool operator==(const UPolynomial& lhs, const UPolynomial& rhs);
bool operator!=(const UPolynomial& lhs, const UPolynomial& rhs);
bool operator<(const UPolynomial& lhs, const UPolynomial& rhs);
bool operator<=(const UPolynomial& lhs, const UPolynomial& rhs);
bool operator>(const UPolynomial& lhs, const UPolynomial& rhs);
bool operator>=(const UPolynomial& lhs, const UPolynomial& rhs);

UPolynomial subst_x_neg(const UPolynomial& p);
UPolynomial operator-(const UPolynomial& lhs);
void neg(UPolynomial& p);

/** Add two univariate polynomials. */
UPolynomial operator+(const UPolynomial& lhs, const UPolynomial& rhs);
/** Subtract two univariate polynomials. */
UPolynomial operator-(const UPolynomial& lhs, const UPolynomial& rhs);
/** Multiply two univariate polynomials. */
UPolynomial operator*(const UPolynomial& lhs, const UPolynomial& rhs);
UPolynomial operator*(const UPolynomial& lhs, const Integer& rhs);

UPolynomial pow(const UPolynomial& lhs, long rhs);

UPolynomial derivative(const UPolynomial& p);

bool divides(const UPolynomial& lhs, const UPolynomial& rhs);

UPolynomial div_degrees(const UPolynomial& lhs, long rhs);

UPolynomial div_exact(const UPolynomial& lhs, const UPolynomial& rhs);
UPolynomial div_exact(const UPolynomial& lhs, const Integer& rhs);
UPolynomial rem_exact(const UPolynomial& lhs, const UPolynomial& rhs);
std::pair<UPolynomial, UPolynomial> div_rem_exact(const UPolynomial& lhs,
                                                  const UPolynomial& rhs);
std::pair<UPolynomial, UPolynomial> div_rem_pseudo(const UPolynomial& lhs,
                                                   const UPolynomial& rhs);

Integer content(const UPolynomial& p);
void make_primitive(const UPolynomial& p);
UPolynomial primitive_part(const UPolynomial& p);

UPolynomial gcd(const UPolynomial& lhs, const UPolynomial& rhs);
UPolynomial extended_gcd(const UPolynomial& lhs, const UPolynomial& rhs,
                         UPolynomial& u, UPolynomial& v);
void solve_bezout(const UPolynomial& p, const UPolynomial& q,
                  const UPolynomial& r, UPolynomial& u, UPolynomial& v);

/**
 * Compute a square-free factorization of a univariate polynomial.
 * Attention: this does not yield a full factorization!
 */
// TODO: Is it useful to have a UPolynomialFactors object?
std::vector<UPolynomial> square_free_factors(const UPolynomial& p,
                                             bool with_constant = false);

std::vector<UPolynomial> sturm_sequence(const UPolynomial& p);

}  // namespace poly
