using namespace std;

#include "mpi.h"
#include "functions.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <random>
#include <ctime>


int main (int argc , char * argv [])
{
  int my_rank ; int numprocs ;

  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);

  ofstream outfile ;
  if ( my_rank == 0 && argc > 1 )
  {
    outfile.open("outfile.dat") ;
  }


  mt19937_64 generat ( clock() + my_rank*4.2765664 ) ;

  //matrix size, initial and final T, and dT as terminal input
  int N = atof(argv[1]) ;
  double Ti = atof(argv[2]) ;
  double Tf = atof(argv[3]) ;
  double dT = atof(argv[4]) ;

  double N_sq_inv = 1/(double)(N*N) ;
  double E , E_sq , M , M_sq , M_abs , E_temp , M_temp ;
  double tE , tE_sq , tM , tM_sq , tM_abs ;
  int accepted , taccepted ;

  int ** A = mat(N) ;

  //array of precalculated boltzmann coefficients (1 for dE<=0)
  double B[17];
  B[0]=1 ; B[4]=1 ; B[8]=1 ;

  //ofstream outenergy ; ////used if energies after each MC cycles is to be written to file
  //outenergy.open(to_string(my_rank)+"energyT1.dat") ;

  //equilibrating the system
  int eq_cyc = 1000000 ;
  B[12]=exp(-4.0/Ti) ; B[16]=exp(-8.0/Ti) ;
  rand_init ( A , N , E_temp , M_temp , generat ) ;
  equilibrate ( A , N , E_temp , M_temp , eq_cyc , B , generat ) ;

  //determining min and max number of MC cycles
  int n_cyc_max = 1000000 ;
  int n_cyc_min = 1000000 ;

  double start_time , end_time ;
  start_time = clock() ;
  //running mc cycles
  for ( int n_cyc = n_cyc_min ; n_cyc <= n_cyc_max ; n_cyc = 10*(n_cyc/8.0) )
  {
    double n_cyc_inv = 1 / (double) n_cyc ;
    int no_intervalls = n_cyc / numprocs;
    int myloop_begin = my_rank * no_intervalls + 1 ;
    int myloop_end = ( my_rank + 1 ) * no_intervalls ;
    //rand_init ( A , N , E_temp , M_temp , generat ) ;
    if ( (my_rank == numprocs-1) && ( myloop_end < n_cyc) ) myloop_end = n_cyc ;
    {
      for ( double T = Ti ; T <= Tf  ; T += dT )
      {
        E_temp = M_temp = E = E_sq = M = M_sq = M_abs = 0 ;
        tE = tE_sq = tM = tM_sq = tM_abs = 0 ;
        accepted = taccepted = 0 ;
        //generating random spin matrix and initial expectation values
        //rand_init ( A , N , E_temp , M_temp , generat ) ;
        cout << T << endl ;
        init_energy ( A , N , E_temp , M_temp ) ;
        B[12]=exp(-4.0/T) ; B[16]=exp(-8.0/T) ;

        for (int k=myloop_begin;k<=myloop_end;k++)
        {
          metropolis ( A, N , E_temp , M_temp , B , generat , accepted ) ;
          E += E_temp ; E_sq += E_temp*E_temp ; M += M_temp ; M_sq += M_temp*M_temp ; M_abs += fabs(M_temp) ;
          //outenergy << setw(15) << setprecision(8) << E_temp << endl ;
        }
        MPI_Reduce ( & E , & tE , 1 , MPI_DOUBLE , MPI_SUM , 0 ,MPI_COMM_WORLD ) ;
        MPI_Reduce ( & E_sq , & tE_sq , 1 , MPI_DOUBLE , MPI_SUM , 0 ,MPI_COMM_WORLD ) ;
        MPI_Reduce ( & M , & tM , 1 , MPI_DOUBLE , MPI_SUM , 0 ,MPI_COMM_WORLD ) ;
        MPI_Reduce ( & M_sq , & tM_sq , 1 , MPI_DOUBLE , MPI_SUM , 0 ,MPI_COMM_WORLD ) ;
        MPI_Reduce ( & M_abs , & tM_abs , 1 , MPI_DOUBLE , MPI_SUM , 0 ,MPI_COMM_WORLD ) ;
        MPI_Reduce ( & accepted , & taccepted , 1 , MPI_INT , MPI_SUM , 0 ,MPI_COMM_WORLD ) ;
        if ( my_rank == 0 )
        {
        file_write (  N_sq_inv , n_cyc_inv , T , tE , tE_sq , tM_sq , tM_abs , n_cyc , taccepted , outfile ) ;
        }
      }
    }
  }
  outfile.close() ;
  //outenergy.close();
  del (A,N) ;
  MPI_Finalize ();
  end_time = clock() ;
  cout << end_time - start_time << endl ;
}
