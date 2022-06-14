//two terminal inputs are needed to run the program:
//the matrix dimension and exercise letter.
//for instance: ./main 100 d runs the program
//for exercise d with 100x100 matrix

using namespace std;
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <time.h>
#include "solver.h"

int main(int argc, char* argv[])
{
  int n = atof(argv[1]);
  int exercise = int(*argv[2]);
  int i;
  int j;
  //variables used to compute computiation time
  double time_i;
  double time_f;

  //defining matrix
  int rows[n];
  int cols[n];
  double** A = new double*[n];
  for (i = 0; i < n; i++){
    A[i] = new double[n];
  }

  double** eig_vec = new double*[n];
  for (i = 0; i < n; i++){
    eig_vec[i] = new double[n];
  }

  double pmin = 0;
  double pmax = 10;
  double h = (pmax-pmin)/n;
  double h_sq = pow(h,2);

  //adding matrix elements

  double omega = 1.0;

  //solver for exercise b
  if (exercise == 98){
    for (i=0;i<n;i++){
      for (j=0;j<n;j++){
        if (i == j){
          A[i][i] = 2/h_sq;
        }
        else if (abs(j-i) == 1){
          A[i][j] = -1/h_sq;
        }
      }
    }
  }
  //solver for electron in harmonic oscillator
  else if (exercise == 100){
    for (i=0;i<n;i++){
      for (j=0;j<n;j++){
        if (i == j){
          A[i][i] = 2/h_sq + pow((i+1)*h,2);
        }
        else if (abs(j-i) == 1){
          A[i][j] = -1/h_sq;
        }
      }
    }
  }
  //solver for two electrons in harmonic oscillator
  //with coulomb interaction
  else if (exercise == 101){
    for (i=0;i<n;i++){
      for (j=0;j<n;j++){
        if (i == j){
          A[i][i] = 2/h_sq + pow(omega,2)*pow((i+1)*h,2) + 1/(double(i+1)*h);
        }
        else if (abs(j-i) == 1){
          A[i][j] = -1/h_sq;
        }
      }
    }
  }
  //solver for two electrons in harmonic oscillator
  //without coulomb interaction
  else if (exercise == 102){
    for (i=0;i<n;i++){
      for (j=0;j<n;j++){
        if (i == j){
          A[i][i] = 2/h_sq + pow(omega,2)*pow((i+1)*h,2);
        }
        else if (abs(j-i) == 1){
          A[i][j] = -1/h_sq;
        }
      }
    }
  }

  time_i = clock();
  double *eig_val = jacobi (A,eig_vec,n);
  time_f = clock();
  cout << time_f-time_i << endl << endl;

  //finding the position of eigenvalues and eigenvectors of ground state
  int count = 100000;
  int index = 0;
  for (int i=0;i<n;i++){
    if (eig_val[i] < count){
      index = i;
      count = eig_val[i];
    }
  }

  //searcing for GS by finding wavefunction
  //without nodes
  /*double* eigvec = new double[n];
  double f = 1;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<250;j++)
    {
      if (eig_vec[j][i] < 0){
        f = eig_vec[j][i];
      }

    }
    if (f > 0){
      for (int m=0;m<n;m++){
        eigvec[m] = eig_vec[m][i];
      }
      break;
    }
    f = 1;
  }*/

  //printing eigenvector ground state
  char filename[64] = "test.dat";
  FILE *outfile = fopen(filename,"w");
  for (int i=0;i<n;i++){
    fprintf(outfile,"%f\n",eig_vec[i][index]);
    //cout << R[i][index] << endl;
  }

  //sorting the eigenvalues in increasing order
  double temp;
  for(int i=0;i<n-1;i++)
  {
    for(int j=0;j<n-i-1;j++)
    {
      if(eig_val[j]>eig_val[j+1])
      {
        temp=eig_val[j];
        eig_val[j]=eig_val[j+1];
        eig_val[j+1]=temp;
      }
    }
  }

  //printing eigenvalues
  for (int i=0;i<10;i++){
    cout << eig_val[i] << endl;
  }

}
