from numpy import *
from matplotlib.pyplot import *
from scipy import stats



T = [2.300, 2.295, 2.290  ,   2.285, 2.275, 2.280]
N = [1/60., 1/80., 1/100. ,   1/60., 1/80., 1/100.]

T_chi = [2.300, 2.295, 2.290]
T_cv  = [2.285, 2.275, 2.280]
N_ =    [1/60., 1/80., 1/100.]

L = [1/60.,1/80.,1/100.]

chi = [2.3,2.295,2.29]
c = [2.285,2.275,2.28]

#T = [2.285, 2.275, 2.280]
#N = [1/60., 1/80., 1/100.]
slope, intercept, r, p, std_err = stats.linregress(N_,T_chi)
print intercept

slope, intercept, r, p, std_err = stats.linregress(N_,T_cv)
print intercept

slope, intercept, r, p, std_err = stats.linregress(N,T)
print slope, intercept, std_err

plot(L,chi,"o",markersize=10,label=r"$\chi$")
plot(L,c,"o",markersize=10,label=r"$C_V$")
plot([0.0095,0.0174] ,[slope*0.0095 + intercept,slope*0.0174 + intercept], label="Linear fit")
axis([0.0095,0.0174,2.270,2.305])
xlabel(r"$L^{-1}$",fontsize="12")
ylabel(r"$k T_C \, J^{-1}$",fontsize="12")
legend(loc="best")
#savefig("f_reg1.png")
show()
