#pragma once

#include "../value.h"

#include "algebraic_number.h"
#include "integer.h"

#include <iosfwd>

namespace poly {

/**
 * Implements a wrapper for lp_value_t from libpoly.
 */
class Value
{
  /** The actual value. */
  deleting_unique_ptr<lp_value_t> mValue;

 public:
  /** Construct a none value. */
  Value();
  /** Create from a lp_value_t, creating a copy. */
  Value(const lp_value_t& val);
  /** Create from a lp_value_t pointer, claiming it's ownership. */
  Value(lp_value_t* ptr);
  /** Copy from the given Value. */
  Value(const Value& val);
  /** Move from the given Value. */
  Value(Value&& val);

  /** Construct from an integer. */
  Value(const Integer& i);
  /** Construct from an algebraic number. */
  Value(const AlgebraicNumber& an);

  /** Copy from the given Value. */
  Value& operator=(const Value& v);
  /** Move from the given Value. */
  Value& operator=(Value&& v);
  /** Assign from the given lp_value_t pointer, claiming it's ownership. */
  Value& operator=(lp_value_t* v);

  /** Get a non-const pointer to the internal lp_value_t. Handle with care! */
  lp_value_t* get_internal();
  /** Get a const pointer to the internal lp_value_t. */
  const lp_value_t* get_internal() const;
  /** Release the lp_value_t pointer. This yields ownership of the returned
   * pointer. */
  lp_value_t* release();

  /** Return -infty */
  static Value minus_infty();
  /** Return +infty */
  static Value plus_infty();

  Integer as_integer() const;
  AlgebraicNumber as_algebraic_number() const;
};

/** Stream the given Value to an output stream. */
std::ostream& operator<<(std::ostream& os, const Value& v);
/** Compare values for equality. */
bool operator==(const Value& lhs, const Value& rhs);
/** Compare values for disequality. */
bool operator!=(const Value& lhs, const Value& rhs);
/** Compare two values. */
bool operator<(const Value& lhs, const Value& rhs);

Value sample_between(const lp_value_t* lhs,
                     bool l_strict,
                     const lp_value_t* rhs,
                     bool r_strict);

Value sample_between(const Value& lhs,
                     bool l_strict,
                     const Value& rhs,
                     bool r_strict);

}  // namespace poly
