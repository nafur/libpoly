#include "root_isolation.h"

namespace CVC4 {
namespace theory {
namespace arith {
namespace nl {
namespace libpoly {

std::vector<RAN> isolate_real_roots(const UPolynomial& p)
{
  lp_algebraic_number_t* roots = new lp_algebraic_number_t[degree(p)];
  std::size_t roots_size;
  lp_upolynomial_roots_isolate(p.get(), roots, &roots_size);
  std::vector<RAN> res;
  for (std::size_t i = 0; i < roots_size; ++i)
  {
    res.emplace_back(roots[i]);
  }
  for (std::size_t i = 0; i < roots_size; ++i)
  {
    lp_algebraic_number_destruct(&roots[i]);
  }
  delete[] roots;
  return res;
}

}  // namespace libpoly
}  // namespace nl
}  // namespace arith
}  // namespace theory
}  // namespace CVC4
