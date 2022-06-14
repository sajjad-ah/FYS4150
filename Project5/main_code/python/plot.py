from numpy import *
from matplotlib.pyplot import *

read = open("init_func.dat","r")

x = []
y = []

for i in read:
    a = i.split()
    x.append(float(a[1]))
    y.append(float(a[0]))
read.close()

read = open("final_func.dat","r")

x1 = []
y1 = []

for i in read:
    a1 = i.split()
    x1.append(float(a1[1]))
    y1.append(float(a1[0]))
read.close()

#plot(x,y,"--",label="init")
plot(x1,y1)#,label="final")
xlabel("x", fontsize="15")
ylabel("u(x)", fontsize="15")
legend(loc="best")
grid()
savefig("")
show()
