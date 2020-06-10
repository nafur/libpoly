#pragma once

#include "integer.h"

#include "../rational.h"

#include <iosfwd>

namespace poly
{

    class Rational
    {

        lp_rational_t mRat;

    public:
        explicit Rational(const lp_rational_t* r);
        /** Construct as zero. */
        Rational();
        /** Construct as copy of r. */
        Rational(const Rational &r);

        Rational(long num, unsigned long denom);
        Rational(const Integer &num, const Integer &denom);
        Rational(const Integer &i);
        /** Construct as d. */
        Rational(double d);

        ~Rational();

        /** Assign from r. */
        Rational &operator=(const Rational &r);

        /** Get a non-const pointer to the internal lp_rational_t. Handle with care! */
        lp_rational_t *get_internal();
        /** Get a const pointer to the internal lp_rational_t. */
        const lp_rational_t *get_internal() const;
    };

    std::ostream &operator<<(std::ostream &os, const Rational &r);

    double to_double(const Rational &r);

    int sgn(const Rational &r);

    bool operator==(const Rational &lhs, const Rational &rhs);
    bool operator!=(const Rational &lhs, const Rational &rhs);
    bool operator<(const Rational &lhs, const Rational &rhs);
    bool operator<=(const Rational &lhs, const Rational &rhs);
    bool operator>(const Rational &lhs, const Rational &rhs);
    bool operator>=(const Rational &lhs, const Rational &rhs);

    bool operator==(const Rational &lhs, const Integer &rhs);
    bool operator!=(const Rational &lhs, const Integer &rhs);
    bool operator<(const Rational &lhs, const Integer &rhs);
    bool operator<=(const Rational &lhs, const Integer &rhs);
    bool operator>(const Rational &lhs, const Integer &rhs);
    bool operator>=(const Rational &lhs, const Integer &rhs);

    bool operator==(const Integer &lhs, const Rational &rhs);
    bool operator!=(const Integer &lhs, const Rational &rhs);
    bool operator<(const Integer &lhs, const Rational &rhs);
    bool operator<=(const Integer &lhs, const Rational &rhs);
    bool operator>(const Integer &lhs, const Rational &rhs);
    bool operator>=(const Integer &lhs, const Rational &rhs);

    void swap(Rational &lhs, Rational &rhs);

    Rational operator+(const Rational &lhs, const Rational &rhs);
    Rational operator+(const Rational &lhs, const Integer &rhs);
    Rational operator+(const Integer &lhs, const Rational &rhs);

    Rational operator-(const Rational &lhs, const Rational &rhs);
    Rational operator-(const Rational &r);

    Rational inverse(const Rational &r);

    Rational operator*(const Rational &lhs, const Rational &rhs);

    Rational mul_2exp(const Rational &lhs, unsigned n);

    Rational pow(const Rational &r, unsigned n);

    Rational operator/(const Rational &lhs, const Rational &rhs);

    Rational div_2exp(const Rational &lhs, unsigned n);

    Integer numerator(const Rational &r);
    Integer denominator(const Rational &r);

    bool is_integer(const Rational &r);

    Integer ceil(const Rational &r);
    Integer floor(const Rational &r);

} // namespace poly
