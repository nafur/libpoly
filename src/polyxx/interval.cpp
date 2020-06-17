#include "polyxx/interval.h"

#include <cassert>

namespace poly {

Interval::Interval(const lp_interval_t* i) {
  lp_interval_construct_copy(get_internal(), i);
}

Interval::Interval(const Value& a, bool a_open, const Value& b, bool b_open) {
  lp_interval_construct(get_internal(), a.get_internal(), a_open ? 1 : 0,
                        b.get_internal(), b_open ? 1 : 0);
}

Interval::Interval(const Value& a, const Value& b)
    : Interval(a, true, b, true) {}

Interval::Interval(const Value& a) {
  lp_interval_construct_point(get_internal(), a.get_internal());
}

Interval::Interval(const Interval& i) {
  lp_interval_construct_copy(get_internal(), i.get_internal());
}

Interval::~Interval() { lp_interval_destruct(get_internal()); }

Interval& Interval::operator=(Interval i) {
  std::swap(mInterval, i.mInterval);
  return *this;
}

lp_interval_t* Interval::get_internal() { return &mInterval; }

const lp_interval_t* Interval::get_internal() const { return &mInterval; }

const Value& get_lower(const Interval& i) {
  return *detail::cast_from(lp_interval_get_lower_bound(i.get_internal()));
}
const Value& get_upper(const Interval& i) {
  return *detail::cast_from(lp_interval_get_upper_bound(i.get_internal()));
}

std::ostream& operator<<(std::ostream& os, const Interval& i) {
  if (i.get_internal()->is_point) {
    assert(!i.get_internal()->a_open && !i.get_internal()->b_open);
    os << "[ ";
    stream_ptr(os, lp_value_to_string(&(i.get_internal()->a)));
    os << " ; ";
    stream_ptr(os, lp_value_to_string(&(i.get_internal()->a)));
    return os << " ]";
  }
  os << (i.get_internal()->a_open ? "( " : "[ ");
  stream_ptr(os, lp_value_to_string(&(i.get_internal()->a)));
  os << " ; ";
  stream_ptr(os, lp_value_to_string(&(i.get_internal()->b)));
  os << (i.get_internal()->b_open ? " )" : " ]");
  return os;
}

lp_interval_cmp_t compare(const Interval& lhs, const Interval& rhs) {
  return lp_interval_cmp(lhs.get_internal(), rhs.get_internal());
}

bool operator==(const Interval& lhs, const Interval& rhs) {
  lp_interval_cmp_t res = compare(lhs, rhs);
  return res == LP_INTERVAL_CMP_EQ;
}
bool operator!=(const Interval& lhs, const Interval& rhs) {
  return !(lhs == rhs);
}
bool operator<(const Interval& lhs, const Interval& rhs) {
  lp_interval_cmp_t res = compare(lhs, rhs);
  return (res == LP_INTERVAL_CMP_LT_NO_INTERSECT) || (res == LP_INTERVAL_CMP_LT_WITH_INTERSECT) || (res == LP_INTERVAL_CMP_LT_WITH_INTERSECT_I1);
}
bool operator<=(const Interval& lhs, const Interval& rhs) {
  lp_interval_cmp_t res = compare(lhs, rhs);
  return (res == LP_INTERVAL_CMP_LT_NO_INTERSECT) || (res == LP_INTERVAL_CMP_LT_WITH_INTERSECT) || (res == LP_INTERVAL_CMP_LT_WITH_INTERSECT_I1) || (res == LP_INTERVAL_CMP_LEQ_WITH_INTERSECT_I2) || (res == LP_INTERVAL_CMP_EQ);
}
bool operator>(const Interval& lhs, const Interval& rhs) {
  return rhs < lhs;
}
bool operator>=(const Interval& lhs, const Interval& rhs) {
  return rhs <= lhs;
}


}  // namespace poly
