using namespace std;

#include <fstream>
#include <sstream>
#include <iostream>
#include <time.h>
#include "planet.h"
#include "lin.h"
#include "solver.h"

int main(int argc,char * argv[])
{
  int n;
  int it_per_print; //how many iterations for each time data is written to file
  int num_of_planets;
  int const_sun; //0=no, 1=yes. Sun must be placed last in input file if yes.
  double dt;
  string line;
  string name;
  int i = 0;
  double x,y,z,vx,vy,vz,mass;

  //Reading initial conditions and simulation config from file
  ifstream file(argv[1]);
  getline(file,line);
  getline(file,line);
  stringstream linestream(line);
  linestream >> n >> it_per_print >> dt >> num_of_planets >> const_sun;
  Planet * planets;
  planets = new Planet [num_of_planets];
  getline(file,line);
  getline(file,line);
  while(getline(file, line))
  {
    stringstream linestream(line);
    linestream >> name >> x >> y >> z >> vx >> vy >> vz >> mass;
    Lin pos(x,y,z), vel(vx,vy,vz);
    planets[i] = Planet(name,pos,vel,mass);
    //cout << name << " " << x << " " << y << " " << z << " " << vx << " " << vy << " " << vz << " " << mass << endl;
    i++;
  }
  file.close();
  Solver solv(num_of_planets,n,dt,it_per_print,const_sun);
  //double time_i, time_f;
  //time_i = clock();

  //solv.Euler(planets);            //solve with Euler
  solv.VVerlet(planets);            //solve with VVerlet
  //solv.VVerlet_rel(planets);      //solve with VVerlet relativistic

  //time_f = clock();
  //cout << time_f-time_i << endl;
  delete [] planets;
}



//Compile: c++ -o main main.cpp solver.cpp lin.cpp planet.cpp -std=c++11
