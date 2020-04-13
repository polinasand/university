import numpy as np
import math

n = 4

a = np.loadtxt("a.txt")
b = np.loadtxt("b.txt")

for i in range(n):
    for j in range(i):
        if a[i][j] != a[j][i]:
            exit(0)

d = [[0] * n for i in range(n)]
s = [[0] * n for i in range(n)]

ad = 0
i = 0

while i < n:
    ad = 0
    p = 0
    while p < i:
        ad += s[p][i] * s[p][i] * d[p][p]
        p += 1
    d[i][i] = np.sign(a[i][i] - ad)
    s[i][i] = np.sqrt(np.fabs(a[i][i] - ad))
    # print(d[i][i])
    # print(s[i][i])
    if i < n - 1:
        j = i + 1
        while j < n:
            ad = 0
            p = 0
            while p < i:
                ad += s[p][i] * d[p][p] * s[p][j]
                p += 1
            s[i][j] = (a[i][j] - ad)/(d[i][i]*s[i][i])

            j += 1
    i += 1


s = np.array(s)
s_t = np.array(s.transpose())
m = np.array(s_t.dot(d))

y = []
for i in range(n):
    ans = 0
    for j in range(i):
        ans += y[j]*m[i][j]
    y.append((b[i] - ans)/m[i][i])

x = []
for i in range(n):
    ans = 0
    for j in range(i):
        ans += x[j]*s[n-1-i][n-1-j]
    x.append((y[n-1-i] - ans)/s[n-i-1][n-i-1])
x.reverse()
print("Solution")
for i in x:
    print('%.3f' % i)

det = 1
for i in range(n):
    det *= s[i][i]*s[i][i]*d[i][i]
print("determinant")
print('%.3f' % det)

a_inv = np.linalg.inv(a)
a_n = 0
for i in range (n):
    curr = 0
    for j in range(n):
        curr += a[i][j]
    a_n = max(curr, a_n)
a_inv_n = 0

for i in range (n):
    curr = 0
    for j in range(n):
        curr += a_inv[i][j]
    a_inv_n = max(curr, a_inv_n)

print(a_n*a_inv_n)