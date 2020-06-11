#include "polyxx/value.h"

namespace poly {

Value::Value(lp_value_type_t type, const void* data) {
  lp_value_construct(get_internal(), type, data);
}

Value::Value() { lp_value_construct_none(&mValue); }
Value::Value(long i) {
  lp_value_construct_int(get_internal(), i);
}
Value::Value(const lp_value_t* val) {
  lp_value_construct_copy(get_internal(), val);
}
Value::Value(const Value& val) {
  lp_value_construct_copy(get_internal(), val.get_internal());
}

Value::Value(const Integer& i)
    : Value(lp_value_type_t::LP_VALUE_INTEGER, i.get_internal()) {}
Value::Value(const AlgebraicNumber& an)
    : Value(lp_value_type_t::LP_VALUE_ALGEBRAIC, an.get_internal()) {}

Value& Value::operator=(const Value& v) {
  lp_value_assign(get_internal(), v.get_internal());
  return *this;
}
Value& Value::operator=(Value&& v) {
  mValue = std::move(v.mValue);
  return *this;
}

lp_value_t* Value::get_internal() { return &mValue; }
const lp_value_t* Value::get_internal() const { return &mValue; }

Value Value::minus_infty() { return Value(LP_VALUE_MINUS_INFINITY, nullptr); }
Value Value::plus_infty() { return Value(LP_VALUE_PLUS_INFINITY, nullptr); }

const Integer& to_integer(const Value& v) {
  return *detail::cast_from(&v.get_internal()->value.z);
}

const AlgebraicNumber& to_algebraic_number(const Value& v) {
  return *detail::cast_from(&v.get_internal()->value.a);
}

std::ostream& operator<<(std::ostream& os, const Value& v) {
  return os << lp_value_to_string(v.get_internal());
}
bool operator==(const Value& lhs, const Value& rhs) {
  return lp_value_cmp(lhs.get_internal(), rhs.get_internal()) == 0;
}
bool operator!=(const Value& lhs, const Value& rhs) {
  if (lhs.get_internal()->type == LP_VALUE_NONE) return true;
  if (rhs.get_internal()->type == LP_VALUE_NONE) return true;
  return lp_value_cmp(lhs.get_internal(), rhs.get_internal()) != 0;
}
bool operator<(const Value& lhs, const Value& rhs) {
  return lp_value_cmp(lhs.get_internal(), rhs.get_internal()) < 0;
}

Value sample_between(const lp_value_t* lhs, bool l_strict,
                     const lp_value_t* rhs, bool r_strict) {
  Value res;
  lp_value_get_value_between(lhs, l_strict ? 1 : 0, rhs, r_strict ? 1 : 0,
                             res.get_internal());
  return res;
}

Value sample_between(const Value& lhs, bool l_strict, const Value& rhs,
                     bool r_strict) {
  return sample_between(lhs.get_internal(), l_strict, rhs.get_internal(),
                        r_strict);
}

}  // namespace poly
