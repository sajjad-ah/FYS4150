//Compile: c++ -o unit_test unit_test.cpp ../main_code/solver.cpp ../main_code/lin.cpp ../main_code/planet.cpp -std=c++11

#define CATCH_CONFIG_MAIN
#include <cmath>
#include <iostream>
#include "catch.hpp"

#include "../main_code/lin.h"
#include "../main_code/planet.h"
#include "../main_code/solver.h"

double eps = 1e-7;

double i_ang, i_energy, f_ang, f_energy;

//testing that jacobi returns correct eigen values
//for a specific 5x5 tridiagonal Toeplitz matrix
TEST_CASE( "Jacobi analytical eigenvalues" ) {
  int n = 100000;
  int it_per_print = 1000;
  int num_of_planets = 2;
  int const_sun = 0;
  double dt = 0.001;
  int i = 0;
  double x,y,z,vx,vy,vz,mass;
  Planet * planets;
  planets = new Planet [num_of_planets];
  planets[0] = Planet("sun",Lin(0,0,0),Lin(0,0,0),1);
  planets[1] = Planet("earth",Lin(1,0,0),Lin(0,6.28,0),3.00348959632e-6);

  Solver solv(num_of_planets,n,dt,it_per_print,const_sun);
  //solv.Euler(planets);
  solv.Energy(planets);
  i_energy = solv.r_energy();
  i_ang = solv.r_ang_mom();
  solv.VVerlet(planets);
  f_energy = solv.r_energy();
  f_ang = solv.r_ang_mom();
  //solv.VVerlet_rel(planets);

  //REQUIRE(b == Approx(a).epsilon(eps));
  double exact_energy = -5.934660450610923e-05;
  double exact_ang = 1.88619146648896e-05;
  REQUIRE(i_ang == Approx(exact_ang).epsilon(eps));
  REQUIRE(i_energy == Approx(exact_energy).epsilon(eps));
  REQUIRE(f_energy == Approx(i_energy).epsilon(eps));
  REQUIRE(f_ang == Approx(i_ang).epsilon(eps));
  delete [] planets;
}

//testing that max_off_diagonal returns the correct
//max off diagonal element
