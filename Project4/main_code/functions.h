#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <random>
#include <ctime>


void metropolis ( int ** A , int N , double & E_temp , double & M_temp , double * B , mt19937_64 & generat , int & accepted ) ;

void equilibrate ( int ** A , int & N , double & E_temp , double & M_temp , int & eq_cyc , double * B , mt19937_64 & generat ) ;

void init_energy ( int ** A , int & N , double & E_temp , double & M_temp ) ;

int per_ind (int a , int N) ;

void T_rand ( int ** A , int N , double & E_temp , double & M_temp , double & T ) ;

void rand_init ( int ** A , int N , double & E_temp , double & M_temp , mt19937_64 & generat ) ;

void file_write (  double & N_sq_inv , double & n_cyc_inv , double & T , double & E , double & E_sq , double & M_sq , double & M_abs , int & n_cyc , int & accepted , ofstream & outfile ) ;

int ** mat ( int N ) ;

void del ( int ** A , int N ) ;

void print ( int ** A, int N ) ;

#endif
