#pragma once

#include "../dyadic_interval.h"

#include <iosfwd>

#include "integer.h"

namespace poly {

/**
 * Implements a wrapper for lp_dyadic_interval_t from libpoly.
 */
class DyadicInterval
{
 private:
  /** The actual interval. */
  lp_dyadic_interval_t mInterval;

 public:
  /** Disallow the default constructor. */
  DyadicInterval() = delete;
  /** Construct an open interval from the given two integers. */
  DyadicInterval(const Integer& a, const Integer& b);
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
};

/** Stream the given DyadicInterval to an output stream. */
std::ostream& operator<<(std::ostream& os, const DyadicInterval& i);

}  // namespace poly
