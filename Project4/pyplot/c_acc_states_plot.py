import numpy as np
import matplotlib.pyplot as plt

c24ord = np.genfromtxt('new_24ord.dat', dtype = 'float', delimiter = '')
c24uno = np.genfromtxt('new_24uno.dat', dtype = 'float', delimiter = '')

c10ord = np.genfromtxt('new_10ord.dat', dtype = 'float', delimiter = '')
c10uno  = np.genfromtxt('new_10uno.dat', dtype = 'float', delimiter = '')

cycles_24ord = c24ord[:,5]
cycles_24uno = c24uno[:,5]



accepted_24ord = c24ord[:,6]
accepted_24uno = c24uno[:,6]

cycles_10ord = c10ord[:,5]
cycles_10uno = c10uno[:,5]

accepted_10ord = c10ord[:,6]
accepted_10uno = c10uno[:,6]

plt.figure()
plt.plot(cycles_24ord, accepted_24ord, label = 'T = 2.4, ordered')
plt.plot(cycles_24uno, accepted_24uno, label = 'T = 2.4 , random')
plt.legend(loc = "best")
plt.xlabel('MC cycles')
plt.ylabel('Accepted configurations')
#plt.savefig('c_num_acc_24_3.png')

plt.figure()
plt.plot(cycles_10ord, accepted_10ord, label = 'T = 1.0, ordered')
plt.plot(cycles_10uno, accepted_10uno, label = 'T = 1.0, random')
plt.legend(loc = "best")
plt.xlabel('MC cycles')
plt.ylabel('Accepted configurations')
#plt.savefig('c_num_acc_10_3.png')
plt.show()
