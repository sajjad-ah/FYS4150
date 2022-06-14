using namespace std;

#define CATCH_CONFIG_MAIN
#include <iostream>
#include <cmath>

#include "catch.hpp"

#include "../main_code/solver.h"

double eps = 0.1 ;

TEST_CASE( "" )
{
  double a ;
  int b = 10 ;
  double dx = 1/(double) b ;
  double dt = 0.4 * dx * dx ;
  double alpha = dt / ( dx * dx ) ;
  int t_cyc = 10 ;
  double * vec1 = new double[b+1] ;
  double * vec2 = new double[b+1] ;
  double * vec3 = new double[b+1] ;
  for (int i=0;i<=b;i++)
  {
    vec1[i] = 0 ;
    vec2[i] = 0 ;
    vec3[i] = 0 ;
  }
  vec1[b] = 1 ;
  vec2[b] = 1 ;
  vec3[b] = 1 ;
  Solver solv ;

  for (int i=0;i<10;i++)
  {
    solv.ForwardEuler( vec1 , b , alpha ) ;
  }

  for (int i=0;i<10;i++)
  {
    solv.BackwardEuler( vec2 , b , alpha ) ;
  }

  for (int i=0;i<10;i++)
  {
    solv.CrankNicolson( vec3 , b , alpha ) ;
  }

  REQUIRE(0.07709975801630 == Approx(vec1[5]).epsilon(eps));
  REQUIRE(0.28884436449600 == Approx(vec1[7]).epsilon(eps));
  REQUIRE(0.07709975801630 == Approx(vec2[5]).epsilon(eps));
  REQUIRE(0.28884436449600 == Approx(vec2[7]).epsilon(eps));
  REQUIRE(0.07709975801630 == Approx(vec3[5]).epsilon(eps));
  REQUIRE(0.28884436449600 == Approx(vec3[7]).epsilon(eps));
}
