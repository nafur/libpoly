#include "polyxx/interval_assignment.h"

namespace poly {

IntervalAssignment::IntervalAssignment(const Context &c) {
  lp_interval_assignment_construct(get_internal(), c.get_variable_db());
}
IntervalAssignment::~IntervalAssignment() {
  lp_interval_assignment_destruct(get_internal());
}

lp_interval_assignment_t *IntervalAssignment::get_internal() {
  return &mAssignment;
}
const lp_interval_assignment_t *IntervalAssignment::get_internal() const {
  return &mAssignment;
}

void IntervalAssignment::set(const Variable &var, const Interval &interval) {
  lp_interval_assignment_set_interval(get_internal(), var.get_internal(),
                                      interval.get_internal());
}
void IntervalAssignment::unset(const Variable &var) {
  lp_interval_assignment_set_interval(get_internal(), var.get_internal(),
                                      nullptr);
}
Interval IntervalAssignment::get(const Variable &var) const {
  return Interval(
      lp_interval_assignment_get_interval(get_internal(), var.get_internal()));
}
void IntervalAssignment::clear() {
  const lp_variable_db_t *var_db = get_internal()->var_db;
  lp_interval_assignment_destruct(get_internal());
  lp_interval_assignment_construct(get_internal(), var_db);
}

std::ostream &operator<<(std::ostream &os, const IntervalAssignment &a) {
  return stream_ptr(os, lp_interval_assignment_to_string(a.get_internal()));
}

}  // namespace poly