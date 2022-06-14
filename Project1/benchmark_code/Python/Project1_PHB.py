"""
Created on Mon Sep  3 11:41:40 2018
@author: phb
"""
import numpy as np
import matplotlib.pyplot as plt
import time
from scipy.sparse import diags # using diags to from scipi to make a tridiagonalmatrix. 
import scipy.linalg as linalg # linalg LU solver fra scipi

def Tridiagsolver(a,b,c,d): # general solver for tridagonal matrix
    # a = lower diagonal vector
    # b = diagonal vector
    # c = upper diagonal vector
    # d = "right-side" vector
    
    N = len(d)  
    dc = np.array(d)    #copying dc

    t_start = time.time()     # start timing here
    
    for i in range(1,N): #forward substitution. 
        alpha = a[i-1]/b[i-1]
        b[i] = b[i] - alpha * c[i-1] 
        dc[i] = dc[i] - alpha * dc[i-1]
    
    x = b
    x[-1] = dc[-1]/b[-1] 
        
    for j in range(N-2,-1,-1): #backward substitution 
        x[j] = ( dc[j] - c[j]*x[j+1] )/b[j]
        
    time_std = time.time() - t_start     # stop timing here. 
    
    del a,b,c,dc
    
    return x , time_std

def Speedy_Tridiagsolver(f): #the speedy version for this spesific case
    # Precalculating diagonale elements after forw.substitution.
    # writes the result in to a file. 
    
    n = len(f)
    i = np.array(range(1,n+1),float)
    b = np.array((i+1)/i,float)
    a = np.array((i-1)/i,float)
    fc = np.array(f) #copying fc
    
    t_start = time.time()     # start timing here


    for j in range(1,n): #forward substitution
        fc[j] = fc[j] + a[j]*fc[j-1]
    
    x = b
    x[-1] = fc[-1]/b[-1]  
    
    for il in range(n-2, -1, -1): # backward substitution    
        x[il] = a[il+1]*(fc[il] + x[il+1])
        
    time_speedy = time.time() - t_start    # stop timing here 
    
    del a, b, n, i,fc
    
    return x, time_speedy

def LU_solver_speedtest(p,f):
    
    #Creating the matrix:
    n = 10**p
    k = np.array([-1.*np.ones(n-1,float),2.*np.ones(n,float),-1.*np.ones(n-1,float)])
    offset = [-1,0,1]
    A = diags(k,offset).toarray()
        
    fc = np.array(f) # copying f(x)
    
    start_time_1 = time.time() #starting timing.
    LU = linalg.lu_factor(A)
    x_LU = linalg.lu_solve(LU,fc) 
    time_LU = time.time() - start_time_1 #stop timing
    
    del A
    
    return x_LU, time_LU

def speedtest(p): # speedtest from 10**1 up to 10**p meshpoints
    
    for i in range(1, p+1):
        
        print('-----------10^%d matrix: -----------' % i )
        n = 10**i         
        h = 1/(n+1)
        x = np.linspace(h,1-h,n,)# x-values with space h
        f = h**2 * (100 * np.exp(-10 * x)) # matrix of values of f.
        
        #Timing speedy
        u_speedy, time_speedy = Speedy_Tridiagsolver(f) 
        del u_speedy
        print ('time_speedy=',  time_speedy)      

        #Timing standard
        a = np.full(n,-1,float)
        b = np.full(n,2,float)     
        u_std, time_std =  Tridiagsolver(a,b,a,f) 
        del u_std
        print ('time_std=' , time_std)
        
        #Timing LU
        u_LU, time_LU = LU_solver_speedtest(i,f) 
        print ('time_LU=' , time_LU)
        print('')
        
        #Difference:
        print ('---- difference between the speedy solver ------')
        print ('LU:  ' , (time_LU - time_speedy))
        print ('Standard: ' , (time_std - time_speedy))
        print ('')
#1c
def speedtest_speedy_vs_std(p): # speedtest from 10**1 up to 10**p meshpoints
    
    print('Speedy solver vs standard solver')
    
    for i in range(5, p+1):
        print('-----------10^%d matrix: -----------' % i )
        n = 10**i         
        h = 1/(n+1)
        x = np.linspace(h,1-h,n,)# x-values with space h
        
        f = h**2 * (100 * np.exp(-10 * x)) # matrix of values of f.
        
        #Timing speedy:
        u_speedy, time_speedy = Speedy_Tridiagsolver(f) #Timing speedy
        del u_speedy
        print ('time_speedy=',  time_speedy) 
        
        #Timing standard:
        a = np.full(n,-1,float)
        b = np.full(n,2,float)  
        u_std, time_std =  Tridiagsolver(a,b,a,f) #timing standard
        del u_std
        
        #Difference
        print ('time_std=' , time_std)
        print('')
        print ('---- difference between the speedy solver ------')
        print ('Standard: ' , (time_std - time_speedy))
        print ('')
    
#1d
def Main_compare(p): 
    
    relativ_error_max = np.zeros(p)
    
    for i in range(1,p+1):
        print('-----------10^%d matrix --------- ' % i )
        
        n = 10**i
        x = np.linspace(0,1,n,)# x-values with space h
        h = 1/(n+1) #stepsize
        x = np.linspace(h,1-h,n,)# x-values with space h

        f = h**2 * (100 * np.exp(-10 * x)) 
        u = 1. - (1.-np.exp(-10.))*x - np.exp(-10.*x) #analytical values. 

        v_s , time_speedy = Speedy_Tridiagsolver(f) 
        del time_speedy 
        
        #computing the relativ error.
        relativ_error = np.abs( (v_s - u)/u )
        relativ_error_max[i-1] = np.max(relativ_error)
        
        print('rel_max = ', relativ_error_max[i-1]) 
        
        #ploting u and v
        plt.figure()
        plt.plot(x, v_s, '-b', label = 'u aprox')
        plt.plot(x, u,'-r', label = 'u exact')
        plt.xlabel('x')
        plt.ylabel('u')
        #plt.savefig('plot_u'+str(i)) #saving plot
        plt.legend(loc = 'upper right')
        plt.show()
        
        
        #Ploting relativ error for each mesh point
        plt.figure()
        plt.xlabel('x')
        plt.ylabel('Relativ error')    
        plt.plot(x,abs(v_s - u)/u, label = 'relativ error')
        plt.legend(loc = 'upper left')
        #plt.savefig('plot_error'+str(i))
        plt.show()
        del n, x, h, f, u
        
    #ploting the relativ error as a function of log(n)
    print('----Relativ Error-----')
    plt.figure()
    plt.title('Log plot of Relativ error') 
    plt.xlabel('log(n)')
    plt.ylabel('log(Relativ_error)')
    plt.plot(range(1,p+1), np.log(relativ_error_max ))
    #plt.savefig('relativ_error') #saving plot
    plt.show()

def main():   
    speedtest(4)
    speedtest_speedy_vs_std(6)
    Main_compare(7) 
    
main()
    

