#pragma once

/** Some general guidelines for this API

Classes hold their data either as a member or within a std::unique_ptr.
    - Pointer, if the constructor methods return pointers to freshly allocated memory.
    - Member, if the constructor methods initialize pre-allocated objects.

All classes provide the following interface:
    - lp_data_t* get_internal();
    - const lp_data_t* get_internal() const;

If a copy constructor exists (lp_data_construct_copy):
    - explicit Data(const lp_data_t*);

Additionally, for classes that hold pointers:
    - lp_data_t* release();
    - explicit Data(lp_data_t*);

All methods are implemented as free functions, if possible.

All context classes (polynomial_context, variable_db, variable_order) are bundled in a Context class.
If computations shall be done with 


All classes that hold members should not have any other members.
Thus, we have
    static_assert(sizeof(Data) == sizeof(lp_data_t));
and can use reinterpret_cast between the two.
This also allows for direct conversions between std::vector<Data>::data() and lp_data_t*

*/

#include "poly.h"

#include "polyxx/algebraic_number.h"
#include "polyxx/assignment.h"
#include "polyxx/context.h"
#include "polyxx/dyadic_interval.h"
#include "polyxx/dyadic_rational.h"
#include "polyxx/integer.h"
#include "polyxx/integer_ring.h"
#include "polyxx/interval.h"
#include "polyxx/interval_assignment.h"
#include "polyxx/polynomial.h"
#include "polyxx/rational.h"
#include "polyxx/rational_interval.h"
#include "polyxx/sign_condition.h"
#include "polyxx/upolynomial.h"
#include "polyxx/upolynomial_roots.h"
#include "polyxx/value.h"
#include "polyxx/variable.h"
