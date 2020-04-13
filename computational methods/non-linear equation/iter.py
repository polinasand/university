import math


def func(x):
    return math.asin(-x**3/4)


x_p = 0
x_n = 1
x_o = 0
ans = 0
eps = math.pow(10, -6)
q = 3/math.sqrt(15)
print("Eps = ", eps)
print("Count of iterations (expected):", 60)
print("Iterations:")

while math.fabs(x_p - x_n) > eps*(1-q)/q:
    x_p = x_n
    print(x_p)
    x_n = func(x_p)
    ans = ans + 1
print("count of iterations: ", ans)

