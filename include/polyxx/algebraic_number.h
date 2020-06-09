#pragma once

#include "../algebraic_number.h"

#include "dyadic_interval.h"
#include "integer.h"
#include "upolynomial.h"

#include <iosfwd>

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
  //AlgebraicNumber(const DyadicRational& dr);

  /** Construct from a defining polynomial and an isolating interval. */
  AlgebraicNumber(UPolynomial&& poly, const DyadicInterval& i);
  /** Construct from a defining polynomial and an isolating interval. */
  AlgebraicNumber(const UPolynomial& poly, const DyadicInterval& i);
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
std::ostream& operator<<(std::ostream& os, const AlgebraicNumber& v);

/** Compare two AlgebraicNumbers for equality. */
bool operator==(const AlgebraicNumber& lhs, const AlgebraicNumber& rhs);
/** Compare a AlgebraicNumber and an Integer for equality. */
bool operator==(const AlgebraicNumber& lhs, const Integer& rhs);
/** Compare an Integer and a AlgebraicNumber for equality. */
bool operator==(const Integer& lhs, const AlgebraicNumber& rhs);

}  // namespace poly
