#include "solver.h"
#include "planet.h"
#include "lin.h"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

Solver::Solver(int num_of_planets,int num_of_iterations, double dt_, int it_per_print, int constant_sun)
{
  m = num_of_planets;
  n = num_of_iterations;
  o = it_per_print;
  dt = dt_;
  fixed_sun = constant_sun;
  half_dt = 0.5*dt; half_dt_sq = 0.5*dt*dt;
}

void Solver::Euler(Planet* p)
{
  temp_A = new Lin[m];
  tot_mass = 0;
  for (int j=0;j<m;j++)
  {
    tot_mass += p[j].r_mass();
  }

  l = 0;
  base = ".dat";
  for(int i=0;i<m+1;++i){
    std::ofstream(std::to_string(i)+base);
  }
  for (int i=0;i<n;i++)
  {
    l++;

    //resetting temp_A
    for(int j=0;j<m-fixed_sun;j++)
    {
      temp_A[j] = Lin(0,0,0);
    }

    for (int j=0;j<m-fixed_sun;j++)
    {
      for (int k=j+1;k<m;k++)
      {
        Acceleration(p,j,k);
      }
      p[j].w_pos(p[j].r_pos() + dt*p[j].r_vel());
      p[j].w_vel(p[j].r_vel() + dt*temp_A[j]);
    }
    //write to file, and computing energies etc.
    if (l == o){ Energy(p); l = 0; }
  }
  for(int i=0;i<m+1;++i){ std::ofstream(std::to_string(i)+base,std::ios::app).close(); }
  delete [] temp_A;
}

void Solver::VVerlet(Planet* p)
{
  temp_A = new Lin[m];
  tot_mass = 0;
  for (int j=0;j<m;j++)
  {
    tot_mass += p[j].r_mass();
  }

  l = 0;

  base = ".dat";
  for(int i=0;i<m+1;++i){ std::ofstream(std::to_string(i)+base); }

  //computing initial accelerations
  for(int j=0;j<m-fixed_sun;j++)
  {
    for(int k=j+1;k<m;k++)
      {
        Acceleration(p,j,k);
      }
      p[j].w_acc(temp_A[j]);
  }

  //verlet solver-loop
  for(int i=0;i<n;i++)      //iterations
  {
    l++;
    //computing positions
    for(int j=0;j<m;j++)
    {
      p[j].w_pos(p[j].r_pos() + dt*p[j].r_vel() + half_dt_sq*p[j].r_acc()); //write_pos:r_pos is now the new position
    }

    //resetting temp_A
    for(int j=0;j<m;j++){ temp_A[j] = Lin(0,0,0); }

    //computing accelerations and velocities
    for(int j=0;j<m-fixed_sun;j++)
    {
      for(int k=j+1;k<m;k++)
      {
        Acceleration(p,j,k);
      }//write_vel
      p[j].w_vel(p[j].r_vel() + half_dt*(temp_A[j]+p[j].r_acc()));
      p[j].w_acc(temp_A[j]);
    }
    //write to file, and computing energies etc.
    if (l == o){ Energy(p); l = 0; }
  }
  for(int i=0;i<m+1;++i){ std::ofstream(std::to_string(i)+base,std::ios::app).close(); }
  delete [] temp_A;
}



