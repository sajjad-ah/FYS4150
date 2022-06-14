from numpy import *
from matplotlib.pyplot import *

x0, y0 = [],[]
read = open('0.dat','r')
for i in read:
    a = i.split()
    x0.append(float(a[0]))
    y0.append(float(a[1]))
read.close()

"""
x1, y1 = [],[]
read = open('1.dat','r')
for i in read:
    a = i.split()
    x1.append(float(a[0]))
    y1.append(float(a[1]))
read.close()

"""
plot(x0,y0,'b')
#plot(x1,y1,'g')
#plot(x2,y2)
scatter(0,0,color='orange')
xlabel('x/AU')
ylabel('y/AU')
axis([-1.8,1.8,-1.8,1.8])
legend([r'Earth'])#,r'Jupiter'])#r'dt = 10$^{-4}$'])
savefig('sej.png')
show()
