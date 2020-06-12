#include "polyxx/upolynomial.h"

#include "upolynomial_factors.h"

namespace poly {

  /** A deleter for an std::unique_ptr holding a lp_upolynomial_t pointer */
  inline void upolynomial_deleter(lp_upolynomial_t* ptr) {
    lp_upolynomial_delete(ptr);
  }

  UPolynomial::UPolynomial(lp_upolynomial_t* poly)
      : mPoly(poly, upolynomial_deleter) {}
  UPolynomial::UPolynomial(const lp_upolynomial_t* poly)
      : mPoly(lp_upolynomial_construct_copy(poly), upolynomial_deleter) {}

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

  UPolynomial::UPolynomial(std::size_t degree, long c)
      : UPolynomial(IntegerRing::Z, degree, c) {}

  UPolynomial::UPolynomial(IntegerRing& ir, std::size_t degree, long c)
      : mPoly(lp_upolynomial_construct_power(ir.get_internal(), degree, c),
              upolynomial_deleter) {}

  UPolynomial::UPolynomial(const UPolynomial& poly)
      : mPoly(lp_upolynomial_construct_copy(poly.get_internal()),
              upolynomial_deleter) {}

  UPolynomial::UPolynomial(UPolynomial&& poly)
      : mPoly(poly.release(), upolynomial_deleter) {}

  UPolynomial::UPolynomial(IntegerRing& ir, const UPolynomial& poly)
      : mPoly(lp_upolynomial_construct_copy_K(ir.get_internal(),
                                              poly.get_internal()),
              upolynomial_deleter) {}

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

  Integer evaluate_at(const UPolynomial& p, const Integer& i) {
    Integer res;
    lp_upolynomial_evaluate_at_integer(p.get_internal(), i.get_internal(),
                                       res.get_internal());
    return res;
  }
  Rational evaluate_at(const UPolynomial& p, const Rational& r) {
    Rational res;
    lp_upolynomial_evaluate_at_rational(p.get_internal(), r.get_internal(),
                                        res.get_internal());
    return res;
  }
  DyadicRational evaluate_at(const UPolynomial& p, const DyadicRational& dr) {
    DyadicRational res;
    lp_upolynomial_evaluate_at_dyadic_rational(
        p.get_internal(), dr.get_internal(), res.get_internal());
    return res;
  }

  int sign_at(const UPolynomial& p, const Integer& i) {
    return lp_upolynomial_sgn_at_integer(p.get_internal(), i.get_internal());
  }
  int sign_at(const UPolynomial& p, const Rational& r) {
    return lp_upolynomial_sgn_at_rational(p.get_internal(), r.get_internal());
  }
  int sign_at(const UPolynomial& p, const DyadicRational& dr) {
    return lp_upolynomial_sgn_at_dyadic_rational(p.get_internal(),
                                                 dr.get_internal());
  }

  bool operator==(const UPolynomial& lhs, const UPolynomial& rhs) {
    return lp_upolynomial_cmp(lhs.get_internal(), rhs.get_internal()) == 0;
  }
  bool operator!=(const UPolynomial& lhs, const UPolynomial& rhs) {
    return lp_upolynomial_cmp(lhs.get_internal(), rhs.get_internal()) != 0;
  }
  bool operator<(const UPolynomial& lhs, const UPolynomial& rhs) {
    return lp_upolynomial_cmp(lhs.get_internal(), rhs.get_internal()) < 0;
  }
  bool operator<=(const UPolynomial& lhs, const UPolynomial& rhs) {
    return lp_upolynomial_cmp(lhs.get_internal(), rhs.get_internal()) <= 0;
  }
  bool operator>(const UPolynomial& lhs, const UPolynomial& rhs) {
    return lp_upolynomial_cmp(lhs.get_internal(), rhs.get_internal()) > 0;
  }
  bool operator>=(const UPolynomial& lhs, const UPolynomial& rhs) {
    return lp_upolynomial_cmp(lhs.get_internal(), rhs.get_internal()) >= 0;
  }

