#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <polyxx.h>

TEST_CASE("algebraic_number::constructors") {
    int coeffs[] = {-2,0,1};
    poly::UPolynomial p(2, coeffs);
    poly::AlgebraicNumber an(p, poly::DyadicInterval(1,2));
}