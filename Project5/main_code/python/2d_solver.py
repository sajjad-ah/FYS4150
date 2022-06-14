#!/usr/bin/env python3
import numpy as np
from scipy.sparse import diags
from scipy.sparse.linalg import spsolve

import matplotlib.pyplot as plt

""""
NOT FINISHED
""""

def u_exact(t, N = 1e4, dx = 0.01, L = 1):
    """
    The analytical solution:
    """
    N = int(N)

    x = np.linspace(0,1,int(1/dx), 'float')
    u_exact = x/L

    for n in np.arange(1, N+1):
        lmb = n*np.pi/L
        A_n = 2*(np.pi*n*np.cos(np.pi*n)-np.sin(np.pi*n))/(np.pi*n)**2
        u_exact += A_n * np.exp(-lmb**2*t)*np.sin(lmb*x)

    return u_exact


def solver(I ,dx, dt, T, theta = 1/2, save_solution = False, filename = 'u_aprox'):

    """
    Numerically solves the 1D diffusion equation using finite difference method:
                        u_t = u_xx

    With none-homegenus didrech boundary conditions:
                u(0,t) = 0 and u(1,t) = 1

    Initial condition:
                        u(x,0) = I(x)

    The method for solving the PDE is determined by theta:
        Explicit forward euler:               theta = 0
        Implicit backward euler:              theta = 1
        Implicit Crank Nicolson scheme:       theta = 1/2

    """

    T = 1. # End time

    Nx = int(1/dx)
    Nt = int(T/dt)

    x = np.linspace(0,1,Nx)
    t = np.linspace(0,T,Nt)

    lmbd = dt/dx**2

    print('______________________________________________________________')
    if theta == 0: print('Explicit euler')
    elif theta == 1/2: print('Implicit Crank Nicolson scheme')
    elif theta == 1: print('Implicit backward euler')
    print( 'Lambda: ', round(lmbd,2) )
    print( 'dt = ' , dt)
    print( 'dx = ' , dx)
    print('______________________________________________________________')

    # setting up the linear system: Au = b
    # A (Tridiagonal matrix elements):

    upper = np.zeros(Nx-1)
    upper.fill(-lmbd*theta)

    lower = np.zeros(Nx-1)
    lower.fill(-lmbd*theta)

    diag = np.zeros(Nx)
    diag.fill(1+2*lmbd*theta)

    #modify the elements to fit the B.C.
    diag[0]  = 1
    diag[-1] = 1

    if theta == 1:
        upper[0] = 0
        lower[-1] = 0

    A = diags(
        diagonals=[diag, lower, upper],
        offsets=[0, -1, 1], shape=(Nx, Nx),
        format='csr')

    #print('A matrix: ')
    #print (A.todense() )  # Check that A is correct
    #print('')

    def calculate_b(u, theta, lmbd):
        size = len(u)

        b = np.zeros(len(u))
        b[0] = u[0]
        b[-1] = u[-1]

        for i in np.arange(1,size-1):
            b[i] = u[i] + lmbd*(1-theta)*(u[i+1]-2*u[i]+u[i-1])

        return b

    #b satisfying the initial condition:
    u = I(x)
    b = calculate_b(u, theta, lmbd)

    #print('b matrix: ')
    #print(b)

    # solve for each time step assert if numerical solution reaches a treshold
    u_aprox = np.zeros((Nt,Nx))

    u1 = np.zeros(Nx+1)                         # The next time step.

    for n in range(0,Nt):
        u = spsolve(A,b)

        u[0] = 0.0; u[-1] = 1.0                 # updating boundary condtions

        u1 = u                                  # reshuffle
        b = calculate_b(u, theta, lmbd)

        u_aprox[n] = u                          # store solutions to array for later use

    if save_solution == True:
        np.savetxt(filename +'.txt', u_aprox, delimiter =  ' ')    # save solution


    return u_aprox

def test_of_stability():


    def I(x):
        I = np.zeros(len(x))
        I[-1] = 1
        return I

    thetas = [0,1/2,1]

    for theta in thetas:
        theta = 0
        dt = 0.001
        dx = 0.05

    return 0



if __name__ == '__main__':


    def I(x):
        I = np.zeros(len(x))
        I[-1] = 1
        return I


    theta = 0
    dt = 0.001
    dx = 0.05



    u_aprox = solver(I ,dx = dx, dt = dt, T = 1, theta = 1)
