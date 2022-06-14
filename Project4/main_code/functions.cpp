using namespace std;

#include "functions.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <random>
#include <ctime>


void metropolis ( int ** A , int N , double & E_temp , double & M_temp , double * B , mt19937_64 & generat , int & accepted )
{
  uniform_real_distribution<double> RNG_int(0,N);
  uniform_real_distribution<double> RNG(0.0,1.0);
  int x , y , dE ;
  for (int i=0;i<N;i++)
  {
    for (int j=0;j<N;j++)
    {
      x = int ( RNG_int ( generat ) ) ;
      y = int ( RNG_int ( generat ) ) ;

      dE = 2 * A[x][y] *
      ( A[ per_ind(x-1, N) ][y] + A[per_ind(x+1, N)][y]
       + A[x][per_ind(y-1, N)] + A[x][per_ind(y+1, N)] ) ;
      double aaa = RNG ( generat ) ;
      if ( aaa <= B[dE + 8] )
      {
        A[x][y] *= -1 ;
        E_temp += dE ;
        M_temp += 2*A[x][y] ;
        accepted += 1 ;
      }
    }
  }
}

//equilibrates the system
void equilibrate ( int ** A , int & N , double & E_temp , double & M_temp , int & eq_cyc , double * B , mt19937_64 & generat )
{
  int accepted ;
  E_temp = M_temp = accepted = 0 ;
  for (int i = 0 ; i < eq_cyc/4.0 ; i++ )
  {
    metropolis ( A , N , E_temp , M_temp , B , generat , accepted ) ;
  }
}

//computes energy and magnetization
void init_energy ( int ** A , int & N , double & E_temp , double & M_temp )
{
  int counter ;
  for (int i=0;i<N;i++)
  {
    counter = N-1 ;
    for (int j=0;j<N;j++)
    {
      E_temp -= A[i][j] * A[i][counter] ;
      E_temp -= A[j][i] * A[counter][i] ;
      M_temp += A[i][j] ;
      counter = j ;
    }
  }
}

//returns periodic indices
int per_ind (int a , int N)
{
  if ( a == -1 ) { return N-1 ; }
  else if ( a == N ) { return 0 ; }
  else { return a ; }
}

//sets all spins to 1 if T < 1.5
void T_rand ( int ** A , int N , double & E_temp , double & M_temp , double & T )
{
  if ( T <= 1.5 )
  {
    for (int i=0;i<N;i++)
    {
      for (int j=0;j<N;j++)
      {
        A[i][j] = 1 ;
      }
    }
  }
}

//initializing a random matrix
void rand_init ( int ** A , int N , double & E_temp , double & M_temp , mt19937_64 & generat )
{
  uniform_real_distribution<double> RNG_int(0,2) ;
  for (int i=0;i<N;i++)
  {
    for (int j=0;j<N;j++)
    {
      A[i][j] = int ( RNG_int ( generat ) ) ;
      if ( A[i][j] == 0 ) { A[i][j] = -1 ; }
    }
  }
}


//writes expectation values to file
void file_write (  double & N_sq_inv , double & n_cyc_inv , double & T , double & E , double & E_sq , double & M_sq , double & M_abs , int & n_cyc , int & accepted , ofstream & outfile )
{
  double E_ = E*n_cyc_inv;
  double E_sq_ = E_sq*n_cyc_inv;
  double M_sq_ = M_sq*n_cyc_inv;
  double M_abs_ = M_abs*n_cyc_inv;

  double E_var = (E_sq_- E_*E_)*N_sq_inv;
  double M_var = (M_sq_ - M_abs_*M_abs_)*N_sq_inv;

  outfile << setiosflags(ios::showpoint | ios::uppercase);
  outfile << setw(15) << setprecision(8) << T;
  outfile << setw(15) << setprecision(8) << E_*N_sq_inv;
  outfile << setw(15) << setprecision(8) << E_var/(T*T);
  outfile << setw(15) << setprecision(8) << M_abs_*N_sq_inv;
  outfile << setw(15) << setprecision(8) << M_var/T;
  outfile << setw(15) << setprecision(8) << n_cyc;
  outfile << setw(15) << setprecision(8) << accepted << endl ;
}


//dynamically allocates 2D array
int ** mat ( int N )
{
  int ** A = new int * [N] ;
  for (int i=0;i<N;i++)
  {
    A[i] = new int [N] ;
    for (int j=0;j<N;j++)
    {
      A[i][j] = 0 ;
    }
  }
  return A ;
}


//deallocates 2D array
void del ( int ** A , int N )
{
  for (int i=0;i<N;i++) { delete [] A [i] ; }
  delete [] A ;
}


//print matrix to terminal
void print ( int ** A, int N )
{
  for (int i=0;i<N;i++)
  {
    for (int j=0;j<N;j++)
    {
      cout << A[i][j] << " " ;
    }
    cout << endl ;
  }
}
