//Program ued for benchmarking the parallelization implementation.

using namespace std;

#include "../main_code/functions.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <random>
#include <ctime>

int main (int argc , char * argv [])
{
  ofstream outfile ;
  double start_time , end_time ;
  //srand (time(NULL)) ;

  outfile.open("outloop-nonpara.dat") ;

  mt19937_64 generat ( clock() + 4.2765664 ) ;

  int N = atof(argv[1]) ;
  double Ti = atof(argv[2]) ;
  double Tf = atof(argv[3]) ;
  double dT = atof(argv[4]) ;

  double N_sq_inv = 1/(double)(N*N) ;
  double E , E_sq , M , M_sq , M_abs , E_temp , M_temp ;
  double tE , tE_sq , tM , tM_sq , tM_abs ;
  int accepted , taccepted ;

  int ** A = mat(N) ;

  //array of precalc boltzmann coeffs (1 for dE<=0)
  double B[17];
  B[0]=1 ; B[4]=1 ; B[8]=1 ;

  //ofstream outenergy ;
  //outenergy.open(to_string(my_rank)+"energyT1.dat") ;
  int eq_cyc = 1000000 ;
  B[12]=exp(-4.0/Ti) ; B[16]=exp(-8.0/Ti) ;
  rand_init ( A , N , E_temp , M_temp , generat ) ;
  equilibrate ( A , N , E_temp , M_temp , eq_cyc , B , generat ) ;

  int n_cyc_max = 1000000 ; int n_cyc_min = 1000000 ;
  //running mc cycles
  start_time = clock() ;
  for ( int n_cyc = n_cyc_min ; n_cyc <= n_cyc_max ; n_cyc = 10*(n_cyc/8.0) )
  {
    double n_cyc_inv = 1 / (double) n_cyc ;
    //rand_init ( A , N , E_temp , M_temp , generat ) ;
      for ( double T = Ti ; T <= Tf  ; T += dT )
      {
        E_temp = M_temp = E = E_sq = M = M_sq = M_abs = 0 ;
        tE = tE_sq = tM = tM_sq = tM_abs = 0 ;
        accepted = taccepted = 0 ;
        //generating random spin matrix and initial expectation values
        //rand_init ( A , N , E_temp , M_temp , generat ) ;
        cout << T << endl ;
        init_energy ( A , N , E_temp , M_temp ) ;
        B[12]=exp(-4.0/T) ; B[16]=exp(-8.0/T) ;
        for (int k=0;k<n_cyc;k++)
        {
          metropolis ( A, N , E_temp , M_temp , B , generat , accepted ) ;
          E += E_temp ; E_sq += E_temp*E_temp ; M += M_temp ; M_sq += M_temp*M_temp ; M_abs += fabs(M_temp) ;
          //outenergy << setw(15) << setprecision(8) << E_temp << endl ;
        }
        file_write (  N_sq_inv , n_cyc_inv , T , E , E_sq , M_sq , M_abs , n_cyc , accepted , outfile ) ;
      }

  }
  outfile.close();
  //outenergy.close();
  del (A,N) ;
  end_time = clock() ;
  cout << end_time - start_time << endl ;
}
