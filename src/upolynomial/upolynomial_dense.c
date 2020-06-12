/**
 * Copyright 2015, SRI International.
 *
 * This file is part of LibPoly.
 *
 * LibPoly is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LibPoly is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with LibPoly.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "upolynomial/upolynomial_dense.h"
#include "upolynomial/upolynomial.h"
#include "upolynomial/output.h"

#include "utils/debug_trace.h"

#include <stdlib.h>
#include <assert.h>

static inline
void upolynomial_dense_normalize(upolynomial_dense_t* p_d, const lp_int_ring_t* K) {
  int d = p_d->size - 1;
  while (d > 0 && integer_sgn(K, p_d->coefficients + d) == 0) {
    d --;
  }
  p_d->size = d + 1;
}

void upolynomial_dense_construct(upolynomial_dense_t* p_d, size_t capacity) {
  assert(capacity > 0);
  p_d->capacity = capacity;
  p_d->size = 1;
  p_d->coefficients = malloc(capacity*sizeof(lp_integer_t));
  size_t i = 0;
  for (i = 0; i < capacity; i ++) {
    integer_construct_from_int(lp_Z, p_d->coefficients + i, 0);
  }
}

void upolynomial_dense_construct_p(upolynomial_dense_t* p_d, size_t capacity, const lp_upolynomial_t* p) {
  assert(capacity > lp_upolynomial_degree(p));
  upolynomial_dense_construct(p_d, capacity);
  lp_upolynomial_unpack(p, p_d->coefficients);
  p_d->size = lp_upolynomial_degree(p) + 1;
}

void upolynomial_dense_destruct(upolynomial_dense_t* p_d) {
  size_t i;
  for (i = 0; i < p_d->capacity; ++ i) {
    integer_destruct(p_d->coefficients + i);
  }
  free(p_d->coefficients);
}

void upolynomial_dense_swap(upolynomial_dense_t* p_d, upolynomial_dense_t* q_d) {
  size_t tmp1;

  tmp1 = p_d->capacity;
  p_d->capacity = q_d->capacity;
  q_d->capacity = tmp1;

  tmp1 = p_d->size;
  p_d->size = q_d->size;
  q_d->size = tmp1;

  lp_integer_t* tmp2;

  tmp2 = p_d->coefficients;
  p_d->coefficients = q_d->coefficients;
  q_d->coefficients = tmp2;
}

void upolynomial_dense_assign(upolynomial_dense_t* p_d, const upolynomial_dense_t* q_d) {
  assert(p_d->capacity >= q_d->size);
  if (p_d == q_d) return;
  size_t deg;
  for (deg = 0; deg < q_d->size; ++ deg) {
    integer_assign(lp_Z, p_d->coefficients + deg, q_d->coefficients + deg);
  }
  for (; deg < p_d->size; ++ deg) {
    integer_assign_int(lp_Z, p_d->coefficients + deg, 0);
  }
  p_d->size = q_d->size;
}

int upolynomial_dense_is_zero(const upolynomial_dense_t* p_d) {
  return p_d->size == 1 && integer_sgn(lp_Z, p_d->coefficients) == 0;
}

const lp_integer_t* upolynomial_dense_lead_coeff(const upolynomial_dense_t* p_d) {
  assert(p_d->size > 0);
  return p_d->coefficients + p_d->size - 1;
}

void upolynomial_dense_evaluate_at_rational(const upolynomial_dense_t* p_d, const lp_rational_t* x, lp_rational_t* value) {
  int i;
  rational_assign_int(value, 0, 1);
  for (i = p_d->size - 1; i >= 0; -- i) {
    rational_mul(value, value, x);
    rational_add_integer(value, value, p_d->coefficients + i);
  }
}

void upolynomial_dense_evaluate_at_dyadic_rational(const upolynomial_dense_t* p_d, const lp_dyadic_rational_t* x, lp_dyadic_rational_t* value) {
  int i;
  dyadic_rational_assign_int(value, 0, 0);
  for (i = p_d->size - 1; i >= 0; -- i) {
    dyadic_rational_mul(value, value, x);
    dyadic_rational_add_integer(value, value, p_d->coefficients + i);
  }
}

int upolynomial_dense_sgn_at_rational(const upolynomial_dense_t* p_d, const lp_rational_t* x) {
  lp_rational_t value;
  rational_construct(&value);
  upolynomial_dense_evaluate_at_rational(p_d, x, &value);
  int sgn = rational_sgn(&value);
  rational_destruct(&value);
  return sgn;
}

int upolynomial_dense_sgn_at_dyadic_rational(const upolynomial_dense_t* p_d, const lp_dyadic_rational_t* x) {
  lp_dyadic_rational_t value;
  dyadic_rational_construct(&value);
  upolynomial_dense_evaluate_at_dyadic_rational(p_d, x, &value);
  int sgn = dyadic_rational_sgn(&value);
  dyadic_rational_destruct(&value);
  return sgn;
}

int upolynomial_dense_sgn_at_plus_inf(const upolynomial_dense_t* p_d) {
  return integer_sgn(lp_Z, p_d->coefficients + p_d->size - 1);
}

int upolynomial_dense_sgn_at_minus_inf(const upolynomial_dense_t* p_d) {
  if (upolynomial_dense_is_zero(p_d)) {
    return 0;
  }
  if (p_d->size % 2) {
    // deg + 1 is odd, deg is even
    return integer_sgn(lp_Z, p_d->coefficients + p_d->size - 1);
  } else {
    return -integer_sgn(lp_Z, p_d->coefficients + p_d->size - 1);
  }
  return 0;
}

void upolynomial_dense_clear(upolynomial_dense_t* p_d) {
  size_t deg;
  for (deg = 0; deg < p_d->size; ++ deg) {
    integer_assign_int(lp_Z, p_d->coefficients + deg, 0);
  }
  p_d->size = 1;
}

lp_upolynomial_t* upolynomial_dense_to_upolynomial(const upolynomial_dense_t* p_d, const lp_int_ring_t* K) {
  assert(p_d->size > 0);
  lp_upolynomial_t* result = lp_upolynomial_construct(K, p_d->size - 1, p_d->coefficients);
  return result;
}

void upolynomial_dense_touch(upolynomial_dense_t* p_d, size_t degree) {
  if (degree >= p_d->size) {
    assert(degree < p_d->capacity);
    p_d->size = degree + 1;
  }
}

void upolynomial_dense_mk_primitive_Z(upolynomial_dense_t* p_d, int positive) {

  int degree = p_d->size > 0 ? p_d->size - 1 : 0;
  int lc_sgn = integer_sgn(lp_Z, p_d->coefficients + degree);

  lp_integer_t tmp;
  integer_construct_from_int(lp_Z, &tmp, 0);

  lp_integer_t gcd;

  // GCD start
  integer_construct_copy(lp_Z, &gcd, p_d->coefficients + degree);
  if (integer_sgn(lp_Z, &gcd) < 0) {
    integer_neg(lp_Z, &gcd, p_d->coefficients + degree);
  }
  // GCD rest
  for (-- degree; degree >= 0; -- degree) {
    if (integer_sgn(lp_Z, p_d->coefficients + degree)) {
      integer_gcd_Z(&tmp, &gcd, p_d->coefficients + degree);
      integer_swap(&tmp, &gcd);
    }
  }
  assert(integer_sgn(lp_Z, &gcd) > 0);

  // If the lc is negative, make gcd negative
  if (positive && lc_sgn < 0) {
    integer_neg(lp_Z, &tmp, &gcd);
    integer_swap(&tmp, &gcd);
  }

  // Make it primitive
  if (integer_cmp_int(lp_Z, &gcd, 1)) {
    for (degree = 0; degree <  (int) p_d->size; ++ degree) {
      if (integer_sgn(lp_Z, p_d->coefficients + degree)) {
        integer_div_Z(&tmp, p_d->coefficients + degree, &gcd);
        integer_swap(&tmp, p_d->coefficients + degree);
      }
    }
  }

  integer_destruct(&tmp);
  integer_destruct(&gcd);
}

void upolynomial_dense_mult_c(upolynomial_dense_t* p_d, const lp_int_ring_t* K, const lp_integer_t* c) {
  assert(integer_sgn(K, c));
  lp_integer_t mult;
  integer_construct_from_int(lp_Z, &mult, 0);
  size_t i;
  for (i = 0; i < p_d->size; ++ i) {
    if (integer_sgn(lp_Z, p_d->coefficients + i)) {
      integer_mul(K, &mult, p_d->coefficients + i, c);
      integer_swap(&mult, p_d->coefficients + i);
    }
  }
  integer_destruct(&mult);
}

void upolynomial_dense_div_c(upolynomial_dense_t* p_d, const lp_int_ring_t* K, const lp_integer_t* c) {
  assert(integer_sgn(K, c));
  lp_integer_t div;
  integer_construct_from_int(lp_Z, &div, 0);
  size_t i;
  for (i = 0; i < p_d->size; ++ i) {
    if (integer_sgn(lp_Z, p_d->coefficients + i)) {
      integer_div_exact(K, &div, p_d->coefficients + i, c);
      integer_swap(&div, p_d->coefficients + i);
    }
  }
  integer_destruct(&div);
}

void upolynomial_dense_add_mult_p_c(upolynomial_dense_t* p_d, const lp_upolynomial_t* p, const lp_integer_t* c) {
  assert(integer_sgn(p->K, c));
  size_t needed_degree = lp_upolynomial_degree(p);
  assert(p_d->capacity > needed_degree);
  // Add
  size_t i;
  for (i = 0; i < p->size; ++ i) {
    integer_add_mul(p->K, &p_d->coefficients[p->monomials[i].degree], &p->monomials[i].coefficient, c);
  }
  // Adjust size
  if (needed_degree >= p_d->size) {
    p_d->size = needed_degree + 1;
  }
  upolynomial_dense_normalize(p_d, p->K);
}

void upolynomial_dense_add_mult_p_int(upolynomial_dense_t* p_d, const lp_upolynomial_t* p, int c) {
  assert(c);
  size_t needed_degree = lp_upolynomial_degree(p);
  assert(p_d->capacity > needed_degree);
  // Add
  size_t i;
  for (i = 0; i < p->size; ++ i) {
    integer_add_mul_int(p->K, &p_d->coefficients[p->monomials[i].degree], &p->monomials[i].coefficient, c);
  }
  // Adjust size
  if (needed_degree >= p_d->size) {
    p_d->size = needed_degree + 1;
  }
  upolynomial_dense_normalize(p_d, p->K);
}

void upolynomial_dense_add_mult_p_mon(upolynomial_dense_t* p_d, const lp_upolynomial_t* p, const ulp_monomial_t* m) {
  assert(m->degree > 0 || integer_sgn(p->K, &m->coefficient));
  size_t needed_degree = lp_upolynomial_degree(p) + m->degree;
  assert(p_d->capacity > needed_degree);
  size_t i;
  for (i = 0; i < p->size; ++ i) {
    size_t degree = p->monomials[i].degree + m->degree;
    integer_add_mul(p->K, &p_d->coefficients[degree], &p->monomials[i].coefficient, &m->coefficient);
  }
  if (needed_degree >= p_d->size) {
    p_d->size = needed_degree + 1;
  }
  upolynomial_dense_normalize(p_d, p->K);
}

void upolynomial_dense_sub_mult_p_mon(upolynomial_dense_t* p_d, const lp_upolynomial_t* p, const ulp_monomial_t* m) {
  assert(m->degree > 0 || integer_sgn(p->K, &m->coefficient));
  size_t needed_degree = lp_upolynomial_degree(p) + m->degree;
  size_t i;
  for (i = 0; i < p->size; ++ i) {
    size_t degree = p->monomials[i].degree + m->degree;
    assert(p_d->capacity > degree);
    integer_sub_mul(p->K, &p_d->coefficients[degree], &p->monomials[i].coefficient, &m->coefficient);
  }
  if (needed_degree >= p_d->size) {
    p_d->size = needed_degree + 1;
  }
  upolynomial_dense_normalize(p_d, p->K);
}

void upolynomial_dense_sub_mult_mon(upolynomial_dense_t* p_d, const lp_int_ring_t* K, const upolynomial_dense_t* p, const ulp_monomial_t* m) {
  assert(m->degree > 0 || integer_sgn(K, &m->coefficient));

  size_t needed_size = p->size + m->degree;
  size_t d;
  for (d = 0; d < p->size; ++ d) {
    if (integer_sgn(lp_Z, p->coefficients + d)) {
      size_t degree = d + m->degree;
      assert(p_d->capacity > degree);
      integer_sub_mul(K, &p_d->coefficients[degree], p->coefficients + d, &m->coefficient);
    }
  }

  if (needed_size > p_d->size) {
    p_d->size = needed_size;
  }
  upolynomial_dense_normalize(p_d, K);
}


void upolynomial_dense_sub_mult(upolynomial_dense_t* p_d, const lp_int_ring_t* K, const upolynomial_dense_t* p, const upolynomial_dense_t* q) {

  if (upolynomial_dense_is_zero(p) || upolynomial_dense_is_zero(q)) {
    return;
  }

  size_t p_deg = p->size - 1;
  size_t q_deg = q->size - 1;

  assert(p_d->capacity > p_deg + q_deg);

  size_t i, j;
  for (i = 0; i <= p_deg; ++ i) {
    if (integer_sgn(lp_Z, p->coefficients + i)) {
      for (j = 0; j <= q_deg; ++ j) {
        if (integer_sgn(lp_Z, q->coefficients + j)) {
          integer_sub_mul(K, p_d->coefficients + i + j, p->coefficients + i, q->coefficients + j);
        }
      }
    }
  }

  if (p_deg + q_deg >= p_d->size) {
    p_d->size = p_deg + q_deg + 1;
  }
  upolynomial_dense_normalize(p_d, K);
}

void upolynomial_dense_negate(upolynomial_dense_t* p_d, const lp_int_ring_t* K) {
  size_t i;
  for (i = 0; i < p_d->size; ++ i) {
    integer_neg(K, p_d->coefficients + i, p_d->coefficients + i);
  }
}

void upolynomial_dense_div_general(const lp_int_ring_t* K, int exact, const upolynomial_dense_t* p, const upolynomial_dense_t* q, upolynomial_dense_t* div, upolynomial_dense_t* rem) {

  if (trace_is_enabled("division")) {
    tracef("upolynomial_div_general(");
    lp_int_ring_print(K, trace_out);
    tracef(", ");
    upolynomial_dense_print(p, trace_out);
    tracef(", ");
    upolynomial_dense_print(q, trace_out);
    tracef(")\n");
  }

  assert(p);
  assert(q);
  assert(q->size <= p->size);

  // monomial we use to multiply with
  ulp_monomial_t m;
  umonomial_construct_from_int(lp_Z, &m, 0, 0);

  // adjustment for the powers of div
  lp_integer_t adjust;
  integer_construct_from_int(lp_Z, &adjust, 0);

  // Degrees of p and q
  int p_deg = p->size > 0 ? p->size - 1 : 0;
  int q_deg = q->size > 0 ? q->size - 1 : 0;

  // Copy p into rem
  upolynomial_dense_assign(rem, p);
  upolynomial_dense_clear(div);

  int k;
  for (k = p_deg; k >= q_deg; -- k) {
    // next coefficient to eliminate
    while (exact && k >= q_deg && integer_sgn(lp_Z, rem->coefficients + k) == 0) {
      k --;
    }
    // if found, eliminate it
    if (k >= (int) q_deg) {

      if (trace_is_enabled("division")) {
        tracef("q = ");
        upolynomial_dense_print(q, trace_out);
        tracef("\nrem = ");
        upolynomial_dense_print(rem, trace_out);
        tracef("\ndiv = ");
        upolynomial_dense_print(div, trace_out);
        tracef("\n");
      }

      assert(!exact || integer_divides(K, q->coefficients + q_deg, rem->coefficients + k));

      // Eliminate the coefficient using q*m
      m.degree = k - q_deg;

      // Get the quotient coefficient
      if (exact) {
        // get the quotient
        integer_div_exact(K, &m.coefficient, rem->coefficients + k, q->coefficients + q_deg);
      } else {
        // rem: a*x^k, q: b*x^d, so we multiply rem with b and subtract a*q
        integer_assign(lp_Z, &m.coefficient, rem->coefficients + k);
        upolynomial_dense_mult_c(rem, K, q->coefficients + q_deg);
      }

      // Do the subtraction
      if (integer_sgn(lp_Z, &m.coefficient)) {
        upolynomial_dense_sub_mult_mon(rem, K, q, &m);
      }

      // Put the monomial into the division
      if (exact || !integer_sgn(lp_Z, &m.coefficient)) {
        integer_swap(&div->coefficients[m.degree], &m.coefficient);
      } else {
        // Adjust the monomial with to be lc(q)^(k-deg_q)
        integer_pow(K, &adjust, q->coefficients + q_deg, m.degree);
        integer_mul(K, &div->coefficients[m.degree], &m.coefficient, &adjust);
      }
      upolynomial_dense_touch(div, m.degree);
    }
  }

  // Free temporaries
  integer_destruct(&adjust);
  umonomial_destruct(&m);

  TRACE("division", "upolynomial_div_general(): done\n");

}

void upolynomial_dense_reduce_Z(const upolynomial_dense_t* p, const upolynomial_dense_t* q, lp_integer_t* a, upolynomial_dense_t* red) {

  lp_integer_t lcm, red_mult;
  integer_construct_from_int(lp_Z, &lcm, 0);
  integer_construct_from_int(lp_Z, &red_mult, 0);

  if (trace_is_enabled("division")) {
    tracef("upolynomial_dense_reduce_Z(");
    upolynomial_dense_print(p, trace_out);
    tracef(", ");
    upolynomial_dense_print(q, trace_out);
    tracef(")\n");
  }

  assert(p);
  assert(q);
  assert(q->size <= p->size);

  // We start with 1
  integer_assign_int(lp_Z, a, 1);

  // monomial we use to multiply with
  ulp_monomial_t m;
  umonomial_construct_from_int(lp_Z, &m, 0, 0);

  // Degrees of p and q
  int p_deg = p->size > 0 ? p->size - 1 : 0;
  int q_deg = q->size > 0 ? q->size - 1 : 0;

  // Copy p into rem
  upolynomial_dense_assign(red, p);

  int k;
  for (k = p_deg; k >= q_deg; -- k) {
    // next coefficient to eliminate
    while (k >= q_deg && integer_sgn(lp_Z, red->coefficients + k) == 0) {
      k --;
    }
    // if found, eliminate it
    if (k >= (int) q_deg) {

      if (trace_is_enabled("division")) {
        tracef("q = ");
        upolynomial_dense_print(q, trace_out);
        tracef("\nred = ");
        upolynomial_dense_print(red, trace_out);
        tracef("\n");
      }

      // Eliminate the coefficient using q*m
      m.degree = k - q_deg;

      // Get the quotient coefficient
      if (integer_divides(lp_Z, q->coefficients + q_deg, red->coefficients + k)) {
        integer_div_Z(&m.coefficient, red->coefficients + k, q->coefficients + q_deg);
      } else{
        // red: a*x^k, q: b*x^d, so we multiply red with lcm/a and subtract
        // lcm/b multiple of q
        integer_lcm_Z(&lcm, red->coefficients + k, q->coefficients + q_deg);
        integer_div_exact(lp_Z, &red_mult, &lcm, red->coefficients + k);
        integer_div_exact(lp_Z, &m.coefficient, &lcm, q->coefficients + q_deg);

        if (trace_is_enabled("division")) {
          tracef("lcm = "); integer_print(&lcm, trace_out); tracef("\n");
          tracef("red_mult = "); integer_print(&red_mult, trace_out); tracef("\n");
          tracef("m.c = "); integer_print(&m.coefficient, trace_out); tracef("\n");
        }

        integer_mul(lp_Z, a, a, &red_mult);
        upolynomial_dense_mult_c(red, lp_Z, &red_mult);
      }

      // Do the subtraction
      upolynomial_dense_sub_mult_mon(red, lp_Z, q, &m);

      if (trace_is_enabled("division")) {
        tracef("red' = ");
        upolynomial_dense_print(red, trace_out);
      }
    }
  }

  // Free temporaries
  integer_destruct(&lcm);
  integer_destruct(&red_mult);
  umonomial_destruct(&m);

  TRACE("division", "upolynomial_dense_reduce_Z(): done\n");
}

void upolynomial_dense_derivative(const lp_int_ring_t* K, const upolynomial_dense_t* p_d, upolynomial_dense_t* p_d_prime) {
  upolynomial_dense_clear(p_d_prime);
  int deg = p_d->size - 1;
  if (deg > 0) {
    int i;
    for (i = deg; i > 0; -- i) {
      if (integer_sgn(K, &p_d->coefficients[i])) {
        integer_mul_int(K, &p_d_prime->coefficients[i-1], &p_d->coefficients[i], i);
      }
    }
    upolynomial_dense_touch(p_d_prime, deg-1);
    upolynomial_dense_normalize(p_d_prime, K);
  }
}
