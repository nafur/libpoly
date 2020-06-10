
#ifndef CVC4__THEORY__NLARITH__LIBPOLY__ROOT_ISOLATION_H
#define CVC4__THEORY__NLARITH__LIBPOLY__ROOT_ISOLATION_H

#include <poly/algebraic_number.h>

#include "assignment.h"
#include "polynomial.h"
#include "upolynomial.h"
#include "ran.h"
#include "value.h"

namespace CVC4 {
namespace theory {
namespace arith {
namespace nl {
namespace libpoly {

/** Isolate the real roots of a UPolynomial. */
std::vector<RAN> isolate_real_roots(const UPolynomial& p);

}  // namespace libpoly
}  // namespace nl
}  // namespace arith
}  // namespace theory
}  // namespace CVC4

#endif
