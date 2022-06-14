#include <cmath>
#include <iomanip>
#include <iostream>
#include "lin.h"

Lin::Lin ()
{
  x = 0; y = 0; z = 0;
}

Lin::Lin (double x0, double y0, double z0)
{
  x = x0; y = y0; z = z0;
}

double Lin::X() const
{
  return x;
}
double Lin::Y() const
{
  return y;
}
double Lin::Z() const
{
  return z;
}

double Lin::abs () const
{
  return sqrt(x*x + y*y + z*z);
}

Lin Lin::unit ()
{
  norm = sqrt(x*x+y*y+z*z);
  return Lin (x/norm, y/norm, z/norm);
}

Lin& Lin::operator= (const Lin& c)
{
   x = c.X();
   y = c.Y();
   z = c.Z();
   return *this;
}

void Lin::read() const
{
  std::cout << std::setprecision(9) << x << " " << y << " " << z << std::endl;
}
