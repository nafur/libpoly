#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <polyxx.h>

using namespace poly;

TEST_CASE("algebraic_number::constructors") {
    int coeffs[] = {-2,0,1};
    UPolynomial p(2, coeffs);
    AlgebraicNumber an(p, DyadicInterval(Integer(1), Integer(2)));
}