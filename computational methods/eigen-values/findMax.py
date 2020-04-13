import numpy as np

eps = 10**(-6)
a = np.loadtxt("matrix.txt")
x = [1, 1, 1]
pv = 0
v = 1
while np.fabs(pv-v) > eps:
    xm = np.sqrt(x[0]**2 + x[1]**2 + x[2]**2)
    e = np.array([x[0]/xm, x[1]/xm, x[2]/xm])
    x = a.dot(e)
    pv = v
    v = x.dot(e)
    print("eigenvalue = ", v)
print("max eigenvalue = ", v)
