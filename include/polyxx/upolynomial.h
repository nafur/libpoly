#pragma once

#include "../integer.h"
#include "../upolynomial.h"

#include "integer.h"
#include "integer_ring.h"
#include "variable.h"

#include <iosfwd>
#include <vector>

namespace poly {

/**
 * Implements a wrapper for lp_upolynomial_t from libpoly.
 */
class UPolynomial
{
  /** The actual univariate polynomial. */
  deleting_unique_ptr<lp_upolynomial_t> mPoly;

 public:
  UPolynomial(const std::vector<Integer>& coefficients);
  UPolynomial(IntegerRing& ir, const std::vector<Integer>& coefficients);

  UPolynomial(std::size_t degree, long c);
  UPolynomial(IntegerRing& ir, std::size_t degree, long c);

  UPolynomial(const UPolynomial& poly);
  UPolynomial(UPolynomial&& poly);

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

/** Stream the given UPolynomial to an output stream. */
std::ostream& operator<<(std::ostream& os, const UPolynomial& p);

/** Add two univariate polynomials. */
UPolynomial operator+(const UPolynomial& lhs, const UPolynomial& rhs);
/** Subtract two univariate polynomials. */
UPolynomial operator-(const UPolynomial& lhs, const UPolynomial& rhs);
/** Multiply two univariate polynomials. */
UPolynomial operator*(const UPolynomial& lhs, const UPolynomial& rhs);

/** Obtain the degree of the given univariate polynomial. */
std::size_t degree(const UPolynomial& p);

/**
 * Compute a square-free factorization of a univariate polynomial.
 * Attention: this does not yield a full factorization!
 */
std::vector<UPolynomial> square_free_factors(const UPolynomial& p,
                                             bool with_constant = false);

}  // namespace poly
