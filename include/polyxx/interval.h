#pragma once

#include <iosfwd>

#include "../interval.h"
#include "value.h"

namespace poly {

/**
 * Implements a wrapper for lp_interval_t.
 */
class Interval {
 private:
  /** The actual interval. */
  lp_interval_t mInterval;

 public:
  explicit Interval(const lp_interval_t* i);
  Interval();
  /** Construct an open interval from the given two values and bound types. */
  Interval(const Value& a, bool a_open, const Value& b, bool b_open);
  /** Construct an open interval from the given two values. */
  Interval(const Value& a, const Value& b);
  /** Construct a point interval from the given value. */
  Interval(const Value& a);
  /** Copy from the given Interval. */
  Interval(const Interval& i);
  /** Custom destructor. */
  ~Interval();
  /** Assign from the given Interval. */
  Interval& operator=(Interval i);

  /** Get a non-const pointer to the internal lp_interval_t. Handle with
   * care! */
  lp_interval_t* get_internal();
  /** Get a const pointer to the internal lp_interval_t. */
  const lp_interval_t* get_internal() const;

  static Interval full();
};

static_assert(sizeof(Interval) == sizeof(lp_interval_t),
              "Please check the size of Interval.");

void swap(Interval& lhs, Interval& rhs);

bool contains(const Interval& i, const Value& v);
int log_size(const Interval& i);

/** Stream the given Interval to an output stream. */
std::ostream& operator<<(std::ostream& os, const Interval& i);

bool is_point(const Interval& i);
bool is_full(const Interval& i);
const Value& get_point(const Interval& i);
const Value& get_lower(const Interval& i);
const Value& get_upper(const Interval& i);

Value pick_value(const Interval& i);

int compare_lower(const Interval& lhs, const Interval& rhs);
int compare_upper(const Interval& lhs, const Interval& rhs);

bool operator==(const Interval& lhs, const Interval& rhs);
bool operator!=(const Interval& lhs, const Interval& rhs);
bool operator<(const Interval& lhs, const Interval& rhs);
bool operator<=(const Interval& lhs, const Interval& rhs);
bool operator>(const Interval& lhs, const Interval& rhs);
bool operator>=(const Interval& lhs, const Interval& rhs);

int sgn(const Interval& i);
Interval pow(const Interval& i, unsigned n);
Interval operator+(const Interval& lhs, const Interval& rhs);
Interval operator*(const Interval& lhs, const Interval& rhs);

}  // namespace poly