  UPolynomial subst_x_neg(const UPolynomial& p) {
    return UPolynomial(lp_upolynomial_subst_x_neg(p.get_internal()));
  }
  UPolynomial operator-(const UPolynomial& p) {
    return UPolynomial(lp_upolynomial_neg(p.get_internal()));
  }
  void neg(UPolynomial& p) { lp_upolynomial_neg_in_place(p.get_internal()); }

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
  UPolynomial operator*(const UPolynomial& lhs, const Integer& rhs) {
    return UPolynomial(
        lp_upolynomial_mul_c(lhs.get_internal(), rhs.get_internal()));
  }
  UPolynomial operator*(const Integer& lhs, const UPolynomial& rhs) {
    return UPolynomial(
        lp_upolynomial_mul_c(rhs.get_internal(), lhs.get_internal()));
  }

  UPolynomial pow(const UPolynomial& lhs, long rhs) {
    return UPolynomial(lp_upolynomial_pow(lhs.get_internal(), rhs));
  }

  UPolynomial derivative(const UPolynomial& p) {
    return UPolynomial(lp_upolynomial_derivative(p.get_internal()));
  }

  bool divides(const UPolynomial& lhs, const UPolynomial& rhs) {
    return lp_upolynomial_divides(lhs.get_internal(), rhs.get_internal());
  }

  UPolynomial div_degrees(const UPolynomial& lhs, long rhs) {
    return UPolynomial(lp_upolynomial_div_degrees(lhs.get_internal(), rhs));
  }

  UPolynomial div_exact(const UPolynomial& lhs, const UPolynomial& rhs) {
    return UPolynomial(
        lp_upolynomial_div_exact(lhs.get_internal(), rhs.get_internal()));
  }
  UPolynomial div_exact(const UPolynomial& lhs, const Integer& rhs) {
    return UPolynomial(
        lp_upolynomial_div_exact_c(lhs.get_internal(), rhs.get_internal()));
  }
  UPolynomial rem_exact(const UPolynomial& lhs, const UPolynomial& rhs) {
    return UPolynomial(
        lp_upolynomial_rem_exact(lhs.get_internal(), rhs.get_internal()));
  }
  std::pair<UPolynomial, UPolynomial> div_rem_exact(const UPolynomial& lhs,
                                                    const UPolynomial& rhs) {
    lp_upolynomial_t* div = nullptr;
    lp_upolynomial_t* rem = nullptr;
    lp_upolynomial_div_rem_exact(lhs.get_internal(), rhs.get_internal(), &div,
                                 &rem);
    return {UPolynomial(div), UPolynomial(rem)};
  }
  std::pair<UPolynomial, UPolynomial> div_rem_pseudo(const UPolynomial& lhs,
                                                     const UPolynomial& rhs) {
    lp_upolynomial_t* div = nullptr;
    lp_upolynomial_t* rem = nullptr;
    lp_upolynomial_div_pseudo(&div, &rem, lhs.get_internal(),
                              rhs.get_internal());
    return {UPolynomial(div), UPolynomial(rem)};
  }

  /** Computes the content of a polynomial.
   * The content is the gcd of all coefficients with the sign of the leading
   * coefficient.
   */
  Integer content(const UPolynomial& p);
  /** Makes a polynomial primitive in place.
   * A polynomial is primitive if its content is one.
   */
  void make_primitive(UPolynomial& p);
  /** Computes the primitive part, that is p / content(p). */
  UPolynomial primitive_part(const UPolynomial& p);

  /** Compute the greatest common divisor. */
  UPolynomial gcd(const UPolynomial& lhs, const UPolynomial& rhs);
  /** Compute the extended greatest common divisor. */
  UPolynomial extended_gcd(const UPolynomial& lhs, const UPolynomial& rhs,
                           UPolynomial& u, UPolynomial& v);
  /** Solves the equations
   *  u * p + v * q = r
   * assuming that gcd(p,q) divides r.
   */
  void solve_bezout(const UPolynomial& p, const UPolynomial& q,
                    const UPolynomial& r, UPolynomial& u, UPolynomial& v);

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

  std::vector<UPolynomial> sturm_sequence(const UPolynomial& p);

}  // namespace poly
