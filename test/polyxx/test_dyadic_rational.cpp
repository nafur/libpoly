#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <polyxx.h>

using namespace poly;

TEST_CASE("dyadic_rational::constructors")
{
    CHECK(DyadicRational() == DyadicRational());
    CHECK(DyadicRational() == DyadicRational(0, 1));
}

TEST_CASE("dyadic_rational::to_double")
{
    CHECK(to_double(DyadicRational(0)) == 0.0);
    CHECK(to_double(DyadicRational(1)) == 1.0);
}

TEST_CASE("dyadic_rational::sgn")
{
    CHECK(sgn(DyadicRational(-10)) == -1);
    CHECK(sgn(DyadicRational(-1)) == -1);
    CHECK(sgn(DyadicRational(0)) == 0);
    CHECK(sgn(DyadicRational(1)) == 1);
    CHECK(sgn(DyadicRational(10)) == 1);
}

TEST_CASE("dyadic_rational::operator==")
{
    CHECK_FALSE(DyadicRational(1) == DyadicRational(2));
    CHECK_FALSE(DyadicRational(1) == Integer(2));
    CHECK_FALSE(Integer(1) == DyadicRational(2));
    CHECK(DyadicRational(1) == DyadicRational(1));
    CHECK(DyadicRational(1) == Integer(1));
    CHECK(Integer(1) == DyadicRational(1));
    CHECK_FALSE(DyadicRational(2) == DyadicRational(1));
    CHECK_FALSE(DyadicRational(2) == Integer(1));
    CHECK_FALSE(Integer(2) == DyadicRational(1));
}

TEST_CASE("dyadic_rational::operator!=")
{
    CHECK(DyadicRational(1) != DyadicRational(2));
    CHECK(DyadicRational(1) != Integer(2));
    CHECK(Integer(1) != DyadicRational(2));
    CHECK_FALSE(DyadicRational(1) != DyadicRational(1));
    CHECK_FALSE(DyadicRational(1) != Integer(1));
    CHECK_FALSE(Integer(1) != DyadicRational(1));
    CHECK(DyadicRational(2) != DyadicRational(1));
    CHECK(DyadicRational(2) != Integer(1));
    CHECK(Integer(2) != DyadicRational(1));
}

TEST_CASE("dyadic_rational::operator<")
{
    CHECK(DyadicRational(1) < DyadicRational(2));
    CHECK(DyadicRational(1) < Integer(2));
    CHECK(Integer(1) < DyadicRational(2));
    CHECK_FALSE(DyadicRational(1) < DyadicRational(1));
    CHECK_FALSE(DyadicRational(1) < Integer(1));
    CHECK_FALSE(Integer(1) < DyadicRational(1));
    CHECK_FALSE(DyadicRational(2) < DyadicRational(1));
    CHECK_FALSE(DyadicRational(2) < Integer(1));
    CHECK_FALSE(Integer(2) < DyadicRational(1));
}

TEST_CASE("dyadic_rational::operator<=")
{
    CHECK(DyadicRational(1) <= DyadicRational(2));
    CHECK(DyadicRational(1) <= Integer(2));
    CHECK(Integer(1) <= DyadicRational(2));
    CHECK(DyadicRational(1) <= DyadicRational(1));
    CHECK(DyadicRational(1) <= Integer(1));
    CHECK(Integer(1) <= DyadicRational(1));
    CHECK_FALSE(DyadicRational(2) <= DyadicRational(1));
    CHECK_FALSE(DyadicRational(2) <= Integer(1));
    CHECK_FALSE(Integer(2) <= DyadicRational(1));
}

TEST_CASE("dyadic_rational::operator>")
{
    CHECK_FALSE(DyadicRational(1) > DyadicRational(2));
    CHECK_FALSE(DyadicRational(1) > Integer(2));
    CHECK_FALSE(Integer(1) > DyadicRational(2));
    CHECK_FALSE(DyadicRational(1) > DyadicRational(1));
    CHECK_FALSE(DyadicRational(1) > Integer(1));
    CHECK_FALSE(Integer(1) > DyadicRational(1));
    CHECK(DyadicRational(2) > DyadicRational(1));
    CHECK(DyadicRational(2) > Integer(1));
    CHECK(Integer(2) > DyadicRational(1));
}

TEST_CASE("dyadic_rational::operator>=")
{
    CHECK_FALSE(DyadicRational(1) >= DyadicRational(2));
    CHECK_FALSE(DyadicRational(1) >= Integer(2));
    CHECK_FALSE(Integer(1) >= DyadicRational(2));
    CHECK(DyadicRational(1) >= DyadicRational(1));
    CHECK(DyadicRational(1) >= Integer(1));
    CHECK(Integer(1) >= DyadicRational(1));
    CHECK(DyadicRational(2) >= DyadicRational(1));
    CHECK(DyadicRational(2) >= Integer(1));
    CHECK(Integer(2) >= DyadicRational(1));
}

TEST_CASE("dyadic_rational::swap")
{
    DyadicRational a(1);
    DyadicRational b(2);
    swap(a, b);
    CHECK(a == DyadicRational(2));
    CHECK(b == DyadicRational(1));
}

TEST_CASE("dyadic_rational::operator+")
{
    CHECK(DyadicRational(1) + DyadicRational(2) == DyadicRational(3));
    CHECK(DyadicRational(1) + Integer(2) == DyadicRational(3));
    CHECK(Integer(1) + DyadicRational(2) == DyadicRational(3));
}
TEST_CASE("dyadic_rational::operator-")
{
    CHECK(DyadicRational(1) - DyadicRational(2) == DyadicRational(-1));
    CHECK(-DyadicRational(1) == DyadicRational(-1));
}

TEST_CASE("dyadic_rational::operator*")
{
    CHECK(DyadicRational(1) * DyadicRational(2) == DyadicRational(2));
}
TEST_CASE("dyadic_rational::mul_2exp")
{
    CHECK(mul_2exp(DyadicRational(2), 2) == DyadicRational(8));
}
TEST_CASE("dyadic_rational::pow")
{
    CHECK(pow(DyadicRational(2), 3) == DyadicRational(8));
}

TEST_CASE("dyadic_rational::div_2exp")
{
    CHECK(div_2exp(DyadicRational(2), 1) == DyadicRational(Integer(1)));
}

TEST_CASE("dyadic_rational::numerator")
{
    CHECK(numerator(DyadicRational(1)) == DyadicRational(1));
    CHECK(numerator(DyadicRational(2)) == DyadicRational(2));
}
TEST_CASE("dyadic_rational::denominator")
{
    CHECK(denominator(DyadicRational(1)) == DyadicRational(1));
    CHECK(denominator(DyadicRational(2)) == DyadicRational(1));
}

TEST_CASE("dyadic_rational::is_integer")
{
    CHECK(is_integer(DyadicRational(1)));
    CHECK(is_integer(DyadicRational(2)));
}

TEST_CASE("dyadic_rational::ceil")
{
    CHECK(ceil(DyadicRational(1)) == DyadicRational(1));
}
TEST_CASE("dyadic_rational::floor")
{
    CHECK(floor(DyadicRational(1)) == DyadicRational(1));
}
