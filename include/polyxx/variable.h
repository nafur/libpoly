#pragma once

#include "../variable_db.h"
#include "context.h"

#include <iostream>

namespace poly
{

  /**
 * Implements a wrapper for lp_variable_t from libpoly.
 */
  class Variable
  {
    friend std::ostream &operator<<(std::ostream &os, const Variable &v);

    /** The context. */
    const Context &mContext;

    /** The actual variable. */
    lp_variable_t mVariable;

  public:
    /** Construct with a null variable. */
    Variable(const Context &c);
    Variable() : Variable(Context::get_context()) {}
    /** Construct from a lp_variable_t. */
    Variable(const Context &c, lp_variable_t var);
    Variable(lp_variable_t var) : Variable(Context::get_context(), var) {}
    /** Construct a new variable with the given name. */
    Variable(const Context &c, const char *name);
    Variable(const char *name) : Variable(Context::get_context(), name) {}

    /** Get the internal lp_variable_t. Note that it's only a type alias for long.
   */
    lp_variable_t get_internal() const;
  };

  /** Stream the given Variable to an output stream. */
  std::ostream &operator<<(std::ostream &os, const Variable &v);

  /** Compare two variables for equality. */
  bool operator==(const Variable &lhs, const Variable &rhs);
  /** Compare two variables for inequality. */
  bool operator!=(const Variable &lhs, const Variable &rhs);

} // namespace poly
