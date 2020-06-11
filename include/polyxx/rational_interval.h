#pragma once

#include <iosfwd>

#include "../rational_interval.h"
#include "algebraic_number.h"
#include "dyadic_interval.h"
#include "integer.h"
#include "rational.h"
#include "value.h"

namespace poly {

/**
 * Implements a wrapper for lp_rational_interval_t from libpoly.
 */
class RationalInterval {
 private:
  /** The actual interval. */
  lp_rational_interval_t mInterval;

 public:
  explicit RationalInterval(const lp_rational_interval_t* ri);
  RationalInterval();
  RationalInterval(const Rational& a, bool a_open, const Rational& b,
                   bool b_open);
  RationalInterval(const Rational& a, const Rational& b);
  RationalInterval(const Rational& a);
  RationalInterval(const RationalInterval& i);
  RationalInterval(const DyadicRational& a, bool a_open,
                   const DyadicRational& b, bool b_open);
  RationalInterval(const DyadicRational& a, const DyadicRational& b);
  RationalInterval(const DyadicInterval& i);
  ~RationalInterval();
  RationalInterval& operator=(const RationalInterval& i);
  RationalInterval& operator=(RationalInterval&& i);

  /** Get a non-const pointer to the internal lp_interval_t. Handle with
   * care! */
  lp_rational_interval_t* get_internal();
  /** Get a const pointer to the internal lp_interval_t. */
  const lp_rational_interval_t* get_internal() const;
};

void swap(RationalInterval& lhs, RationalInterval& rhs);

/** Stream the given Interval to an output stream. */
std::ostream& operator<<(std::ostream& os, const RationalInterval& i);

bool contains(const RationalInterval& ri, const AlgebraicNumber& an);
bool contains(const RationalInterval& ri, const DyadicRational& dr);
bool contains(const RationalInterval& ri, const Integer& i);
bool contains(const RationalInterval& ri, const Rational& r);
bool contains(const RationalInterval& ri, const Value& v);
bool contains_zero(const RationalInterval& ri);

bool is_point(const RationalInterval& ri);
const Rational& get_point(const RationalInterval& ri);

int sgn(const RationalInterval& ri);

}  // namespace poly
