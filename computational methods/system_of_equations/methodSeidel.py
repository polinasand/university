import numpy as np
import math

n = 3
eps = 0.0001
a = np.loadtxt("a.txt")
b = np.loadtxt("b.txt")

for i in range(n):
    if a[i][i] == 0:
        print ("elem at (", i, ";", i, ") is 0")
        exit(0)

q = 0
for i in range(n):
    curr = 0
    for j in range(n):
        if j != i:
            curr += abs(a[i][j])
    if abs(a[i][i]) < curr:
        print ("no limit")
        exit(0)
    q = max(q, curr/a[i][i])

x = [0]*n
k = np.floor(np.log(eps*(1-q))/np.log(q))
t = 0
while t<k:
    for i in range(n):
      prev = 0
      curr = 0
      for j in range(i):
          curr += a[i][j]/a[i][i]*x[j]
      j = i+1
      while j < n:
          prev += a[i][j]/a[i][i]*x[j]
          j+=1
      x[i] = -prev-curr+b[i]/a[i][i]
    t+=1
print(x)
print(np.linalg.solve(a, b))