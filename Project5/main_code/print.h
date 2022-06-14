#ifndef PRINT_H
#define PRINT_H

#include <fstream>

void print_mat ( int b , double ** A , ofstream & outfile , const char * file_name ) ;

void print_vec ( int b , double dx , double * vec , ofstream & outfile , const char * file_name ) ;


#endif
