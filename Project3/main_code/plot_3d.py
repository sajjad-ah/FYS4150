import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

n = 2

fig = plt.figure()
ax = fig.gca(projection='3d')

for i in range(n):
    read = open(str(i) + ".dat","r")
    x = []
    y = []
    z = []
    for j in read:
        a = j.split()
        b,c, d = a[0], a[1], a[2]
        x.append(float(b))
        y.append(float(c))
        z.append(float(d))
    ax.plot(x, y, z)

#xplt , yplt = np.meshgrid(x,y)
plt.scatter([0,0,0], [0,0,0],color='orange')
ax.legend()
plt.xlabel("x")
plt.ylabel("y")
ax.set_zlabel('z')
ax.set_xlim([-1,1])
ax.set_ylim([-1,1])
ax.set_zlim([-1,1])
plt.show()


"""
plt.plot(x,y)
plt.axis([-10.1,10.1,-10.1,10.1])
plt.show()
"""
