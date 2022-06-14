#include "planet.h"
#include "lin.h"

Planet::Planet()
{
  mass = 0;
  number = 0;
}

Planet::Planet(std::string name_,Lin r0, Lin v0,double m)
{
  name = name_;
  pos = r0;
  vel = v0;
  mass = m;
}

void Planet::w_pos(Lin r)
{
  pos = r;
}
void Planet::w_vel(Lin v)
{
  vel = v;
}
void Planet::w_acc(Lin a)
{
  acc = a;
}
Lin Planet::r_pos()
{
  return pos;
}
Lin Planet::r_vel()
{
  return vel;
}
Lin Planet::r_acc()
{
  return acc;
}
double Planet::r_mass()
{
  return mass;
}
std::string Planet::r_name()
{
  return name;
}
