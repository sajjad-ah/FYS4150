#omega = 0.01 were ran with p_max = 100 and 400x400 matrix
#omega >= 0.5 were ran with p_max = 10 and 300x300 matrix

import numpy as np
import matplotlib.pyplot as plt
import sys


file = sys.argv[1]

psi = []
read = open(file,"r")
for i in read:
    psi.append(float(i))
read.close()


p_min = 0
p_max = 100.0
h = (p_max-p_min)/float(len(psi))

r = np.zeros(len(psi))
for i in range(len(psi)):
    r[i] = (i+1)*h

plt.plot(r,psi)
plt.xlabel(r"$\frac{r}{\alpha}$", fontsize="20")
plt.ylabel("u(r)")
plt.show()
