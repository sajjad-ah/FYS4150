#include "solver.h"
#include "mat.h"
#include <iostream>

Solver::Solver (){}


void Solver::ForwardEuler ( double * u , int n , double alpha )
{
  double beta = u[0] ;
  double gamma ;
  for (int i=1;i<n;i++)
  {
    gamma = u[i] ;
    u[i] = alpha * beta + (1-2*alpha)*u[i] + alpha * u[i+1] ;
    beta = gamma ;
  }
}


void Solver::BackwardEuler ( double * r , int n , double alpha )
{
  tridiag (-alpha, 1+2*alpha, -alpha , r , n+1) ;
}

void Solver::CrankNicolson ( double * u , int n , double alpha )
{
  double beta = u[0] ;
  double gamma ;
  for (int i=1;i<n;i++)
  {
    gamma = u[i] ;
    u[i] = alpha * beta + (2-2*alpha)*u[i] + alpha * u[i+1] ;
    beta = gamma ;
  }
  tridiag (-alpha, 2+2*alpha, -alpha , u , n+1) ;
}

void Solver::ForwardEuler2D ( double ** A , int n , double alpha )
{
  double ** B = mat ( n+1 ) ;
  for (int i=1;i<n;i++)
  {
    for (int j=1;j<n;j++)
    {
      B[i][j] = A[i][j] + alpha * ( A[i+1][j] + A[i-1][j] + A[i][j+1] + A[i][j-1] - 4*A[i][j] ) ;
    }
  }
  for (int i=1;i<n;i++)
  {
    for (int j=1;j<n;j++)
    {
      A[i][j] = B[i][j] ;
    }
  }
  del (B,n+1) ;
}


//trdiagonal matrix solver
void Solver::tridiag( double a, double b, double c, double *r, int n )
{
  double bet, *gam, *u;
  gam = new double[n];
  u = new double[n];
  u[0] = r[0] ; u[n-1] = r[n-1] ;
  bet = b;
  // forward substitution
  u[1]=r[1]/bet;
  for (int i=2;i<n-1;i++)
  {
      gam[i] = c/bet;
      bet = b - a*gam[i];
      u[i] = (r[i] - a*u[i-1])/bet;
  }
  //std::cout << gam[n-1] << std::endl ;
  gam[n-1] = c/bet ;
  // backward substitution
  for (int i=n-2; i>=1; i--) {u[i] -= gam[i+1]*u[i+1];}
  for (int i=1; i<n-1; i++) {r[i] = u[i] ; }
  delete [] gam;
  delete [] u;
}
