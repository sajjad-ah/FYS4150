from numpy import *
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter

A = zeros((51,51))
B = zeros((51,51))

absol = zeros((51,51))
relat = zeros((51,51))

read1 = open("2d-analytical_tsteps2500_dt0,2_500_50x50.dat","r")
read2 = open("2d-new_t0,2_dt0,25.dat","r")


i = 0
for el1 in read1:
    s = el1.split()
    for j in range(len(s)):
        A[i][j] = s[j]
    i += 1

i = 0
for el1 in read2:
    s = el1.split()
    for j in range(len(s)):
        B[i][j] = float(s[j])
    i += 1
read1.close()
read2.close()

absol = abs(B - A)
relat = abs(B-A)/A

ab = 0
ai = 0
aj = 0
re = 0
ri = 0
rj = 0

for i in range(1,50):
    for j in range(1,50):
        if absol[i][j] > ab:
            ab = absol[i][j]
            ai = i
            aj = j
        if relat[i][j] > re:
            re = relat[i][j]
            ri = i
            rj = j

print ab, ai, aj
print re, ri, rj

A_250 = A
N_250 = B
E_250 = abs(N_250-A_250)
rE_250 = E_250/A_250
