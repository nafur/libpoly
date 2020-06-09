#pragma once

#include "integer.h"
#include "rational.h"

#include "../dyadic_rational.h"

#include <iosfwd>

namespace poly
{

    class DyadicRational
    {

        lp_dyadic_rational_t mDRat;

    public:
        /** Construct as zero. */
        DyadicRational();
        /** Construct as copy of dr. */
        DyadicRational(const DyadicRational &dr);

        /** Construct as a * 2^n. */
        DyadicRational(long a, unsigned long n);
        /** Construct as a. */
        DyadicRational(const Integer &i);
        /** Construct as d. */
        DyadicRational(double d);

        ~DyadicRational();

        /** Assign from dr. */
        DyadicRational &operator=(const DyadicRational &dr);

        operator Rational() const;

        /** Get a non-const pointer to the internal lp_dyadic_rational_t. Handle with care! */
        lp_dyadic_rational_t *get_internal();
        /** Get a const pointer to the internal lp_dyadic_rational_t. */
        const lp_dyadic_rational_t *get_internal() const;
    };

    std::ostream &operator<<(std::ostream &os, const DyadicRational &dr);

    double to_double(const DyadicRational &dr);

    int sgn(const DyadicRational &dr);

    bool operator==(const DyadicRational &lhs, const DyadicRational &rhs);
    bool operator!=(const DyadicRational &lhs, const DyadicRational &rhs);
    bool operator<(const DyadicRational &lhs, const DyadicRational &rhs);
    bool operator<=(const DyadicRational &lhs, const DyadicRational &rhs);
    bool operator>(const DyadicRational &lhs, const DyadicRational &rhs);
    bool operator>=(const DyadicRational &lhs, const DyadicRational &rhs);

    bool operator==(const DyadicRational &lhs, const Integer &rhs);
    bool operator!=(const DyadicRational &lhs, const Integer &rhs);
    bool operator<(const DyadicRational &lhs, const Integer &rhs);
    bool operator<=(const DyadicRational &lhs, const Integer &rhs);
    bool operator>(const DyadicRational &lhs, const Integer &rhs);
    bool operator>=(const DyadicRational &lhs, const Integer &rhs);

    bool operator==(const Integer &lhs, const DyadicRational &rhs);
    bool operator!=(const Integer &lhs, const DyadicRational &rhs);
    bool operator<(const Integer &lhs, const DyadicRational &rhs);
    bool operator<=(const Integer &lhs, const DyadicRational &rhs);
    bool operator>(const Integer &lhs, const DyadicRational &rhs);
    bool operator>=(const Integer &lhs, const DyadicRational &rhs);

/* See https://github.com/SRI-CSL/libpoly/issues/22
    bool operator==(const DyadicRational &lhs, const Rational &rhs);
    bool operator!=(const DyadicRational &lhs, const Rational &rhs);
    bool operator<(const DyadicRational &lhs, const Rational &rhs);
    bool operator<=(const DyadicRational &lhs, const Rational &rhs);
    bool operator>(const DyadicRational &lhs, const Rational &rhs);
    bool operator>=(const DyadicRational &lhs, const Rational &rhs);

    bool operator==(const Rational &lhs, const DyadicRational &rhs);
    bool operator!=(const Rational &lhs, const DyadicRational &rhs);
    bool operator<(const Rational &lhs, const DyadicRational &rhs);
    bool operator<=(const Rational &lhs, const DyadicRational &rhs);
    bool operator>(const Rational &lhs, const DyadicRational &rhs);
    bool operator>=(const Rational &lhs, const DyadicRational &rhs);
*/
    void swap(DyadicRational &lhs, DyadicRational &rhs);

    DyadicRational operator+(const DyadicRational &lhs, const DyadicRational &rhs);
    DyadicRational operator+(const DyadicRational &lhs, const Integer &rhs);
    DyadicRational operator+(const Integer &lhs, const DyadicRational &rhs);

    DyadicRational operator-(const DyadicRational &lhs, const DyadicRational &rhs);

    DyadicRational operator-(const DyadicRational &dr);

    DyadicRational operator*(const DyadicRational &lhs, const DyadicRational &rhs);

    DyadicRational mul_2exp(const DyadicRational &lhs, unsigned long n);
    DyadicRational pow(const DyadicRational &lhs, unsigned long n);
    DyadicRational div_2exp(const DyadicRational &lhs, unsigned long n);

    Integer numerator(const DyadicRational &r);
    Integer denominator(const DyadicRational &r);

    bool is_integer(const DyadicRational &r);

    Integer ceil(const DyadicRational &r);
    Integer floor(const DyadicRational &r);
} // namespace poly
