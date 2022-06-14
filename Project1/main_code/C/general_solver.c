using namespace std;

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>

int main (int argc, char* argv[])
{
  int n = atof(argv[1]);
  int i = 0;                //iteration
  int x0 = 0;
  double xn  =  1;
  double *e = new double[n+1];              //off-diagonal
  double *dt = new double[n+1];              //diagonal
  double *u  = new double[n+1];              //solutions
  double *ft = new double[n+1];             //h**2*f
  double c;
  double d = 2;
  double h = (xn-x0)/(n);

  //double *x = new double[100]

  //adding diagonal elements
  for (i=0; i<=n;i++){
    dt[i] = 2;
  }

  //adding off-diagonal elements
  for (i=0;i<=n;i++){
    e[i] = -1;
  }

  //adding elements to the inhomogenous term
  for (i=0; i<n; i++){
    ft[i] = pow(h,2)*100*exp(-10*h*i);
  }

  dt[1] = d;

  for (i=2; i<n; i++){
    c = e[i-1]/dt[i-1];
    dt[i] = dt[i] - e[i-1]*c;
    ft[i] = ft[i] - ft[i-1]*c;
  }

  u[n-1] = ft[n-1]/dt[n-1];

  for (i=n-2; i>0; i--){
    u[i] = (ft[i] - e[i]*u[i+1])/dt[i];
  }

  //writing x and u to file
//*
  ofstream file;
  file.open("results.dat");
  for (i=0;i<n+1;i++){
    file << u[i] << " " << i*h << endl;
  }
  file.close();
//*

  //Printing relative error
  int num = n/2.0;
  double k = u[num];
  double l = 1.0-(1.0-exp(-10.0))*(h*num) - exp(-10.0*h*num);

  cout << setprecision(12) << abs((k-l)/l) << endl << h << endl;



  delete [] dt;
  delete [] u;
  delete [] ft;

}
