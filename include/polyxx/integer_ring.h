#pragma once

#include <iosfwd>
#include <memory>

#include "../integer.h"
#include "utils.h"

namespace poly {

class Integer;

class IntegerRing
{
  deleting_unique_ptr<lp_int_ring_t> mRing;

 public:
  IntegerRing();
  IntegerRing(const Integer& m, bool is_prime);

  /** Get a non-const pointer to the internal lp_int_ring_t. Handle with care!
   */
  lp_int_ring_t* get_internal();
  /** Get a const pointer to the internal lp_int_ring_t. */
  const lp_int_ring_t* get_internal() const;

  static IntegerRing Z;
};

bool operator==(const IntegerRing& lhs, const IntegerRing& rhs);

/** Stream the given IntegerRing to an output stream. */
std::ostream& operator<<(std::ostream& os, const IntegerRing& ir);

}  // namespace poly
