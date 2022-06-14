using namespace std;

#define CATCH_CONFIG_MAIN
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <random>
#include <ctime>
#include "catch.hpp"

#include "../main_code/functions.h"

double eps = 0.1 ;

TEST_CASE( "" )
{
  int N = 2 ;
  int ** A = mat(N) ;
  A[0][0] = A[0][1] = A[1][0] = A[1][1] = 1 ;
  double T = 1.0 ;
  int accepted = 0 ;
  int n_cyc = 1000000 ; double E_temp , M_temp , E , E_sq , M , M_sq , M_abs ;
  E_temp = M_temp = E = E_sq = M = M_sq = M_abs = 0 ;
  double n_cyc_inv = 1 / (double) n_cyc ;
  double N_sq_inv = 1/(double)(N*N) ;
  double B[17] ;
  B[0]=1 ; B[4]=1 ; B[8]=1 ; B[12]=exp(-4.0/T) ; B[16]=exp(-8.0/T) ;

  init_energy ( A , N , E_temp , M_temp ) ;

  mt19937_64 generat ( 0 ) ;
  for (int i = 0 ; i < n_cyc ; i++)
  {
    metropolis ( A, N , E_temp , M_temp , B , generat , accepted ) ;
    E += E_temp ; E_sq += E_temp*E_temp ; M += M_temp ; M_sq += M_temp*M_temp ; M_abs += fabs(M_temp) ;
  }
  double E_ = E * n_cyc_inv ;
  double E_sq_ = E_sq * n_cyc_inv ;
  double M_sq_ = M_sq * n_cyc_inv ;
  double M_abs_ = M_abs * n_cyc_inv ;

  double E_var = (E_sq_- E_*E_) * N_sq_inv ;
  double M_var = (M_sq_ - M_abs_*M_abs_) * N_sq_inv ;

  REQUIRE(-1.9959821 == Approx(E_*N_sq_inv).epsilon(eps));
  REQUIRE(0.032082332 == Approx(E_var/(T*T)).epsilon(eps));
  REQUIRE(0.998660733 == Approx(M_abs_*N_sq_inv).epsilon(eps));
  REQUIRE(0.0040107395 == Approx(M_var/T).epsilon(eps));

  del (A,N) ;
}
