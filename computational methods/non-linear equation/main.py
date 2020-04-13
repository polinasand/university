def func(x):
    return pow(x, 3) + 4*math.sin(x)

import math

m1 = 4
M1 = 3 + 4*math.cos(1)
t = 2/(m1 + M1)
x_p = 1
x_n = x_p
x_o = 0
ans = 0
eps = math.pow(10, -6)
print("Paramethr t = ", t)
print("Eps = ", eps)
print("Count of iterations (expected):", 8)
print("Iterations:")

while math.fabs(x_o - x_n) > eps:
    print(x_p)
    x_n = x_p - t*func(x_p)
    x_p = x_n
    ans = ans + 1
print("count of iterations: ", ans)

