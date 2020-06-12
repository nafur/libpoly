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

TEST_CASE("upolynomial::evaluate_at") {
    UPolynomial p({1, 1, 1});
    CHECK(evaluate_at(p, Integer(-1)) == Integer(1));
    CHECK(evaluate_at(p, Integer()) == Integer(1));
    CHECK(evaluate_at(p, Integer(1)) == Integer(3));
    CHECK(evaluate_at(p, Integer(2)) == Integer(7));

    CHECK(evaluate_at(p, Rational(-1, 2)) == Rational(3, 4));
    CHECK(evaluate_at(p, Rational()) == Rational(1));
    CHECK(evaluate_at(p, Rational(1, 3)) == Rational(13, 9));
    CHECK(evaluate_at(p, Rational(2, 3)) == Rational(19, 9));

    CHECK(evaluate_at(p, DyadicRational(-1, 1)) == DyadicRational(3, 2));
    CHECK(evaluate_at(p, DyadicRational()) == DyadicRational(1));
    CHECK(evaluate_at(p, DyadicRational(1, 2)) == DyadicRational(21, 4));
    CHECK(evaluate_at(p, DyadicRational(1, 3)) == DyadicRational(73, 6));
}

TEST_CASE("upolynomial::sign_at") {
    UPolynomial p({2, 1, -1});
    CHECK(sign_at(p, Integer(-2)) == -1);
    CHECK(sign_at(p, Integer(-1)) == 0);
    CHECK(sign_at(p, Integer()) == 1);
    CHECK(sign_at(p, Integer(1)) == 1);
    CHECK(sign_at(p, Integer(2)) == 0);

    CHECK(sign_at(p, Rational(-5, 2)) == -1);
    CHECK(sign_at(p, Rational(-1)) == 0);
    CHECK(sign_at(p, Rational(-1, 2)) == 1);
    CHECK(sign_at(p, Rational(2)) == 0);
    CHECK(sign_at(p, Rational(7, 3)) == -1);

    CHECK(sign_at(p, DyadicRational(-13, 2)) == -1);
    CHECK(sign_at(p, DyadicRational(-8, 3)) == 0);
    CHECK(sign_at(p, DyadicRational(-1, 5)) == 1);
    CHECK(sign_at(p, DyadicRational(8, 2)) == 0);
    CHECK(sign_at(p, DyadicRational(71, 3)) == -1);
}

TEST_CASE("upolynomial::subst_x_neg") {
    CHECK(subst_x_neg(UPolynomial({2, 1, -1})) == UPolynomial({2, -1, -1}));
}

TEST_CASE("upolynomial::operator-") {
    CHECK(-UPolynomial({2, 1, -1}) == UPolynomial({-2, -1, 1}));
}

TEST_CASE("upolynomial::neg") {
    UPolynomial p({2, 1, -1});
    neg(p);
    CHECK(p == UPolynomial({-2, -1, 1}));
}