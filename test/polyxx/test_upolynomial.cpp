#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <polyxx.h>

TEST_CASE("upolynomial::constructors") {
    poly::UPolynomial p({-2,0,1});
}