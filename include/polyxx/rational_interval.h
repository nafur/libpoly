#pragma once

#include "../rational_interval.h"

#include "dyadic_interval.h"
#include "interval.h"

#include <iosfwd>

namespace poly {

/**
 * Implements a wrapper for lp_rational_interval_t from libpoly.
 */
class RationalInterval
{
 private:
  /** The actual interval. */
  lp_rational_interval_t mInterval;

 public:
  explicit RationalInterval(const lp_rational_interval_t* ri);
  RationalInterval();
  RationalInterval(const Rational& a, bool a_open, const Rational& b, bool b_open);
  RationalInterval(const Rational& a, const Rational& b);
  RationalInterval(const Rational& a);
  RationalInterval(const RationalInterval& i);
  RationalInterval(const DyadicRational& a, bool a_open, const DyadicRational& b, bool b_open);
  RationalInterval(const DyadicRational& a, const DyadicRational& b);
  RationalInterval(const DyadicRational& a);
  RationalInterval(const DyadicInterval& i);
  ~RationalInterval();
  RationalInterval& operator=(RationalInterval i);

  /** Get a non-const pointer to the internal lp_interval_t. Handle with
   * care! */
  lp_rational_interval_t* get_internal();
  /** Get a const pointer to the internal lp_interval_t. */
  const lp_rational_interval_t* get_internal() const;
};

void swap(RationalInterval& lhs, RationalInterval& rhs);

/** Stream the given Interval to an output stream. */
std::ostream& operator<<(std::ostream& os, const Interval& i);

bool contains(const RationalInterval& ri, const AlgebraicNumber& an);
bool contains(const RationalInterval& ri, const DyadicRational& dr);
bool contains(const RationalInterval& ri, const Integer& i);
bool contains(const RationalInterval& ri, const Rational& r);
bool contains(const RationalInterval& ri, const Value& v);

bool operator==(const Interval& lhs, const Interval& rhs);

bool operator<(const Interval& lhs, const Interval& rhs);

bool lower_is_infty(const Interval& i);
bool upper_is_infty(const Interval& i);

bool interval_covers(const Interval& lhs, const Interval& rhs);
bool interval_connect(const Interval& lhs, const Interval& rhs);

}  // namespace poly
