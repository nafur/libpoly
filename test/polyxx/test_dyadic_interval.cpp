#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <polyxx.h>

using namespace poly;

TEST_CASE("dyadic_interval::constructors") {
    DyadicInterval di(Integer(1), Integer(2));
}
