from numpy import *

def f(x,y):
    count = 0
    for m in range(1,3000):
        for n in range(1,3000):
            a = sin(m*pi*x)*sin(n*pi*y)
            b = (16.0/(pi*pi*m*n))*sin(pi*m/4.0)*sin(pi*m/2.0)*sin(pi*n/4.0)*sin(pi*n/2.0)
            count += a*b
    return count

print f(1/2.,1/2.)
