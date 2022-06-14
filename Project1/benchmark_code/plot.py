import numpy as np
import matplotlib.pyplot as plt

x = []
y = []

file_ = open("results.dat", "r")

for i in file_.readlines():
    a = i.split()
    x.append(float(a[1]))
    y.append(float(a[0]))

x_ = np.linspace(0,1,10000)
exact = 1 - (1 - np.exp(-10))*x_ - np.exp(-10*x_)


plt.plot(x_,exact, 'r',label="Analytical solution")
plt.plot(x, y, '--',label="Numerical solution")
plt.legend()
plt.xlabel("x")
plt.ylabel("u")
plt.show()
