using namespace std;

#include <iostream>
#include <cmath>
#include "mpi.h"
#include "print.h"
#include "mat.h"

int main (int argc , char * argv [])
{
  int b = 50 ;
  double dx = 1/(double) b ;
  double ** A = mat(b+1) ;
  int t_cyc = 250;
  double dt = 0.2 * dx * dx ;
  double t = dt * t_cyc ;
  int my_rank ; int numprocs ;
  ofstream outfile ;

  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);

  int n_cyc = 1000 ;

  int no_intervalls = n_cyc / numprocs;
  int myloop_begin = my_rank * no_intervalls + 1 ;
  int myloop_end = ( my_rank + 1 ) * no_intervalls ;
  if ( (my_rank == numprocs-1) && ( myloop_end < n_cyc) ) myloop_end = n_cyc ;
  if ( (my_rank == 0) && ( myloop_begin == 0) ) myloop_begin = 1 ;

  double count = 0 ;
  double tcount = 0 ;
  double x = 1/3.9 ;
  double y = 1/3.9 ;

  for (int i=0;i<b;i++)
  {
    x = i*dx ;
    for (int j=0;j<b;j++)
    {
      y = j*dx ;
      for (int m=myloop_begin;m<=myloop_end;m++)
      {
        for (int n=1;n<=n_cyc;n++)
        {
          count += sin(m*M_PI*x)*sin(n*M_PI*y)*(16.0/(M_PI*M_PI*m*n))*
          sin(M_PI*m/4.0)*sin(M_PI*m/2.0)*sin(M_PI*n/4.0)*sin(M_PI*n/2.0)*
          exp(-((m*M_PI)*(m*M_PI)+(n*M_PI)*(n*M_PI))*t) ;
        }
      }
      MPI_Reduce ( & count , & tcount , 1 , MPI_DOUBLE , MPI_SUM , 0 ,MPI_COMM_WORLD ) ;
      if (my_rank == 0) { A[i][j] = tcount ; }
      count = tcount = 0 ;
    }
  }
  print_mat ( b , A , outfile , "analytical_tcyc10.dat" ) ;
  MPI_Finalize ();
}
