#!/usr/bin/env python3
from scipy.stats import linregress
import numpy as np
import matplotlib.pyplot as plt

T = np.array([2.300, 2.295, 2.290,2.285, 2.275, 2.280])
L = np.array([1/60, 1/80, 1/100, 1/60, 1/80,1/100])

slope , intercept , r_value, p_value, std_err = linregress(L, T)
del r_value, p_value, std_err

f = lambda x: x*slope + intercept
x_plt = np.linspace(-0.0, 0.02)

plt.figure()
plt.scatter(L[:3],T[:3], label = r"$\chi$")
plt.scatter(L[3:],T[3:], label = r'$C_V$')
plt.plot(x_plt, f(x_plt))
plt.xlim(0,0.02)
plt.ylim(2.27,2.305)
plt.legend(loc = 2)
plt.xlabel(r'$L^{-1}$')
plt.ylabel(r'$T_C(L^{-1li})$')
plt.savefig('linreg_e')
#plt.show()

print('The best value estimate of T_C is: ', f(0))
print(slope, intercept)
