#!/usr/bin/python

import polypy
import polypy_test

import time
 
polypy_test.init()

[x, y, z] = [polypy.Variable(name) for name in ['x', 'y', 'z']]
polypy.variable_order.set([z, y, x])

polypy_test.start("Polynomial Feasibility Intervals")

# polypy.trace_enable("polynomial")
# polypy.trace_enable("coefficient")
# polypy.trace_enable("coefficient::sgn")
# polypy.trace_enable("coefficient::roots")
# polypy.trace_enable("value::pick");
# polypy.trace_enable("value::cmp");
# polypy.trace_enable("value::get_value_between")

# All signs
sgns = [polypy.SGN_LT_0, 
        polypy.SGN_LE_0, 
        polypy.SGN_EQ_0, 
        polypy.SGN_NE_0, 
        polypy.SGN_GT_0, 
        polypy.SGN_GE_0
        ]

sgn_name = {
            polypy.SGN_LT_0 : "<  0",
            polypy.SGN_LE_0 : "<= 0", 
            polypy.SGN_EQ_0 : "== 0",
            polypy.SGN_NE_0 : "!= 0",
            polypy.SGN_GT_0 : ">  0",
            polypy.SGN_GE_0 : ">= 0"
}

def check_feasible(p, var, assignment, expected):
    ok = True
    for sgn, expected in zip(sgns, expected):
        p_feasible = p.feasible_intervals(assignment, sgn)        
#         print "p =", p
#         print "sgn =", sgn_name[sgn]            
#         print "expected =", expected
#         print "p_feasible =", p_feasible        
        ok = len(p_feasible) == expected
        if (not ok):
            print "expected =", expected
            print "p_feasible =", p_feasible        
        if ok:
            for I in p_feasible:             
                v = I.pick_value()
                ok = I.contains(v)
                if (not ok):
                    print "I =", I
                    print "v =", v
                    break 
        if (not ok):
            print "p =", p
            print "assignment =", assignment
            print "sgn =", sgn_name[sgn]            
        polypy_test.check(ok)

assignment = polypy.Assignment()
assignment.set_value(y, polypy.AlgebraicNumber(x**2 - 2, 1))
assignment.set_value(z, polypy.AlgebraicNumber(x**2 - 3, 1))

# [-0.809841]
# -1 0 1
p_slow = ((2*z)*y**2)*x**3 + ((1*z**3)*y)*x**2 + ((1*z**2)*y**3)*x + (1*z + 4)
p_expected = [1, 1, 1, 2, 1, 1] 
check_feasible(p_slow, x, assignment, p_expected)

p_slow = (1*y**3 + (2*z**3)*y)*x**3 + ((2*z)*y**3)*x**2 + ((2*z**2)*y**2 + 3)

# for random in xrange(1000):
#     start = time.time()
#     p = polypy_test.random_polynomial(3, 2, [x, y, z], 5)
#     print p
#     for sgn in sgns:
#         p_feasible = p.feasible_intervals(assignment, sgn)        
#         # print p_feasible
#     end = time.time()
#     print end - start

# + 0 - 0 +
p = ((1*z)*y**2 + (1*z**2)*y)*x**2 + ((1*z**2)*y**2)*x + 1
p_expected = [1, 1, 2, 3, 2, 2] 
check_feasible(p, x, assignment, p_expected)

# [-0.686589047969039, 0.686589047969039]
# + 0 - 0 +
p = ((1*z**2)*y)*x**2 + (-1*y**2)
p_expected = [1, 1, 2, 3, 2, 2]
check_feasible(p, x, assignment, p_expected)

assignment = polypy.Assignment()
assignment.set_value(y, polypy.AlgebraicNumber(x**2 - 2, 1))
assignment.set_value(z, polypy.AlgebraicNumber(x**2 - 2, 1))

# + 0 + 
p = (y + z)*x**2 + (y - z)*x + (y - z)
p_expected = [0, 1, 1, 2, 2, 1]
check_feasible(p, x, assignment, p_expected)

# coefficient vanish at sqrt(2)
V = y*z -2

# + 0 -
p1 = V*x**2 - 2  *x +   (y+z)
p1_expected = [1, 1, 1, 2, 1, 1]
check_feasible(p1, x, assignment, p1_expected)

# +
p2 =   x**2 - 2*V*x +   (y+z)
p2_expected = [0, 0, 0, 1, 1, 1]
check_feasible(p2, x, assignment, p2_expected)

# + 0 - 0 +
p3 =   x**2 - 2  *x + V*(y+z)
p3_expected = [1, 1, 2, 3, 2, 2]
check_feasible(p3, x, assignment, p3_expected)

# + 0 - 0 - 0 +
p = (x**2 - y - z)*(x**2)
expected = [2, 1, 3, 4, 2, 3]
check_feasible(p, x, assignment, expected)

assignment = polypy.Assignment()
assignment.set_value(y, 1)
assignment.set_value(z, 1)

# + 0 - 0 - 0 +
p = (x**2 - y - z)*(x**2)
expected = [2, 1, 3, 4, 2, 3]
check_feasible(p, x, assignment, expected)

assignment = polypy.Assignment()
assignment.set_value(y, 1)
assignment.set_value(z, 1)

# + 0 - 0 +
p = x**2 - y - z
expected = [1, 1, 2, 3, 2, 2]
check_feasible(p, x, assignment, expected)

assignment = polypy.Assignment()
assignment.set_value(y, 0)
assignment.set_value(z, 1)

# - 0 + 0 -
p = (x - y)*(x - z)*(y - z)
expected = [2, 2, 2, 3, 1, 1]
check_feasible(p, x, assignment, expected)

assignment = polypy.Assignment()
assignment.set_value(y, 0)
assignment.set_value(z, 1)

# +
p = x**2 + y**2 + z**2
expected = [0, 0, 0, 1, 1, 1]
check_feasible(p, x, assignment, expected)
