//to compile and make executable:
//c++ -o unit_test unit_test.cpp -std=c++11

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
//#include <iostream>
#include <cmath>
#include "catch.hpp"
#include "../main_code/solver.h"

double eps = 0.0001;

//testing that jacobi returns correct eigen values
//for a specific 5x5 tridiagonal Toeplitz matrix
TEST_CASE( "Jacobi analytical eigenvalues" ) {
  int n = 5;
  double d = 2.0/1.4;
  double a = -1.0;
  int rows[n];
  int cols[n];
  //creating matrices for input in jacobi
  double** A = new double*[n];
  for (int i = 0; i < n; i++){
    A[i] = new double[n];
  }
  double** R = new double*[n];
  for (int i = 0; i < n; i++){
    R[i] = new double[n];
  }
  //adding matrix elements
  for (int i=0;i<n;i++){
    for (int j=0;j<n;j++){
      if (i == j){
        A[i][i] = d;
      }
      else if (abs(j-i) == 1){
        A[i][j] = a;
      }
    }
  }

  //computing analytical eigenvaluess
  double* lambda = new double[5];
  for (int i=0;i<n;i++){
    double k = M_PI;
    lambda[i] = d+2*a*cos((i+1)*k/(n+1));
  }
  double *eig = jacobi (A,R,n);
  REQUIRE(eig[0] == Approx(lambda[3]).epsilon(eps));
  REQUIRE(eig[1] == Approx(lambda[1]).epsilon(eps));
  REQUIRE(eig[2] == Approx(lambda[4]).epsilon(eps));
  REQUIRE(eig[3] == Approx(lambda[0]).epsilon(eps));
  REQUIRE(eig[4] == Approx(lambda[2]).epsilon(eps));
}

//testing that max_off_diagonal returns the correct
//max off diagonal element
TEST_CASE( "Maxx off diagonal" ) {
  int n = 5;
  //creating matrices for input in max_off_diagonal
  int rows[n];
  int cols[n];
  double** A = new double*[n];
  //adding matrix elements for the test
  for (int i = 0; i < n; i++){
    A[i] = new double[n];
  }
  for (int i=0;i<n;i++){
    for (int j=0;j<n;j++){
      A[i][j] = 0.12*5 + 5.5*i*j -0.3*pow(i*j,2);
    }
  }
  A[1][3] = -25.5;
  A[3][1] = -25.5;
  int k = 0;
  int l = 0;
  double max = max_off_diagonal(A,&k,&l,n);
  REQUIRE(max == 25.5);
  REQUIRE(k == 3);
  REQUIRE(l == 1);
}
