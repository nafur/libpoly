#include "polyxx/rational.h"

#include <iostream>

namespace poly
{

    Rational::Rational()
    {
        lp_rational_construct(&mRat);
    }

    Rational::Rational(const Rational &r)
    {
        lp_rational_construct_copy(&mRat, r.get_internal());
    }

    Rational::Rational(const Integer &num, const Integer &denom)
    {
        lp_rational_construct_from_div(&mRat, num.get_internal(), denom.get_internal());
    }
    Rational::Rational(long num, unsigned long denom)
    {
        lp_rational_construct_from_int(&mRat, num, denom);
    }
    Rational::Rational(const Integer &i)
    {
        lp_rational_construct_from_integer(&mRat, i.get_internal());
    }
    Rational::Rational(double d)
    {
        lp_rational_construct_from_double(&mRat, d);
    }

    Rational::~Rational()
    {
        lp_rational_destruct(&mRat);
    }

    Rational &Rational::operator=(const Rational &r)
    {
        lp_rational_assign(&mRat, r.get_internal());
        return *this;
    }
    lp_rational_t *Rational::get_internal()
    {
        return &mRat;
    }
    const lp_rational_t *Rational::get_internal() const
    {
        return &mRat;
    }

    std::ostream& operator<<(std::ostream& os, const Rational& r) {
        return os << lp_rational_to_string(r.get_internal());
    }

double to_double(const Rational& r) {
    return lp_rational_to_double(r.get_internal());
}

int sgn(const Rational& r) {
    return lp_rational_sgn(r.get_internal());
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lp_rational_cmp(lhs.get_internal(), rhs.get_internal()) == 0;
}
bool operator!=(const Rational& lhs, const Rational& rhs) {
    return lp_rational_cmp(lhs.get_internal(), rhs.get_internal()) != 0;
}
bool operator<(const Rational& lhs, const Rational& rhs) {
    return lp_rational_cmp(lhs.get_internal(), rhs.get_internal()) < 0;
}
bool operator<=(const Rational& lhs, const Rational& rhs) {
    return lp_rational_cmp(lhs.get_internal(), rhs.get_internal()) <= 0;
}
bool operator>(const Rational& lhs, const Rational& rhs) {
    return lp_rational_cmp(lhs.get_internal(), rhs.get_internal()) > 0;
}
bool operator>=(const Rational& lhs, const Rational& rhs) {
    return lp_rational_cmp(lhs.get_internal(), rhs.get_internal()) >= 0;
}

} // namespace poly