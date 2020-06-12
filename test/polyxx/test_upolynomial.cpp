#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <polyxx.h>

#include "doctest.h"

using namespace poly;

TEST_CASE("upolynomial::degree") { 
    CHECK(degree(UPolynomial()) == 0);
    CHECK(degree(UPolynomial({1})) == 0);
    CHECK(degree(UPolynomial({1, 1})) == 1);
    CHECK(degree(UPolynomial({-2, 0, 1})) == 2);
}

TEST_CASE("upolynomial::leading_coefficient") { 
    CHECK(leading_coefficient(UPolynomial()) == Integer(0));
    CHECK(leading_coefficient(UPolynomial({1})) == Integer(1));
    CHECK(leading_coefficient(UPolynomial({1, 2})) == Integer(2));
    CHECK(leading_coefficient(UPolynomial({-2, 0, 3})) == Integer(3));
}

TEST_CASE("upolynomial::constant_coefficient") { 
    CHECK(constant_coefficient(UPolynomial()) == Integer(0));
    CHECK(constant_coefficient(UPolynomial({1})) == Integer(1));
    CHECK(constant_coefficient(UPolynomial({2, 2})) == Integer(2));
    CHECK(constant_coefficient(UPolynomial({2, 0, 3})) == Integer(2));
}

TEST_CASE("upolynomial::constant_coefficient") { 
    CHECK(coefficients(UPolynomial()) == std::vector<Integer>({Integer(0)}));
    CHECK(coefficients(UPolynomial({1})) == std::vector<Integer>({Integer(1)}));
    CHECK(coefficients(UPolynomial({2, 2})) == std::vector<Integer>({Integer(2),Integer(2)}));
    CHECK(coefficients(UPolynomial({2, 0, 3})) == std::vector<Integer>({Integer(2),Integer(),Integer(3)}));
}

TEST_CASE("upolynomial::is_zero") { 
    CHECK(is_zero(UPolynomial()));
    CHECK_FALSE(is_zero(UPolynomial({-1})));
    CHECK(is_zero(UPolynomial({0})));
    CHECK_FALSE(is_zero(UPolynomial({1})));
    CHECK_FALSE(is_zero(UPolynomial({2, 2})));
    CHECK_FALSE(is_zero(UPolynomial({0, 2})));
}

TEST_CASE("upolynomial::is_one") { 
    CHECK_FALSE(is_one(UPolynomial()));
    CHECK_FALSE(is_one(UPolynomial({-1})));
    CHECK_FALSE(is_one(UPolynomial({0})));
    CHECK(is_one(UPolynomial({1})));
    CHECK_FALSE(is_one(UPolynomial({2, 2})));
    CHECK_FALSE(is_one(UPolynomial({0, 2})));
}

TEST_CASE("upolynomial::is_monic") { 
    CHECK_FALSE(is_monic(UPolynomial()));
    CHECK_FALSE(is_monic(UPolynomial({-1})));
    CHECK_FALSE(is_monic(UPolynomial({0})));
    CHECK(is_monic(UPolynomial({1})));
    CHECK(is_monic(UPolynomial({0, 1})));
    CHECK_FALSE(is_monic(UPolynomial({0, 2})));
    CHECK(is_monic(UPolynomial({1, 1})));
    CHECK_FALSE(is_monic(UPolynomial({1, 2})));
    CHECK(is_monic(UPolynomial({2, 1})));
    CHECK_FALSE(is_monic(UPolynomial({2, 2})));
}

TEST_CASE("upolynomial::is_primitive") { 
    CHECK_FALSE(is_primitive(UPolynomial({-1})));
    CHECK(is_primitive(UPolynomial({1})));
    CHECK(is_primitive(UPolynomial({0, 1})));
    CHECK_FALSE(is_primitive(UPolynomial({0, 2})));
    CHECK(is_primitive(UPolynomial({1, 1})));
    CHECK(is_primitive(UPolynomial({1, 2})));
    CHECK(is_primitive(UPolynomial({2, 1})));
    CHECK_FALSE(is_primitive(UPolynomial({2, 2})));
}
