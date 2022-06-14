from numpy import *
from matplotlib.pyplot import *

###################################################
read = open("e40x40.dat","r")

T = []
E = []
M = []
Cv = []
chi = []
accepted = []

for i in read:
    a = i.split()

    T.append(float(a[0]))
    E.append(float(a[1]))
    Cv.append(float(a[2]))
    M.append(float(a[3]))
    chi.append(float(a[4]))
    accepted.append(float(a[6]))

x = T

E = array(E)
M = array(M)
Cv = array(Cv)
chi = array(chi)

E = E
M = M
Cv = Cv
chi = chi
read.close()
#################################################
read = open("e60x60.dat","r")

T1 = []
E1 = []
M1 = []
Cv1 = []
chi1 = []
accepted1 = []

for i in read:
    a = i.split()

    T1.append(float(a[0]))
    E1.append(float(a[1]))
    Cv1.append(float(a[2]))
    M1.append(float(a[3]))
    chi1.append(float(a[4]))
    accepted1.append(float(a[6]))

x1 = T1

E1 = array(E1)
M1 = array(M1)
Cv1 = array(Cv1)
chi1 = array(chi1)

E1 = E1
M1 = M1
Cv1 = Cv1
chi1 = chi1
read.close()
################################################
read = open("e80x80.dat","r")

T2 = []
E2 = []
M2 = []
Cv2 = []
chi2 = []
accepted2 = []

for i in read:
    a = i.split()

    T2.append(float(a[0]))
    E2.append(float(a[1]))
    Cv2.append(float(a[2]))
    M2.append(float(a[3]))
    chi2.append(float(a[4]))
    accepted2.append(float(a[6]))

x2 = T2

E2 = array(E2)
M2 = array(M2)
Cv2 = array(Cv2)
chi2 = array(chi2)

E2 = E2
M2 = M2
Cv2 = Cv2
chi2 = chi2
read.close()
################################################
read = open("e100x100.dat","r")

T3 = []
E3 = []
M3 = []
Cv3 = []
chi3 = []
accepted3 = []

for i in read:
    a = i.split()

    T3.append(float(a[0]))
    E3.append(float(a[1]))
    Cv3.append(float(a[2]))
    M3.append(float(a[3]))
    chi3.append(float(a[4]))
    accepted3.append(float(a[6]))

x3 = T3

E3 = array(E3)
M3 = array(M3)
Cv3 = array(Cv3)
chi3 = array(chi3)

E3 = E3
M3 = M3
Cv3 = Cv3
chi3 = chi3
read.close()
################################################
plot(x,E,label='L = 40')
plot(x1,E1,label='L = 60')
plot(x2,E2,label='L = 80')
plot(x3,E3,label='L = 100')
xlabel(r"$kT\,J^{-1}$")
ylabel(r"$ \langle \mathscr{E} \rangle \, L^{-2}$",size=13)
legend(loc="best")
savefig("4e_e.png")
show()
