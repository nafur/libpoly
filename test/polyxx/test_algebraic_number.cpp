#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <polyxx.h>

using namespace poly;

TEST_CASE("algebraic_number::constructors") {
    UPolynomial p({-2,0,1});
    AlgebraicNumber an(p, DyadicInterval(1, 2));
}