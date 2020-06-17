#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <polyxx.h>

#include "doctest.h"

using namespace poly;

TEST_CASE("interval::operator==") {
  CHECK_FALSE(Interval(1,2) == Interval(3,6));
  CHECK_FALSE(Interval(1,3) == Interval(3,6));
  CHECK_FALSE(Interval(1,4) == Interval(3,6));
  CHECK_FALSE(Interval(1,6) == Interval(3,6));
  CHECK_FALSE(Interval(1,8) == Interval(3,6));
  CHECK_FALSE(Interval(3,5) == Interval(3,6));
  CHECK(Interval(3,6) == Interval(3,6));
  CHECK_FALSE(Interval(3,8) == Interval(3,6));
  CHECK_FALSE(Interval(4,5) == Interval(3,6));
  CHECK_FALSE(Interval(4,6) == Interval(3,6));
  CHECK_FALSE(Interval(4,8) == Interval(3,6));
  CHECK_FALSE(Interval(6,8) == Interval(3,6));
  CHECK_FALSE(Interval(7,8) == Interval(3,6));
}

TEST_CASE("interval::operator!=") {
  CHECK(Interval(1,2) != Interval(3,6));
  CHECK(Interval(1,3) != Interval(3,6));
  CHECK(Interval(1,4) != Interval(3,6));
  CHECK(Interval(1,6) != Interval(3,6));
  CHECK(Interval(1,8) != Interval(3,6));
  CHECK(Interval(3,5) != Interval(3,6));
  CHECK_FALSE(Interval(3,6) != Interval(3,6));
  CHECK(Interval(3,8) != Interval(3,6));
  CHECK(Interval(4,5) != Interval(3,6));
  CHECK(Interval(4,6) != Interval(3,6));
  CHECK(Interval(4,8) != Interval(3,6));
  CHECK(Interval(6,8) != Interval(3,6));
  CHECK(Interval(7,8) != Interval(3,6));
}

TEST_CASE("interval::operator<") {
  CHECK(Interval(1,2) < Interval(3,6));
  CHECK(Interval(1,3) < Interval(3,6));
  CHECK(Interval(1,4) < Interval(3,6));
  CHECK(Interval(1,6) < Interval(3,6));
  CHECK(Interval(1,8) < Interval(3,6));
  CHECK(Interval(3,5) < Interval(3,6));
  CHECK_FALSE(Interval(3,6) < Interval(3,6));
  CHECK_FALSE(Interval(3,8) < Interval(3,6));
  CHECK_FALSE(Interval(4,5) < Interval(3,6));
  CHECK_FALSE(Interval(4,6) < Interval(3,6));
  CHECK_FALSE(Interval(4,8) < Interval(3,6));
  CHECK_FALSE(Interval(6,8) < Interval(3,6));
  CHECK_FALSE(Interval(7,8) < Interval(3,6));
}

TEST_CASE("interval::operator<=") {
  CHECK(Interval(1,2) <= Interval(3,6));
  CHECK(Interval(1,3) <= Interval(3,6));
  CHECK(Interval(1,4) <= Interval(3,6));
  CHECK(Interval(1,6) <= Interval(3,6));
  CHECK(Interval(1,8) <= Interval(3,6));
  CHECK(Interval(3,5) <= Interval(3,6));
  CHECK(Interval(3,6) <= Interval(3,6));
  CHECK_FALSE(Interval(3,8) <= Interval(3,6));
  CHECK_FALSE(Interval(4,5) <= Interval(3,6));
  CHECK_FALSE(Interval(4,6) <= Interval(3,6));
  CHECK_FALSE(Interval(4,8) <= Interval(3,6));
  CHECK_FALSE(Interval(6,8) <= Interval(3,6));
  CHECK_FALSE(Interval(7,8) <= Interval(3,6));
}

TEST_CASE("interval::operator>") {
  CHECK_FALSE(Interval(1,2) > Interval(3,6));
  CHECK_FALSE(Interval(1,3) > Interval(3,6));
  CHECK_FALSE(Interval(1,4) > Interval(3,6));
  CHECK_FALSE(Interval(1,6) > Interval(3,6));
  CHECK_FALSE(Interval(1,8) > Interval(3,6));
  CHECK_FALSE(Interval(3,5) > Interval(3,6));
  CHECK_FALSE(Interval(3,6) > Interval(3,6));
  CHECK(Interval(3,8) > Interval(3,6));
  CHECK(Interval(4,5) > Interval(3,6));
  CHECK(Interval(4,6) > Interval(3,6));
  CHECK(Interval(4,8) > Interval(3,6));
  CHECK(Interval(6,8) > Interval(3,6));
  CHECK(Interval(7,8) > Interval(3,6));
}

TEST_CASE("interval::operator>=") {
  CHECK_FALSE(Interval(1,2) >= Interval(3,6));
  CHECK_FALSE(Interval(1,3) >= Interval(3,6));
  CHECK_FALSE(Interval(1,4) >= Interval(3,6));
  CHECK_FALSE(Interval(1,6) >= Interval(3,6));
  CHECK_FALSE(Interval(1,8) >= Interval(3,6));
  CHECK_FALSE(Interval(3,5) >= Interval(3,6));
  CHECK(Interval(3,6) >= Interval(3,6));
  CHECK(Interval(3,8) >= Interval(3,6));
  CHECK(Interval(4,5) >= Interval(3,6));
  CHECK(Interval(4,6) >= Interval(3,6));
  CHECK(Interval(4,8) >= Interval(3,6));
  CHECK(Interval(6,8) >= Interval(3,6));
  CHECK(Interval(7,8) >= Interval(3,6));
}