void Solver::VVerlet_rel(Planet* p)
{
  temp_A = new Lin[m];
  tot_mass = 0;
  for (int j=0;j<m;j++)
  {
    tot_mass += p[j].r_mass();
  }
  //operator *= is overloaded for cross-product
  temp1 = (p[0].r_pos()*=p[0].r_vel()).abs();
  L = temp1*temp1;

  l = 0;
  base = ".dat";
  for(int i=0;i<m+1;++i){ std::ofstream(std::to_string(i)+base); }
  //computing initial accelerations
  for(int j=0;j<m-fixed_sun;j++)
  {
    for(int k=j+1;k<m;k++)
      {
        temp2 = p[j].r_pos().abs();
        rel = (1.0 + 3.0*L/(temp2*temp2*c_sq));
        temp_a = ( rel*G/pow((p[j].r_pos()-p[k].r_pos()).abs(),2) )*( (p[k].r_pos()-p[j].r_pos()).unit() );
        temp_A[j] = temp_A[j] + p[k].r_mass()*temp_a;
        temp_A[k] = temp_A[k] - p[j].r_mass()*temp_a;
        //std::cout << std::setprecision(20) << (1.0 + 3*pow((p[j].r_pos()*=p[j].r_vel()).abs(),2)/(pow(p[j].r_pos().abs(),2)*c_sq)) << std::endl;
      }
      p[j].w_acc(temp_A[j]);
  }

  //verlet solver-loop
  for(int i=0;i<n;i++)      //iterations
  {
    l++;
    //computing positions
    for(int j=0;j<m;j++)
    {
      p[j].w_pos(p[j].r_pos() + dt*p[j].r_vel() + half_dt_sq*p[j].r_acc()); //write_pos:r_pos is now the new position
    }
    //std::cout << std::setprecision(100) << (1.0 + 3*pow((p[0].r_pos()*=p[0].r_vel()).abs(),2)/(pow(p[0].r_pos().abs(),2)*c_sq)) << std::endl;

    //resetting temp_A
    for(int j=0;j<m;j++){ temp_A[j] = Lin(0,0,0); }

    //computing accelerations and velocities
    for(int j=0;j<m-fixed_sun;j++)
    {
      for(int k=j+1;k<m;k++)
      {
        temp1 = (p[j].r_pos()-p[k].r_pos()).abs();
        temp_a = ( rel*G/(temp1*temp1) )*( (p[k].r_pos()-p[j].r_pos()).unit() );
        temp_A[j] = temp_A[j] + p[k].r_mass()*temp_a;
        temp_A[k] = temp_A[k] - p[j].r_mass()*temp_a;
      }//write_vel
      p[j].w_vel(p[j].r_vel() + half_dt*(temp_A[j]+p[j].r_acc()));
      p[j].w_acc(temp_A[j]);
    }
    temp1 = (p[0].r_pos()*=p[0].r_vel()).abs();
    temp2 = p[0].r_pos().abs();
    rel  = (1.0 + 3*temp1*temp1/(temp2*temp2*c_sq));
    wp = p[0].r_pos();
    if (l > 995000000){
      std::ofstream(std::to_string(0)+base, std::ios::app)
      << std::setprecision(15) << wp.X() << " " << wp.Y() << " " << wp.Z() << std::endl;
    }
  }
  for(int i=0;i<m+1;++i){ std::ofstream(std::to_string(i)+base,std::ios::app).close(); }
  delete [] temp_A;
}

void Solver::Acceleration (Planet * p,int j,int k)
{
  temp_a = ( G/pow((p[j].r_pos()-p[k].r_pos()).abs(),2) )*( (p[k].r_pos()-p[j].r_pos()).unit() );
  temp_A[j] = temp_A[j] + p[k].r_mass()*temp_a;
  temp_A[k] = temp_A[k] - p[j].r_mass()*temp_a;
}

//Computing kinetic, potential and total energy, and angular momentum.
//Prints to file.
void Solver::Energy (Planet * p)
{
    kin=0;pot=0;tot=0;ang=Lin(0,0,0);
    for(int j=0;j<m;j++) {
      wp = p[j].r_pos();
      std::ofstream(std::to_string(j)+base, std::ios::app)
      << std::setprecision(15) << wp.X() << " " << wp.Y() << " " << wp.Z() << std::endl;
      kin = kin + 0.5*p[j].r_mass()*pow(p[j].r_vel().abs(),2);
      for(int k=j+1;k<m;k++){
        pot = pot - G*p[j].r_mass()*p[k].r_mass()/(p[j].r_pos()-p[k].r_pos()).abs();
      }
    }
    tot = kin + pot;
    //computing mass center
    for (int j=0;j<m;j++){ ang = ang + p[j].r_mass()*(p[j].r_pos() *= (p[j].r_vel())); }

    std::ofstream(std::to_string(m)+base, std::ios::app)
    << std::setprecision(12) << kin << " " << pot << " " << tot << " " << ang.abs() << std::endl;

}




double Solver::r_energy(){ return tot; }
double Solver::r_ang_mom(){ return ang.abs(); }
