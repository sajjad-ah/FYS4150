using namespace std;

#include "mat.h"
#include <iostream>

//dynamically allocates 2D array
double ** mat ( int N )
{
  double ** A = new double * [N] ;
  for (int i=0;i<N;i++)
  {
    A[i] = new double [N] ;
    for (int j=0;j<N;j++)
    {
      A[i][j] = 0 ;
    }
  }
  return A ;
}


//deallocates 2D array
void del ( double ** A , int N )
{
  for (int i=0;i<N;i++) { delete [] A [i] ; }
  delete [] A ;
}

//print matrix to terminal
void print ( double ** A, int N )
{
  for (int i=0;i<N;i++)
  {
    for (int j=0;j<N;j++)
    {
      cout << A[i][j] << " " ;
    }
    cout << endl ;
  }
}
