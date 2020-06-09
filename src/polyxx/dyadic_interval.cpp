#include "polyxx/dyadic_interval.h"

#include <iostream>

namespace poly {

DyadicInterval::DyadicInterval(const Integer& a, const Integer& b)
{
  lp_dyadic_interval_construct_from_integer(&mInterval, a.get_internal(), 1, b.get_internal(), 1);
}

DyadicInterval::DyadicInterval(const DyadicInterval& i)
{
  lp_dyadic_interval_construct_copy(&mInterval, i.get_internal());
}

DyadicInterval::~DyadicInterval() { lp_dyadic_interval_destruct(&mInterval); }

DyadicInterval& DyadicInterval::operator=(DyadicInterval i)
{
  std::swap(mInterval, i.mInterval);
  return *this;
}

lp_dyadic_interval_t* DyadicInterval::get_internal() { return &mInterval; }

const lp_dyadic_interval_t* DyadicInterval::get_internal() const { return &mInterval; }

std::ostream& operator<<(std::ostream& os, const DyadicInterval& i)
{
  os << (i.get_internal()->a_open ? "( " : "[ ");
  os << lp_dyadic_rational_to_string(&(i.get_internal()->a)) << " ; "
     << lp_dyadic_rational_to_string(&(i.get_internal()->b));
  os << (i.get_internal()->b_open ? " )" : " ]");
  return os;
}

}  // namespace poly
