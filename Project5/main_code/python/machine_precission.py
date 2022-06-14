#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np

L = 1
n = 1

alpha = np.pi/L
c1 = lambda x , n: np.sin(alpha*n*x)/(np.pi*n)

c2 = lambda t, n: np.exp(-alpha**2 * n**2 * t)


x_plt = np.linspace(0,1,100)
t_plt = np.linspace(0,0.15,100)

plt.figure()
plt.plot(x_plt, c1(x_plt,1), label = r'$n = 1$')
plt.plot(x_plt, c1(x_plt,2), label = r'$n = 2$')
plt.plot(x_plt, c1(x_plt,4), label = r'$n = 4$')
plt.plot(x_plt, c1(x_plt,10), label = r'$n = 10$')
plt.plot(x_plt, c1(x_plt,10), label = r'$n = 100$')
plt.legend()
plt.xlabel(r'$x$')
plt.ylabel(r'$ C_1(x) = \frac{\sin(\pi n x)}{\pi n}$')
plt.savefig('c1')

plt.figure()
plt.plot(t_plt, c2(t_plt,1),label = 'n = 1')
plt.plot(t_plt, c2(t_plt,2), label = 'n = 2')
plt.plot(t_plt, c2(t_plt,4), label = 'n = 4')
plt.plot(t_plt, c2(t_plt,10), label = 'n = 10')
plt.xlabel('t')
plt.ylabel(r'$e^{- \pi^2 n^2 t }$')
plt.legend()
plt.savefig('c2')


t = 1e-5

plt.figure()
plt.plot(x_plt, c1(x_plt, 1)*c2(t,1),label = 'n = 1')
plt.plot(x_plt, c1(x_plt, 2)*c2(t,2),label = 'n = 2')
plt.plot(x_plt, c1(x_plt, 4)*c2(t,4),label = 'n = 4')
plt.plot(x_plt, c1(x_plt, 10)*c2(t,10),label = 'n = 10')
plt.plot(x_plt, c1(x_plt, 100)*c2(t,100),label = 'n = 100')
plt.xlabel('x')
plt.ylabel(r'$C_1 C_2(1e-4)$')
plt.legend(loc = 'best')
plt.savefig('c1c2')

n_plt = np.arange(500,575,5)

max = np.zeros(len(n_plt))
for i in range(len(n_plt)):
    n = n_plt[i]
    max[i] = np.max(np.abs(c1(x_plt, n)*c2(t,n)))

plt.figure()
plt.semilogy(n_plt, (max))
plt.xlabel('n')
plt.ylabel(r'$\max \{ C_1 C_2 \}_{t = 10^-5 }$')
plt.savefig('n_max')


#print(np.max(c1(x_plt, n)*c2(t,n)))
