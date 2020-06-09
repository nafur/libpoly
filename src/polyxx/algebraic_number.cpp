#include "polyxx/algebraic_number.h"

#include <iostream>

namespace poly {

AlgebraicNumber::AlgebraicNumber(UPolynomial&& poly, const DyadicInterval& i)
{
  lp_algebraic_number_construct(&mValue, poly.release(), i.get_internal());
}
AlgebraicNumber::AlgebraicNumber(const UPolynomial& poly, const DyadicInterval& i)
{
  lp_algebraic_number_construct(&mValue, UPolynomial(poly).release(), i.get_internal());
}
AlgebraicNumber::AlgebraicNumber(const lp_algebraic_number_t& an)
{
  lp_algebraic_number_construct_copy(&mValue, &an);
}
AlgebraicNumber::AlgebraicNumber(const AlgebraicNumber& an)
{
  lp_algebraic_number_construct_copy(&mValue, an.get_internal());
}
AlgebraicNumber::AlgebraicNumber(AlgebraicNumber&& an)
{
  lp_algebraic_number_construct_zero(&mValue);
  lp_algebraic_number_swap(&mValue, an.get_internal());
}
AlgebraicNumber::~AlgebraicNumber() { lp_algebraic_number_destruct(&mValue); }
AlgebraicNumber& AlgebraicNumber::operator=(AlgebraicNumber an)
{
  std::swap(mValue, an.mValue);
  return *this;
}

lp_algebraic_number_t* AlgebraicNumber::get_internal() { return &mValue; }
const lp_algebraic_number_t* AlgebraicNumber::get_internal() const { return &mValue; }

std::ostream& operator<<(std::ostream& os, const AlgebraicNumber& v)
{
  return os << lp_algebraic_number_to_string(v.get_internal());
}

bool operator==(const AlgebraicNumber& lhs, const AlgebraicNumber& rhs)
{
  return lp_algebraic_number_cmp(lhs.get_internal(), rhs.get_internal()) == 0;
}
bool operator==(const AlgebraicNumber& lhs, const Integer& rhs)
{
  return lp_algebraic_number_cmp_integer(lhs.get_internal(), rhs.get_internal()) == 0;
}
bool operator==(const Integer& lhs, const AlgebraicNumber& rhs)
{
  return lp_algebraic_number_cmp_integer(rhs.get_internal(), lhs.get_internal()) == 0;
}

}  // namespace poly
