#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <polyxx.h>

TEST_CASE("integer::constructors") {
    poly::Integer i;
    CHECK(i == poly::Integer(0));
}

TEST_CASE("integer::gcd") {
    poly::Integer a(15);
    poly::Integer b(125);
    CHECK(gcd(a, b) == poly::Integer(5));
}