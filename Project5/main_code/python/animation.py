#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

from u_exact import u_exact

u_aprox = np.loadtxt('u_aprox.txt')

print('u shape: ', u_aprox.shape)

Nx = u_aprox.shape[1]
Nt = u_aprox.shape[0]

dx = 1/Nx
dt = 1/Nt

x_plt = np.linspace(0,1,u_aprox.shape[1])

fig = plt.figure()
ax = plt.axes(xlim = (0,1), ylim = (0,1))
line, = ax.plot([],[], lw = 2)

def init():
    line.set_data([],[])
    return line

def animate(i):
    line.set_data(x_plt,u_aprox[i])
    return line

anim = animation.FuncAnimation(fig, animate,
                               init_func = init,
                               frames =u_aprox.shape[0],
                               interval = 1,
                               blit = False)

anim.save('u_aprox.gif', writer = 'imagemagick', fps = 30)
