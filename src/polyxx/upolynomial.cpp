#include "polyxx/upolynomial.h"

#include "upolynomial_factors.h"

namespace poly {

  /** A deleter for an std::unique_ptr holding a lp_upolynomial_t pointer */
  inline void upolynomial_deleter(lp_upolynomial_t* ptr) {
    lp_upolynomial_delete(ptr);
  }

  UPolynomial::UPolynomial(lp_upolynomial_t* poly)
      : mPoly(poly, upolynomial_deleter) {}
  UPolynomial::UPolynomial(const UPolynomial& poly)
      : mPoly(lp_upolynomial_construct_copy(poly.get_internal()),
              upolynomial_deleter) {}

  UPolynomial::UPolynomial()
      : mPoly(lp_upolynomial_construct_power(lp_Z, 0, 0), upolynomial_deleter) {
  }
  UPolynomial::UPolynomial(const Integer& i)
      : mPoly(lp_upolynomial_construct(lp_Z, 0, i.get_internal()),
              upolynomial_deleter) {}
  UPolynomial::UPolynomial(long i)
      : mPoly(lp_upolynomial_construct_power(lp_Z, 0, i), upolynomial_deleter) {
  }

  UPolynomial::UPolynomial(const std::vector<Integer>& coefficients)
      : UPolynomial(IntegerRing::Z, coefficients) {}
  UPolynomial::UPolynomial(IntegerRing& ir,
                           const std::vector<Integer>& coefficients)
      : mPoly(
            lp_upolynomial_construct(ir.get_internal(), coefficients.size() - 1,
                                     detail::cast_to(coefficients.data())),
            upolynomial_deleter) {}
  UPolynomial::UPolynomial(const std::vector<long>& coefficients)
      : UPolynomial(IntegerRing::Z, coefficients) {}
  UPolynomial::UPolynomial(IntegerRing& ir,
                           const std::vector<long>& coefficients)
      : mPoly(lp_upolynomial_construct_from_long(ir.get_internal(),
                                                 coefficients.size() - 1,
                                                 coefficients.data()),
              upolynomial_deleter) {}

  UPolynomial::UPolynomial(std::initializer_list<long> coefficients)
      : UPolynomial(std::vector<long>(coefficients)) {}
  UPolynomial::UPolynomial(IntegerRing& ir,
                           std::initializer_list<long> coefficients)
      : UPolynomial(ir, std::vector<long>(coefficients)) {}

  /** Get a non-const pointer to the internal lp_upolynomial_t. Handle with
   * care!
   */
  lp_upolynomial_t* UPolynomial::get_internal() { return mPoly.get(); }
  /** Get a const pointer to the internal lp_upolynomial_t. */
  const lp_upolynomial_t* UPolynomial::get_internal() const {
    return mPoly.get();
  }
  /** Release the lp_upolynomial_t pointer. This yields ownership of the
   * returned pointer. */
  lp_upolynomial_t* UPolynomial::release() { return mPoly.release(); }

  std::size_t degree(const UPolynomial& p) {
    return lp_upolynomial_degree(p.get_internal());
  }

  const Integer& leading_coefficient(const UPolynomial& p) {
    return *detail::cast_from(lp_upolynomial_lead_coeff(p.get_internal()));
  }
  const Integer& constant_coefficient(const UPolynomial& p) {
    return *detail::cast_from(lp_upolynomial_const_term(p.get_internal()));
  }

  std::vector<Integer> coefficients(const UPolynomial& p) {
    lp_integer_t coeffs[degree(p) + 1];
    for (std::size_t i = 0; i < degree(p) + 1; ++i) {
      lp_integer_construct_from_int(lp_Z, &coeffs[i], 0);
    }
    lp_upolynomial_unpack(p.get_internal(), coeffs);
    std::vector<Integer> res;
    for (std::size_t i = 0; i < degree(p) + 1; ++i) {
      res.emplace_back(&coeffs[i]);
      lp_integer_destruct(&coeffs[i]);
    }
    return res;
  }

  std::ostream& operator<<(std::ostream& os, const UPolynomial& p) {
    return os << lp_upolynomial_to_string(p.get_internal());
  }

  bool is_zero(const UPolynomial& p) {
    return lp_upolynomial_is_zero(p.get_internal());
  }
  bool is_one(const UPolynomial& p) {
    return lp_upolynomial_is_one(p.get_internal());
  }
  bool is_monic(const UPolynomial& p) {
    return lp_upolynomial_is_monic(p.get_internal());
  }
  bool is_primitive(const UPolynomial& p) {
    return lp_upolynomial_is_primitive(p.get_internal());
  }

  UPolynomial operator+(const UPolynomial& lhs, const UPolynomial& rhs) {
    return UPolynomial(
        lp_upolynomial_add(lhs.get_internal(), rhs.get_internal()));
  }
  UPolynomial operator-(const UPolynomial& lhs, const UPolynomial& rhs) {
    return UPolynomial(
        lp_upolynomial_sub(lhs.get_internal(), rhs.get_internal()));
  }
  UPolynomial operator*(const UPolynomial& lhs, const UPolynomial& rhs) {
    return UPolynomial(
        lp_upolynomial_mul(lhs.get_internal(), rhs.get_internal()));
  }

  std::vector<UPolynomial> square_free_factors(const UPolynomial& p,
                                               bool with_constant) {
    auto factors = lp_upolynomial_factor_square_free(p.get_internal());
    std::vector<UPolynomial> res;

    if (with_constant) {
      res.emplace_back(std::vector<Integer>(
          {Integer(lp_upolynomial_factors_get_constant(factors))}));
    }

    for (std::size_t i = 0; i < lp_upolynomial_factors_size(factors); ++i) {
      std::size_t multiplicity = 0;
      res.emplace_back(
          lp_upolynomial_factors_get_factor(factors, i, &multiplicity));
    }

    lp_upolynomial_factors_destruct(factors, 0);
    return res;
  }

}  // namespace poly
