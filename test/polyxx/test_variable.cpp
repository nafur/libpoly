#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <polyxx.h>

TEST_CASE("testing variable") {
    poly::Context context;

    poly::Variable v1;
    poly::Variable v2("foo");
}