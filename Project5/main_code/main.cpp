using namespace std ;

#include "solver.h"
#include "mat.h"
#include "print.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

void solv_1d ( int , double , double  , double , int , ofstream & ) ;
void solv_2d ( int , double , double  , double , int , ofstream & ) ;

int main ( int argc , char ** argv )
{
  int b = 50 ;
  double dx = 1/(double) b ;
  double dt = 0.25 * dx * dx ;
  double alpha = dt / ( dx * dx ) ;
  int t_cyc = 2000 ;
  double t = dt * t_cyc ;
  ofstream outfile ;
  //solv_1d ( b , dx , dt , alpha , t_cyc , outfile ) ;
  solv_2d ( b , dx , dt , alpha , t_cyc , outfile ) ;


}

void solv_1d ( int b , double dx , double dt , double alpha , int t_cyc , ofstream & outfile )
{
  Solver solv ;
  //initializing vector, first and last element is taken as boundary conditions
  double * vec = new double[b+1] ;
  for (int i=0;i<=b;i++)
  {
    vec[i] = 0 ;
  }
  vec[b] = 1 ;

  print_vec ( b , dx , vec , outfile , "init_func.dat" ) ;

  for (int i=0;i<8000;i++)
  {
    //solv.ForwardEuler( vec , b , alpha ) ;
    //solv.BackwardEuler( vec , b , alpha ) ;
    solv.CrankNicolson( vec , b , alpha ) ;
  }
  print_vec ( b , dx , vec , outfile , "final_func.dat" ) ;
  delete [] vec ;
}

void solv_2d ( int b , double dx , double dt , double alpha , int t_cyc , ofstream & outfile )
{
  Solver solv ;
  double ** A = mat(b+1) ;
  //creating initial conditions, the elements on the edges of the final_matrix
  //are taken as boundary conditions
  for (int i=1;i<b;i++)
  {
    for (int j=1;j<b;j++)
    {
      if ( i > b/4.0 && i < 3*b/4.0 && j > b/4.0 && j < 3*b/4.0 ){ A[i][j] = 1 ; }
      else { A[i][j] = 0 ; }
    }
  }
  print_mat ( b , A , outfile , "initial_matrix.dat" ) ;
  for (int i=0;i<t_cyc;i++)
  {
    solv.ForwardEuler2D( A , b , alpha ) ;
  }
  print_mat ( b , A , outfile , "final_matrix.dat" ) ;
  del (A,b+1) ;
}
