#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <polyxx.h>

using namespace poly;

TEST_CASE("integer::constructors") {
    Integer i;
    CHECK(i == Integer(0l));
}

TEST_CASE("integer::bit_size") {
    CHECK(bit_size(Integer(5)) == 3);
    CHECK(bit_size(Integer(64)) == 7);
}

TEST_CASE("integer::gcd") {
    Integer a(15);
    Integer b(125);
    CHECK(gcd(a, b) == Integer(5));
}