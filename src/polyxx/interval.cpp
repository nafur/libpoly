#include "polyxx/interval.h"

#include <cassert>

namespace poly {

  Interval::Interval(const lp_interval_t* i) {
    lp_interval_construct_copy(get_internal(), i);
  }

Interval::Interval(const Value& a, bool a_open, const Value& b, bool b_open)
{
  lp_interval_construct(
      &mInterval, a.get_internal(), a_open ? 1 : 0, b.get_internal(), b_open ? 1 : 0);
}

Interval::Interval(const Value& a, const Value& b) : Interval(a, true, b, true)
{
}

Interval::Interval(const Value& a)
{
  lp_interval_construct_point(&mInterval, a.get_internal());
}

Interval::Interval(const Interval& i)
{
  lp_interval_construct_copy(&mInterval, i.get_internal());
}

Interval::~Interval() { lp_interval_destruct(&mInterval); }

Interval& Interval::operator=(Interval i)
{
  std::swap(mInterval, i.mInterval);
  return *this;
}

lp_interval_t* Interval::get_internal() { return &mInterval; }

const lp_interval_t* Interval::get_internal() const { return &mInterval; }

const Value& get_upper(const Interval& i) {
  return *detail::cast_from(lp_interval_get_upper_bound(i.get_internal()));
}

std::ostream& operator<<(std::ostream& os, const Interval& i)
{
  if (i.get_internal()->is_point)
  {
    assert(!i.get_internal()->a_open && !i.get_internal()->b_open);
    return os << "[ " << lp_value_to_string(&(i.get_internal()->a)) << " ; "
              << lp_value_to_string(&(i.get_internal()->a)) << " ]";
  }
  os << (i.get_internal()->a_open ? "( " : "[ ");
  os << lp_value_to_string(&(i.get_internal()->a)) << " ; "
     << lp_value_to_string(&(i.get_internal()->b));
  os << (i.get_internal()->b_open ? " )" : " ]");
  return os;
}

}  // namespace poly
