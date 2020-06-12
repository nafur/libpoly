#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <polyxx.h>

#include "doctest.h"

using namespace poly;

TEST_CASE("dyadic_interval::constructors") {
  CHECK(DyadicInterval() == DyadicInterval(Integer(0)));
  CHECK(DyadicInterval(DyadicRational(1), DyadicRational(2)) ==
        DyadicInterval(1, true, 2, true));
  CHECK(DyadicInterval(Integer(1), Integer(2)) ==
        DyadicInterval(1, true, 2, true));
  CHECK(DyadicInterval(1, 2) == DyadicInterval(1, true, 2, true));
}

TEST_CASE("dyadic_interval::collapse") {
  DyadicInterval di(1, 2);
  di.collapse(17);
  CHECK(di == Integer(17));
}

TEST_CASE("dyadic_interval::set_lower") {
  DyadicInterval di(1, 2);
  di.set_lower(0, false);
  CHECK(di == DyadicInterval(0, false, 2, true));
}

TEST_CASE("dyadic_interval::set_upper") {
  DyadicInterval di(1, 2);
  di.set_upper(3, false);
  CHECK(di == DyadicInterval(1, true, 3, false));
}

TEST_CASE("dyadic_interval::scale") {
  {
    DyadicInterval di(-1, 1);
    di.scale(-2);
    // See https://github.com/SRI-CSL/libpoly/pull/26
    // CHECK(di == DyadicInterval(DyadicRational(-1,2), DyadicRational(1,2)));
  }
  {
    DyadicInterval di(-1, 1);
    di.scale(2);
    CHECK(di == DyadicInterval(-4, 4));
  }
}

TEST_CASE("dyadic_interval::split") {
  DyadicInterval di(Integer(0), Integer(10));
  auto s = split(di, true, true);
  CHECK(get_lower(di) == get_lower(s.first));
  CHECK(get_upper(s.first) == get_lower(s.second));
  CHECK(get_upper(di) == get_upper(s.second));
  CHECK(disjoint(s.first, s.second));
}

TEST_CASE("dyadic_interval::swap") {
  DyadicInterval a(Integer(1), Integer(2));
  DyadicInterval b(Integer(3), Integer(4));
  swap(a, b);
  CHECK(a == DyadicInterval(Integer(3), Integer(4)));
  CHECK(b == DyadicInterval(Integer(1), Integer(2)));
}

TEST_CASE("dyadic_interval::operator== / operator!=") {
  DyadicInterval a(1, 2);
  DyadicInterval b(DyadicRational(1), DyadicRational(2));
  DyadicInterval c(Integer(3), Integer(4));
  CHECK(a == a);
  CHECK_FALSE(a != a);
  CHECK(a == b);
  CHECK_FALSE(a != b);
  CHECK_FALSE(a == c);
  CHECK(a != c);
  CHECK(b == a);
  CHECK_FALSE(b != a);
  CHECK(b == b);
  CHECK_FALSE(b != b);
  CHECK_FALSE(b == c);
  CHECK(b != c);
  CHECK_FALSE(c == a);
  CHECK(c != a);
  CHECK_FALSE(c == b);
  CHECK(c != b);
  CHECK(c == c);
  CHECK_FALSE(c != c);
}

TEST_CASE("dyadic_interval::contains") {
  CHECK_FALSE(contains(DyadicInterval(1,3), DyadicRational(0)));
  CHECK_FALSE(contains(DyadicInterval(1,3), DyadicRational(1)));
  CHECK(contains(DyadicInterval(1,3), DyadicRational(2)));
  CHECK_FALSE(contains(DyadicInterval(1,3), DyadicRational(3)));
  CHECK_FALSE(contains(DyadicInterval(1,3), DyadicRational(4)));
}
