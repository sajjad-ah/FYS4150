import matplotlib.pyplot as plt


n = [2,3,4,5,6,7]
E = [-2.0000000,-1.9860000,-1.9964000,-1.9955600,-1.9958580,-1.9960120]

A = [-1.9959821,-1.9959821,-1.9959821,-1.9959821,-1.9959821,-1.9959821]

plt.plot(n,E,label='Numerical')
plt.plot(n,A,label='Analytical')
plt.xlabel(r"log$_{10}$(MC cycles)")
plt.ylabel(r"$\langle \mathscr{E} \rangle$",size=15)
plt.legend(loc="best")
#plt.savefig("b_plot.png")
plt.show()
