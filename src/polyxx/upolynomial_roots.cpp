#include "polyxx/upolynomial_roots.h"

namespace poly {

std::vector<AlgebraicNumber> isolate_real_roots(const UPolynomial& p)
{
  lp_algebraic_number_t* roots = new lp_algebraic_number_t[degree(p)];
  std::size_t roots_size;
  lp_upolynomial_roots_isolate(p.get_internal(), roots, &roots_size);
  std::vector<AlgebraicNumber> res;
  for (std::size_t i = 0; i < roots_size; ++i)
  {
    res.emplace_back(&roots[i]);
  }
  for (std::size_t i = 0; i < roots_size; ++i)
  {
    lp_algebraic_number_destruct(&roots[i]);
  }
  delete[] roots;
  return res;
}

}  // namespace poly
