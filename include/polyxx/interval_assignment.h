#pragma once

#include <iosfwd>
#include <memory>

#include "../assignment.h"
#include "context.h"
#include "interval.h"
#include "variable.h"

namespace poly {

/**
 * Implements a wrapper for lp_interval_assignment_t from libpoly.
 */
class IntervalAssignment {
  /** The actual assignment. */
  lp_interval_assignment_t mAssignment;

 public:
  /** Construct an empty assignment with a custom context. */
  IntervalAssignment(const Context& c);
  /** Construct an empty assignment. */
  IntervalAssignment() : IntervalAssignment(Context::get_context()) {}
  ~IntervalAssignment();

  /** Get a non-const pointer to the internal lp_interval_assignment_t. Handle
   * with care!
   */
  lp_interval_assignment_t* get_internal();
  /** Get a const pointer to the internal lp_interval_assignment_t. */
  const lp_interval_assignment_t* get_internal() const;

  /** Assign var to the given value. */
  void set(const Variable& var, const Interval& interval);
  /** Unassign the given variable. */
  void unset(const Variable& var);
  /** Retrieve a value from the Assignment. */
  Interval get(const Variable& var) const;
  /** Clear the assignment. */
  void clear();
};

/** Stream the given Assignment to an output stream. */
std::ostream& operator<<(std::ostream& os, const IntervalAssignment& a);

}  // namespace poly
