#pragma once

#include "../value.h"

#include "algebraic_number.h"
#include "dyadic_rational.h"
#include "integer.h"
#include "rational.h"

#include <iosfwd>

namespace poly {

/**
 * Implements a wrapper for lp_value_t from libpoly.
 */
class Value
{
  /** The actual value. */
  lp_value_t mValue;

  Value(lp_value_type_t type, const void* data);

 public:
  /** Construct a none value. */
  Value();
  Value(long i);
  /** Create from a lp_value_t, creating a copy. */
  explicit Value(const lp_value_t* val);
  /** Copy from the given Value. */
  Value(const Value& val);

  Value(const AlgebraicNumber& an);
  Value(const DyadicRational& i);
  Value(const Integer& i);
  Value(const Rational& i);

  /** Copy from the given Value. */
  Value& operator=(const Value& v);
  /** Move from the given Value. */
  Value& operator=(Value&& v);
  
  /** Get a non-const pointer to the internal lp_value_t. Handle with care! */
  lp_value_t* get_internal();
  /** Get a const pointer to the internal lp_value_t. */
  const lp_value_t* get_internal() const;
  
  /** Return -infty */
  static Value minus_infty();
  /** Return +infty */
  static Value plus_infty();
};

static_assert(sizeof(Value) == sizeof(lp_value_t));
namespace detail {
  inline lp_value_t* cast_to(Value* i) {
    return reinterpret_cast<lp_value_t*>(i);
  }
  inline const lp_value_t* cast_to(const Value* i) {
    return reinterpret_cast<const lp_value_t*>(i);
  }
  inline Value* cast_from(lp_value_t* i) {
    return reinterpret_cast<Value*>(i);
  }
  inline const Value* cast_from(const lp_value_t* i) {
    return reinterpret_cast<const Value*>(i);
  }
}

void swap(Value& lhs, Value& rhs);

// RationalInterval approximate(const Value& v);
 
bool operator==(const Value& lhs, const Value& rhs);
bool operator!=(const Value& lhs, const Value& rhs);
bool operator<(const Value& lhs, const Value& rhs);
bool operator<=(const Value& lhs, const Value& rhs);
bool operator>(const Value& lhs, const Value& rhs);
bool operator>=(const Value& lhs, const Value& rhs);
 
bool operator==(const Value& lhs, const Rational& rhs);
bool operator!=(const Value& lhs, const Rational& rhs);
bool operator<(const Value& lhs, const Rational& rhs);
bool operator<=(const Value& lhs, const Rational& rhs);
bool operator>(const Value& lhs, const Rational& rhs);
bool operator>=(const Value& lhs, const Rational& rhs);
 
bool operator==(const Rational& lhs, const Value& rhs);
bool operator!=(const Rational& lhs, const Value& rhs);
bool operator<(const Rational& lhs, const Value& rhs);
bool operator<=(const Rational& lhs, const Value& rhs);
bool operator>(const Rational& lhs, const Value& rhs);
bool operator>=(const Rational& lhs, const Value& rhs);

/** Stream the given Value to an output stream. */
std::ostream& operator<<(std::ostream& os, const Value& v);

int sgn(const Value& v);

bool is_rational(const Value& v);
bool is_integer(const Value& v);
bool is_infinity(const Value& v);


double to_double(const Value& v);
AlgebraicNumber to_algebraic_number(const Value& v);
DyadicRational to_dyadic_rational(const Value& v);
Integer to_integer(const Value& v);
Rational to_rational(const Value& v);

Integer ceil(const Value& v);
Integer floor(const Value& v);

Integer numerator(const Value& v);
Integer denominator(const Value& v);

Value value_between(const lp_value_t* lhs,
                     bool l_strict,
                     const lp_value_t* rhs,
                     bool r_strict);

Value value_between(const Value& lhs,
                     bool l_strict,
                     const Value& rhs,
                     bool r_strict);

int approximate_size(const Value& lower, const Value& upper);

}  // namespace poly
