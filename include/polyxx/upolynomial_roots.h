#pragma once

#include "algebraic_number.h"
#include "rational_interval.h"
#include "upolynomial.h"

namespace poly {

std::size_t count_real_roots(const UPolynomial& p, const RationalInterval& ri);

/** Isolate the real roots of a UPolynomial. */
std::vector<AlgebraicNumber> isolate_real_roots(const UPolynomial& p);

}  // namespace poly

