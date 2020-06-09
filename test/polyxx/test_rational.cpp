#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <polyxx.h>

using namespace poly;

TEST_CASE("rational::constructors") {
    CHECK(Rational() == Rational());
    CHECK(Rational() == Rational(0, 1));
}