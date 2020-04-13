import numpy as np

n = 3
eps = 10**(-6)
a = np.loadtxt("matrix.txt")
a_n = max(a[0][0]+a[0][1]+a[0][2], a[1][0]+a[1][1]+a[1][2])
a_n = max(a_n, a[2][0]+a[2][1]+a[2][2])

b = np.array([[a_n, 0, 0], [0, a_n, 0], [0, 0, a_n]]) + (-1)*np.array(a)
x = [1, 1, 1]
pv = 0
v = 1
while np.fabs(pv-v) > eps:
    xm = np.sqrt(x[0]**2 + x[1]**2 + x[2]**2)
    e = np.array([x[0]/xm, x[1]/xm, x[2]/xm])
    x = b.dot(e)
    pv = v
    v = x.dot(e)
    print("max eigenvalue for b = ", v)
print("min eigenvalue = ", a_n - v)