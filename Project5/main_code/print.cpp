using namespace std;

#include "print.h"
#include <iomanip>

//writing matrix to file
void print_mat ( int b , double ** A , ofstream & outfile , const char * file_name )
{
  outfile.open(file_name) ;
  for ( int i = 0 ; i <= b ; i++ )
  {
    for (int j = 0 ; j <= b ; j++)  { outfile  << setw(35) << setprecision(16) << A[i][j] ; }
    outfile << endl ;
  }
  outfile.close() ;
}

//writing vector to file
void print_vec ( int b , double dx , double * vec , ofstream & outfile , const char * file_name )
{
  outfile.open(file_name) ;
  for ( int i = 0 ; i <= b ; i++ )
  {
    outfile << setw(35) << setprecision(16) << vec[i] ;
    outfile << setw(35) << setprecision(16) << dx*i << endl ;
  }
  outfile.close() ;
}
