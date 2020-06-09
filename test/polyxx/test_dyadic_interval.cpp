#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <polyxx.h>

TEST_CASE("dyadic_interval::constructors") {
    poly::DyadicInterval di(1,2);
}
