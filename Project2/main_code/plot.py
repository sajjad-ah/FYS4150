import matplotlib.pyplot as plt
import numpy as np


y = np.array([31817,41009,47521,52336,56564,60400,63577,66317,68833,71026,73125,75129,77078,78977,80638,82107,83500,84791,86132,87376]) # number of iterations
x = [1,2,3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,16,17,18,19,20] # negative logarithm, 1.0e-3, 1.0e-4, ...
y=y**3


y1 = [16472, 66317, 149368, 268516, 416657] # number of iterations
x1 = [10000, 40000, 90000, 160000, 250000] # matrix size, 100*100, 200*200, ...


plt.plot(x1,y1,label="Number of matrix elements")
plt.xlabel(r"N$\times$N")
plt.ylabel("Number of iterations")
plt.legend()
plt.savefig("iterations_vs_elements.png")
plt.show()
