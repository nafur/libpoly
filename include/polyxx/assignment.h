#pragma once

#include "context.h"
#include "value.h"
#include "variable.h"

#include <iosfwd>
#include <memory>

namespace poly
{

  /**
 * Implements a wrapper for lp_assignment_t from libpoly.
 */
  class Assignment
  {
    const Context& mContext;

    /** The actual assignment. */
    deleting_unique_ptr<lp_assignment_t> mAssignment;

  public:
    /** Construct an empty assignment with a custom context. */
    Assignment(const Context& c);
    /** Construct an empty assignment. */
    Assignment() : Assignment(Context::get_context()) {}

    /** Get a non-const pointer to the internal lp_assignment_t. Handle with care!
   */
    lp_assignment_t *get_internal();
    /** Get a const pointer to the internal lp_assignment_t. */
    const lp_assignment_t *get_internal() const;

    /** Assign var to the given value. */
    void set(const Variable &var, const Value &value);
    /** Unassign the given variable. */
    void unset(const Variable &var);
    /** Retrieve a value from the Assignment. */
    Value get(const Variable &var) const;
    /** Clear the assignment. */
    void clear();
  };

  /** Stream the given Assignment to an output stream. */
  std::ostream &operator<<(std::ostream &os, const Assignment &a);

} // namespace poly
