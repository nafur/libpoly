#pragma once

#include "../sign_condition.h"

#include <iosfwd>

namespace poly {

enum class SignCondition
{
  LT = LP_SGN_LT_0,
  LE = LP_SGN_LE_0,
  EQ = LP_SGN_EQ_0,
  NE = LP_SGN_NE_0,
  GT = LP_SGN_GT_0,
  GE = LP_SGN_GE_0
};

lp_sign_condition_t to_sign_condition(SignCondition sc);

/** Stream the given SignCondition to an output stream. */
std::ostream& operator<<(std::ostream& os, const SignCondition& sc);

/** Evaluates a sign condition.
 * Expected values of sgn: -1, 0, 1
 */
bool evaluate_sign_condition(SignCondition sc, int sgn);

}  // namespace poly
