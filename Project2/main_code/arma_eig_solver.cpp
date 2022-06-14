#include <iostream>
#include <cmath>
#include <cstdlib>
#include <armadillo>
#include <time.h>
#include "solver.h"

using namespace std;
using namespace arma;

int main (int argc, char* argv[])
{
  int n = atof(argv[1]);
  mat A(n,n);
  cx_vec eig_val;
  cx_mat eig_vec;
  double pmin = 0;
  double pmax = 10;
  double h = (pmax-pmin)/n;
  double h_sq = pow(h,2);
  double omega = 1.0;
  double time_i;
  double time_f;

  for (int i=0;i<n;i++){
    for (int j=0;j<n;j++){
      if (i == j){
        A(i,i) = 2/h_sq;
      }
      else if (abs(j-i) == 1){
        A(i,j) = -1/h_sq;
      }
    }
  }

  time_i = clock();
  eig_gen(eig_val, eig_vec, A);
  time_f = clock();
  cout << time_f-time_i << endl << endl;

  for (int i=0;i<n;i++){
    cout << eig_val(i) << endl;
  }

  /*
  for (int i=0;i<n;i++){
    for (int j=0;j<n;j++){
      cout << A(i,j) << " ";
    }
    cout << endl;
  }
  */
}

//Compile: g++ arma_eig_solver.cpp -o arma_eig_solver -O2 -larmadillo -llapack -lblas
