#include <iostream>
#include <armadillo>
#include <cmath>
#include <time.h>

using namespace std;
using namespace arma;


int main(int argc, char* argv[])
{
  int n = atof(argv[1]);
  double h = (1-0)/(n+1);
  mat A = randu<mat>(n,n);
  mat b = randu<mat>(n,1);


  //filling inhomogenous term
  for (int i=0; i<n; i++){
    b(i,0) = pow(h,2)*100*exp(-10*h*(i+1));
  }

  //creating matrix
  for (int i=0;i<n;i++){
    for (int j=0;j<n;j++){
      if(i == j){
        A(i,j) = 2;
      }
      else if(abs(i-j) == 1){
        A(i,j) = -1;
      }
      else{
        A(i,j) = 0;
      }
    }
  }

  //solving equations with LU and measuring time
  double time_i;
  double time_f;
  time_i = clock();
  vec u(n);
  u = solve(A,b);
  time_f = clock();
  cout << time_f-time_i << endl;
}

//compile: g++ lu.c -o prog -O2 -larmadillo -llapack -lblas
