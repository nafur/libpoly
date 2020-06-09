#include "polyxx/variable.h"

namespace poly
{

  Variable::Variable(const Context &c) : mContext(c), mVariable(lp_variable_null) {}
  Variable::Variable(const Context &c, lp_variable_t var) : mContext(c), mVariable(var) {}
  Variable::Variable(const Context &c, const char *name)
      : mContext(c), mVariable(lp_variable_db_new_variable(mContext.get_variable_db(), name))
  {
  }

  lp_variable_t Variable::get_internal() const { return mVariable; }

  std::ostream &operator<<(std::ostream &os, const Variable &v)
  {
    return os << lp_variable_db_get_name(v.mContext.get_variable_db(), v.get_internal());
  }

  bool operator==(const Variable &lhs, const Variable &rhs)
  {
    return lhs.get_internal() == rhs.get_internal();
  }
  bool operator!=(const Variable &lhs, const Variable &rhs)
  {
    return lhs.get_internal() != rhs.get_internal();
  }

} // namespace poly
