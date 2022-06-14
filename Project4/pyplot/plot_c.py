from numpy import *
from matplotlib.pyplot import *


########################################################
read = open("new_10ord.dat","r")

n_cyc = []
E = []
M = []
accepted = []

for i in read:
    a = i.split()
    n_cyc.append(float(a[5]))
    E.append(float(a[1]))
    M.append(float(a[3]))
    accepted.append(float(a[6]))

x = log10(n_cyc)

E = array(E)
M = array(M)

E = E
M = M
read.close()
########################################################
read = open("new_10uno.dat","r")

n_cyc1 = []
E1 = []
M1 = []
accepted1 = []

for i in read:
    a = i.split()
    n_cyc1.append(float(a[5]))
    E1.append(float(a[1]))
    M1.append(float(a[3]))
    accepted1.append(float(a[6]))

x1 = log10(n_cyc1)

E1 = array(E1)
M1 = array(M1)

E1 = E1
M1 = M1
read.close()
########################################################
read = open("new1_c24ord.dat","r")

n_cyc2 = []
E2 = []
M2 = []
accepted2 = []

for i in read:
    a = i.split()
    n_cyc2.append(float(a[5]))
    E2.append(float(a[1]))
    M2.append(float(a[3]))
    accepted2.append(float(a[6]))

x2 = log10(n_cyc2)

E2 = array(E2)
M2 = array(M2)

E2 = E2
M2 = M2
read.close()
########################################################
read = open("new1_c24uno.dat","r")

n_cyc3 = []
E3 = []
M3 = []
accepted3 = []

for i in read:
    a = i.split()
    n_cyc3.append(float(a[5]))
    E3.append(float(a[1]))
    M3.append(float(a[3]))
    accepted3.append(float(a[6]))

x3 = log10(n_cyc3)

E3 = array(E3)
M3 = array(M3)

E3 = E3
M3 = M3
read.close()
########################################################

plot(x,E,label='T=1.0, ordered')
plot(x1,E1,label='T=1.0, random')
plot(x2,E2,label='T=2.4, ordered')
plot(x3,E3,label='T=2.4, random')
xlabel(r'log$_{10}$(N$_{MC}$)')
ylabel(r'$\langle E \rangle $ $L^{-2}$', fontsize="20")
axis([1,6.1,-2.1,-0.6])
legend(loc="best")
savefig("c_plot_energy.png")
show()
