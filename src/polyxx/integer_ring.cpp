#include "polyxx/integer_ring.h"

#include <iostream>
#include <utility>

#include "integer.h"

namespace poly {

IntegerRing::IntegerRing() : mRing(lp_Z) { lp_int_ring_attach(get_internal()); }

IntegerRing::IntegerRing(const Integer& m, bool is_prime)
    : mRing(lp_int_ring_create(m.get_internal(), is_prime ? 1 : 0))
{
}
IntegerRing::~IntegerRing() { lp_int_ring_detach(get_internal()); }

lp_int_ring_t* IntegerRing::get_internal() { return mRing.get(); }
const lp_int_ring_t* IntegerRing::get_internal() const { return mRing.get(); }

bool operator==(IntegerRing& lhs, IntegerRing& rhs)
{
  return lp_int_ring_equal(lhs.get_internal(), rhs.get_internal());
}

std::ostream& operator<<(std::ostream& os, IntegerRing& ir)
{
  return os << lp_int_ring_to_string(ir.get_internal());
}

}  // namespace poly
