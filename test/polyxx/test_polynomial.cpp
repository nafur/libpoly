#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <polyxx.h>

#include "doctest.h"

using namespace poly;

TEST_CASE("polynomial::psc") {
  Variable y("y");
  Variable x("x");
  Polynomial p = 7*pow(x, 6) + 14*pow(x, 5) + 7*y - 1;
  Polynomial q = 42*pow(x, 5) + 70*pow(x, 4);
  auto tmp = psc(p, q);

  CHECK(tmp.size() == 6);
  CHECK(tmp[0] == 92254156521408*pow(y,5) - 461361174686720*pow(y,4) + 244807578081920*pow(y,3) - 51113953954560*pow(y,2) + 4803956911040*y - 170197631744);
  CHECK(tmp[1] == 174327582240*y*y*y-74711820960*y*y+10673117280*y-508243680);
  CHECK(tmp[2] == Integer(0));
  CHECK(tmp[3] == Integer(0));
  CHECK(tmp[4] == Integer(-6860));
  CHECK(tmp[5] == Integer(42));
}