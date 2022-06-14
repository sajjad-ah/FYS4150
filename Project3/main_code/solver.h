#ifndef SOLVER_H
#define SOLVER_H
#include "planet.h"
#include "lin.h"

class Solver
{
private:
  std::string base;
  int n;
  int m;
  int l; //counter for filewriting
  int o; //value of l when printing to file
  int fixed_sun; //includes sun acceleration if value is 0, and excludes of value is 1
  double dt;
  double tot_mass;
  double G = 39.478417604357;         //4*pi**2
  double c_sq = 3999262994.62;
  double half_dt, half_dt_sq;
  Lin ang; //angular momentum
  Lin wp;
  Lin temp_a;
  Lin * temp_A;
  double L, rel; //used for relativistic correction
  double temp1,temp2; //for computation of squared values
  double kin,pot,tot;
public:
  Solver(int num_of_planets,int num_of_iterations,double dt_,int it_per_print,int constant_sun);
  void Euler(Planet* p);
  void VVerlet(Planet* p);
  void VVerlet_rel(Planet* p);
  void Energy(Planet* p);
  void Acceleration(Planet*p,int j, int k);
  double r_energy();
  double r_ang_mom();
};


#endif
