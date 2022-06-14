#ifndef SOLVER_H
#define SOLVER_H


class Solver
{

private:

public:
  Solver () ;
  void ForwardEuler ( double * u , int n , double alpha ) ;
  void ForwardEuler2D ( double ** A , int n , double alpha ) ;
  void BackwardEuler ( double * r , int n ,  double alpha ) ;
  void CrankNicolson ( double * u , int n , double alpha ) ;
  void tridiag(double a, double b, double c, double *r, int n) ;
} ;


#endif
