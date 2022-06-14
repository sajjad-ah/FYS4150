##!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt

data0_T0 = np.genfromtxt('0energy.dat', dtype = float, delimiter= '')/400.
data1_T0 = np.genfromtxt('1energy.dat', dtype = float, delimiter= '')/400.
data2_T0 = np.genfromtxt('2energy.dat', dtype = float, delimiter= '')/400.
data3_T0 = np.genfromtxt('3energy.dat', dtype = float, delimiter= '')/400.

data_T0 = np.array([data0_T0, data1_T0, data2_T0, data3_T0])
data_T0 = np.reshape(data_T0,4*data_T0.shape[1])


data0_T1 = np.genfromtxt('0energyT1.dat', dtype = float, delimiter= '')/400.
data1_T1 = np.genfromtxt('1energyT1.dat', dtype = float, delimiter= '')/400.
data2_T1 = np.genfromtxt('2energyT1.dat', dtype = float, delimiter= '')/400.
data3_T1 = np.genfromtxt('3energyT1.dat', dtype = float, delimiter= '')/400.

data_T1 = np.array([data0_T1, data1_T1, data2_T1, data3_T1])
data_T1 = np.reshape(data_T1,4*data_T1.shape[1])

print('Variance of the energy at T = 2.4', np.var(data_T0))
print('Variance of the energy at T = 1.0', np.var(data_T1))


def Probability(Energy, data):
    probs = np.zeros(len(Energy))

    for i in range(len(Energy)):
        for d in data:
            if Energy[i] == d:
                probs[i] += 1

    return probs/len(data)

energies_T0 = np.unique(data_T0)
probs_T0 = Probability(energies_T0, data_T0)

energies_T1 = np.unique(data_T1)
probs_T1 = Probability(energies_T1, data_T1)

plt.figure()
plt.bar(energies_T0, probs_T0)
plt.plot(energies_T0, probs_T0,'r', label= r'$T=2.4$')
plt.xlabel('Energy')
plt.ylabel('Probability')
plt.legend()
#plt.savefig('histogram_probs_T0')

plt.figure()
plt.bar(energies_T1, probs_T1)
plt.plot(energies_T1, probs_T1,'r', label = r'T=1.0$')
plt.xlabel('Energy')
plt.ylabel('Probability')
plt.legend()
#plt.savefig('histogram_probs_T1')
plt.show()

"""
plt.figure()
plt.plot(energies_T0, probs_T0,'r', label = 'T = 2.4')
plt.plot(energies_T1, probs_T1,'b', label = 'T = 1.0')
plt.title('Probability for a given energy' )
plt.xlabel('Energy')
plt.ylabel('Probability')
plt.legend()
plt.savefig('histogram_compare_probs')
"""
