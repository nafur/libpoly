#pragma once

#include <cassert>
#include <iosfwd>
#include <vector>

#include "../monomial.h"
#include "../polynomial.h"
#include "../variable_list.h"
#include "assignment.h"
#include "integer.h"
#include "interval.h"
#include "sign_condition.h"
#include "value.h"
#include "variable.h"

namespace poly {

/**
 * Implements a wrapper for lp_polynomial_t from libpoly.
 */
class Polynomial {
  friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);

  /** The actual polynomial. */
  deleting_unique_ptr<lp_polynomial_t> mPoly;

 public:
  Polynomial(lp_polynomial_t* poly);
  Polynomial(const lp_polynomial_t* poly);

  /** Construct a zero polynomial. */
  Polynomial(const lp_polynomial_context_t* c);
  Polynomial(const Context& c);
  Polynomial() : Polynomial(Context::get_context()) {}
  /** Create from a variable. */
  Polynomial(const Context& c, Variable v);
  Polynomial(Variable v) : Polynomial(Context::get_context(), v) {}
  /** Construct i * v^n. */
  Polynomial(const Context& c, Integer i, Variable v, unsigned n);
  Polynomial(Integer i, Variable v, unsigned n)
      : Polynomial(Context::get_context(), i, v, n) {}
  Polynomial(const Context& c, Integer i);
  Polynomial(Integer i) : Polynomial(Context::get_context(), i){};
  /** Copy from the given Polynomial. */
  Polynomial(const Polynomial& p);

  /** Assign from the given Polynomial. */
  Polynomial& operator=(const Polynomial& p);

  /** Get a non-const pointer to the internal lp_polynomial_t. Handle with care!
   */
  lp_polynomial_t* get_internal();
  /** Get a const pointer to the internal lp_polynomial_t. */
  const lp_polynomial_t* get_internal() const;
};

namespace detail {
inline const lp_polynomial_context_t* context(const Polynomial& p) {
  return lp_polynomial_get_context(p.get_internal());
}
inline const lp_polynomial_context_t* context(const Polynomial& lhs,
                                              const Polynomial& rhs) {
  assert(lp_polynomial_context_equal(context(lhs), context(rhs)) == 0);
  (void)rhs;
  return context(lhs);
}
}  // namespace detail

/** Stream the given Polynomial to an output stream. */
std::ostream& operator<<(std::ostream& os, const Polynomial& p);
/** Compare polynomials for equality. */
bool operator==(const Polynomial& lhs, const Polynomial& rhs);
/** Compare polynomials. */
bool operator<(const Polynomial& lhs, const Polynomial& rhs);

/** Add two polynomials. */
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
/** Add a polynomial and an integer. */
Polynomial operator+(const Polynomial& lhs, const Integer& rhs);
/** Add an integer and a polynomial. */
Polynomial operator+(const Integer& lhs, const Polynomial& rhs);

/** Unary negation of a polynomial. */
Polynomial operator-(const Polynomial& p);
/** Subtract two polynomials. */
Polynomial operator-(const Polynomial& lhs, const Polynomial& rhs);
/** Subtract an integer from a polynomial. */
Polynomial operator-(const Polynomial& lhs, const Integer& rhs);
/** Subtract a polynomial from an integer. */
Polynomial operator-(const Integer& lhs, const Polynomial& rhs);

/** Multiply two polynomials. */
Polynomial operator*(const Polynomial& lhs, const Polynomial& rhs);
/** Multiply a polynomial and an integer. */
Polynomial operator*(const Polynomial& lhs, const Integer& rhs);
/** Multiply an integer and a polynomial. */
Polynomial operator*(const Integer& lhs, const Polynomial& rhs);

/** Multiply and assign two polynomials. */
Polynomial& operator*=(Polynomial& lhs, const Polynomial& rhs);

/** Compute a polynomial to some power. */
Polynomial pow(const Polynomial& lhs, unsigned exp);

/** Divide a polynomial by a polynomial, assuming that there is no remainder. */
Polynomial div(const Polynomial& lhs, const Polynomial& rhs);

/** Check if the given polynomial is constant. */
bool is_constant(const Polynomial& p);
/** Obtain the degree of the given polynomial in its main variable. */
std::size_t degree(const Polynomial& p);
/** Obtain the main variable of the given polynomial. */
Variable main_variable(const Polynomial& p);
/** Obtain the k'th coefficient of a polynomial. */
Polynomial coefficient(const Polynomial& p, std::size_t k);
/** Obtain the leading coefficient of a polynomial. */
Polynomial leading_coefficient(const Polynomial& p);
/** Obtain all non-constant coefficients of a polynomial. */
std::vector<Polynomial> coefficients(const Polynomial& p);

/** Compute the derivative of a polynomial (in its main variable). */
Polynomial derivative(const Polynomial& p);

/** Compute the resultant of two polynomials. */
Polynomial resultant(const Polynomial& p, const Polynomial& q);

/** Compute the discriminant of a polynomial. */
Polynomial discriminant(const Polynomial& p);

/**
 * Compute a square-free factorization of a polynomial.
 * Attention: this does not yield a full factorization!
 */
std::vector<Polynomial> square_free_factors(const Polynomial& p);

/** Isolate the real roots of a Polynomial with respect to an Assignment for all
 * but the main variable. */
std::vector<Value> isolate_real_roots(const Polynomial& p, const Assignment& a);

bool evaluate_polynomial_constraint(const Polynomial& p, const Assignment& a,
                                    SignCondition sc);

std::vector<Interval> infeasible_regions(const Polynomial& p,
                                         const Assignment& a, SignCondition sc);

int sgn(const Polynomial& p, const Assignment& a);

/** Utility class to collect all variables from a sequence of polynomials.
 */
class VariableCollector {
 private:
  /** Internal variable list. */
  lp_variable_list_t mVarList;

 public:
  /** Default constructor, create the variable list. */
  VariableCollector();
  /** Destructs the variable list. */
  ~VariableCollector();
  /** Adds the variables of the given polynomial to the list. */
  void operator()(const Polynomial& p);
  /** Returns the list of variables as a vector of Variables. */
  std::vector<Variable> get_variables() const;
};

}  // namespace poly
