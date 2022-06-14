using namespace std;

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>

int main(int argc, char *argv[])
{

  int j;
  int n=atof(argv[1]);
  double *f = new double[n];
  double *i = new double[n];
  double *b = new double[(i+1)/n];
  double *a = new double[(i-1)/n];
  double x, b;

  //TIMESTART

  for(j=1;n;j++){
    f[j] = f[j] + a[j]*f[j-1];
  }

  x = b;
  x[-1] = f[-1]/b[-1];
  for(j=n-2;j>0;j--){
    x[j] = a[j+1]*(f[j]+x[j+1]);
  }

  //TIMESTOP

  delete [] a;
  delete [] b;
  delete [] i;
  delete [] f;

}
