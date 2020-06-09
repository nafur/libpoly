#pragma once

#include "integer.h"
#include "rational.h"

#include "../dyadic_rational.h"

#include <iosfwd>

namespace poly {

class DyadicRational {

    lp_dyadic_rational_t mRat;

    public:
    /** Construct as zero. */
    DyadicRational();
    /** Construct as copy of dr. */
    DyadicRational(const DyadicRational& dr);

    /** Construct as a * 2^n. */
    DyadicRational(long a, unsigned long n);
    /** Construct as a. */
    DyadicRational(const Integer& i);
    /** Construct as d. */
    DyadicRational(double d);

    ~DyadicRational();


    /** Assign from dr. */
    DyadicRational& operator=(const DyadicRational& dr);

    operator Rational() const;

  /** Get a non-const pointer to the internal lp_dyadic_rational_t. Handle with care! */
  lp_dyadic_rational_t* get_internal();
  /** Get a const pointer to the internal lp_dyadic_rational_t. */
  const lp_dyadic_rational_t* get_internal() const;
};

std::ostream& operator<<(std::ostream& os, const DyadicRational& dr);

double to_double(const DyadicRational& dr);

int sgn(const DyadicRational& dr);



bool operator==(const DyadicRational& lhs, const DyadicRational& rhs);
bool operator!=(const DyadicRational& lhs, const DyadicRational& rhs);
bool operator<(const DyadicRational& lhs, const DyadicRational& rhs);
bool operator<=(const DyadicRational& lhs, const DyadicRational& rhs);
bool operator>(const DyadicRational& lhs, const DyadicRational& rhs);
bool operator>=(const DyadicRational& lhs, const DyadicRational& rhs);


}
