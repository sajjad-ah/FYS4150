#!/usr/bin/env python2

import matplotlib
import matplotlib.pyplot as plt
from matplotlib import animation


import numpy as np



def u_exact(t ,N = 1e4, dx = 0.01, L = 1):
    N = int(N)

    x = np.linspace(0,1,int(1/dx), 'float')
    u_exact = x/L

    for n in np.arange(1, N+1):
        lmb = n*np.pi/L
        A_n = 2*(np.pi*n*np.cos(np.pi*n)-np.sin(np.pi*n))/(np.pi*n)**2
        u_exact += A_n * np.exp(-lmb**2*t)*np.sin(lmb*x)

    return u_exact


fig = plt.figure()
ax = plt.axes(xlim = (0,1), ylim = (0,1))
line, = ax.plot([],[], lw = 2)

def init():
    line.set_data([],[])
    return line,

def animate(i):
    dt = 0.001
    dx = 0.001
    x_plt = np.linspace(0,1,int(1/dx), 'float')
    y = u_exact(dt*i,dx = dx)
    line.set_data(x_plt,y)

    return line,

anim = animation.FuncAnimation(fig, animate,
                               init_func = init,
                               frames = 600,
                               interval = 1,
                               blit = False)

anim.save('U_exact.gif', writer='imagemagick', fps=30)
