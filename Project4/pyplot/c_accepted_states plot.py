import numpy as np
import matplotlib.pyplot as plt

# Load data:
c24ord = np.genfromtxt('new_24ord.dat', dtype = 'float', delimiter = '')
c24uno = np.genfromtxt('new_24uno.dat', dtype = 'float', delimiter = '')

c10ord = np.genfromtxt('new_10ord.dat', dtype = 'float', delimiter = '')
c10uno  = np.genfromtxt('new_10uno.dat', dtype = 'float', delimiter = '')

# T = 2.4
cycles_24ord = c24ord[:,5]
cycles_24uno = c24uno[:,5]

accepted_24ord = c24ord[:,6]
accepted_24uno = c24uno[:,6]

# T = 1.0
cycles_10ord = c10ord[:,5]
cycles_10uno = c10uno[:,5]

accepted_10ord = c10ord[:,6]
accepted_10uno = c10uno[:,6]

#plot T = 2.4
plt.figure()
plt.plot((cycles_24ord[:35]), accepted_24ord[:35], label = 'T = 2.4, (ordered)')
plt.plot((cycles_24uno[:35]), accepted_24uno[:35], label = 'T = 2.4 , (unordered)')
plt.legend(loc = 4)
plt.xlabel('Monte Carlo cycles')
plt.ylabel('Accepted states')
plt.savefig('c_num_accepted_24')

#plot T = 1.0
plt.figure()
plt.plot((cycles_10ord), accepted_10ord, label = 'T = 1.0, (orderd)')
plt.plot((cycles_10uno), accepted_10uno, label = 'T = 1.0, (unorderd)')
plt.legend(loc = 4)
plt.xlabel('Monte Carlo cycles')
plt.ylabel('Accepted states')
plt.savefig('c_num_accepted_10')

# accepted states as a function of temperature:
T = np.array([1.0, 2.4])

plt.figure()
plt.bar(T, [np.sum(accepted_10ord), np.sum(accepted_24ord)], align = 'center', log = True, width = 0.2 ,  color = 'r', label = 'orderd')
plt.bar(T,[np.sum(accepted_10uno), np.sum(accepted_24uno)], align = 'edge', log = True, width=0.1 ,  label = 'unorderd')

plt.legend(loc = 2)
plt.xlabel('Temperature T')
plt.ylabel('Accepted states')
plt.savefig('c_T_accepted')
