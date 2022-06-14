#ifndef PLANET_H
#define PLANET_H
#include "lin.h"
#include <string>

class Planet
{
private:
  std::string name;
  int number;
  double mass;
  Lin pos, vel, acc;
public:
  Planet();
  Planet(std::string name_,Lin r0,Lin v0,double m);
  void w_pos(Lin r);
  void w_vel(Lin v);
  void w_acc(Lin v);
  Lin r_pos();
  Lin r_vel();
  Lin r_acc();
  double r_mass();
  std::string r_name();
};

#endif
