#include "polyxx/assignment.h"


#include "assignment.h"

namespace poly
{

  /** A deleter for an std::unique_ptr holding a lp_assignment_t pointer */
  inline void assignment_deleter(lp_assignment_t *ptr)
  {
    lp_assignment_delete(ptr);
  }

  Assignment::Assignment(const Context& c): mContext(c), mAssignment(lp_assignment_new(mContext.get_variable_db()), assignment_deleter)
  {
  }

  lp_assignment_t *Assignment::get_internal() { return mAssignment.get(); }
  const lp_assignment_t *Assignment::get_internal() const { return mAssignment.get(); }

  void Assignment::set(const Variable &var, const Value &value)
  {
    lp_assignment_set_value(get_internal(), var.get_internal(), value.get_internal());
  }
  void Assignment::unset(const Variable &var)
  {
    lp_assignment_set_value(get_internal(), var.get_internal(), nullptr);
  }
  Value Assignment::get(const Variable &var) const
  {
    return *lp_assignment_get_value(get_internal(), var.get_internal());
  }
  void Assignment::clear()
  {
    lp_assignment_destruct(mAssignment.get());
    lp_assignment_construct(mAssignment.get(), mContext.get_variable_db());
  }

  std::ostream &operator<<(std::ostream &os, const Assignment &a)
  {
    return os << lp_assignment_to_string(a.get_internal());
  }

} // namespace poly