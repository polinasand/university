import math

def f0(x):
    return math.sin(2*x)
def f1(x):
    return math.cos(2*x)*2
def f2(x):
    return -4*math.sin(2*x)
def f3(x):
    return -8*math.cos(2*x)

x0 = 0
x1 = math.pi / 4
x2 = math.pi / 2
x3 = math.pi

x = [x0, x0, x1, x1, x1, x1, x2, x3]
n = len(x)
a = []
for i in range(n):
    for j in range(n-i):
        if i == 0:
            a.append(f0(x[j]))
        elif x[j] == x[(j+i) % n]:
            if i == 1:
                a.append(f1(x[j]))
            elif i == 2:
                a.append(f2(x[j]))
            elif i == 3:
                a.append(f3(x[j]))
        else:
            a.append((a[-n+i-1] - a[-n+i])/(x[j] - x[(j+i) % n]))
print(n)

c= []
t = 0
for i in range(n):
    c.append(a[t])
    t += (n-i)

ans = 0
arg = float(input())
for i in range(n):
    t = c[i]
    for j in range(i):
        t *= (arg - x[j])
    ans += t

print('{:.5f}'.format(ans))

