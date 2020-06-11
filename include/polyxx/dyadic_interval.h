#pragma once

#include <iosfwd>

#include "../dyadic_interval.h"
#include "dyadic_rational.h"
#include "integer.h"

namespace poly {

/**
 * Implements a wrapper for lp_dyadic_interval_t from libpoly.
 */
class DyadicInterval {
 private:
  /** The actual interval. */
  lp_dyadic_interval_t mInterval;

 public:
  explicit DyadicInterval(const lp_dyadic_interval_t* di);
  /** Construct the zero interval [0;0]. */
  DyadicInterval();
  DyadicInterval(const DyadicRational& dr);
  DyadicInterval(const DyadicRational& a, const DyadicRational& b);
  DyadicInterval(const DyadicRational& a, bool a_open, const DyadicRational& b,
                 bool b_open);
  /** Construct an open interval from the given two integers. */
  DyadicInterval(const Integer& a, const Integer& b);
  DyadicInterval(const Integer& a, bool a_open, const Integer& b, bool b_open);
  /** Copy from the given DyadicInterval. */
  DyadicInterval(const DyadicInterval& i);
  /** Custom destructor. */
  ~DyadicInterval();
  /** Assign from the given DyadicInterval. */
  DyadicInterval& operator=(DyadicInterval i);

  /** Get a non-const pointer to the internal lp_dyadic_interval_t. Handle with
   * care! */
  lp_dyadic_interval_t* get_internal();
  /** Get a const pointer to the internal lp_dyadic_interval_t. */
  const lp_dyadic_interval_t* get_internal() const;

  void collapse(const DyadicRational& dr);
  void set_lower(const DyadicRational& dr, bool open);
  void set_upper(const DyadicRational& dr, bool open);
  void scale(int n);
};

/** Stream the given DyadicInterval to an output stream. */
std::ostream& operator<<(std::ostream& os, const DyadicInterval& i);

std::pair<DyadicInterval, DyadicInterval> split(const DyadicInterval& di,
                                                bool left_open,
                                                bool right_open);

void swap(DyadicInterval& lhs, DyadicInterval& rhs);

bool operator==(const DyadicInterval& lhs, const DyadicInterval& rhs);

bool contains(const DyadicInterval& lhs, const DyadicRational& rhs);
bool contains_zero(const DyadicInterval& lhs);

bool disjoint(const DyadicInterval& lhs, const DyadicInterval& rhs);

bool is_point(const DyadicInterval& di);
DyadicRational get_point(const DyadicInterval& di);
int log_size(const DyadicInterval& di);

int sgn(const DyadicInterval& di);

bool operator==(const DyadicInterval& lhs, const Integer& rhs);
bool operator!=(const DyadicInterval& lhs, const Integer& rhs);
bool operator<(const DyadicInterval& lhs, const Integer& rhs);
bool operator<=(const DyadicInterval& lhs, const Integer& rhs);
bool operator>(const DyadicInterval& lhs, const Integer& rhs);
bool operator>=(const DyadicInterval& lhs, const Integer& rhs);

bool operator==(const Integer& lhs, const DyadicInterval& rhs);
bool operator!=(const Integer& lhs, const DyadicInterval& rhs);
bool operator<(const Integer& lhs, const DyadicInterval& rhs);
bool operator<=(const Integer& lhs, const DyadicInterval& rhs);
bool operator>(const Integer& lhs, const DyadicInterval& rhs);
bool operator>=(const Integer& lhs, const DyadicInterval& rhs);

bool operator==(const DyadicInterval& lhs, const DyadicRational& rhs);
bool operator!=(const DyadicInterval& lhs, const DyadicRational& rhs);
bool operator<(const DyadicInterval& lhs, const DyadicRational& rhs);
bool operator<=(const DyadicInterval& lhs, const DyadicRational& rhs);
bool operator>(const DyadicInterval& lhs, const DyadicRational& rhs);
bool operator>=(const DyadicInterval& lhs, const DyadicRational& rhs);

bool operator==(const DyadicRational& lhs, const DyadicInterval& rhs);
bool operator!=(const DyadicRational& lhs, const DyadicInterval& rhs);
bool operator<(const DyadicRational& lhs, const DyadicInterval& rhs);
bool operator<=(const DyadicRational& lhs, const DyadicInterval& rhs);
bool operator>(const DyadicRational& lhs, const DyadicInterval& rhs);
bool operator>=(const DyadicRational& lhs, const DyadicInterval& rhs);

bool operator==(const DyadicInterval& lhs, const Rational& rhs);
bool operator!=(const DyadicInterval& lhs, const Rational& rhs);
bool operator<(const DyadicInterval& lhs, const Rational& rhs);
bool operator<=(const DyadicInterval& lhs, const Rational& rhs);
bool operator>(const DyadicInterval& lhs, const Rational& rhs);
bool operator>=(const DyadicInterval& lhs, const Rational& rhs);

bool operator==(const Rational& lhs, const DyadicInterval& rhs);
bool operator!=(const Rational& lhs, const DyadicInterval& rhs);
bool operator<(const Rational& lhs, const DyadicInterval& rhs);
bool operator<=(const Rational& lhs, const DyadicInterval& rhs);
bool operator>(const Rational& lhs, const DyadicInterval& rhs);
bool operator>=(const Rational& lhs, const DyadicInterval& rhs);

}  // namespace poly
