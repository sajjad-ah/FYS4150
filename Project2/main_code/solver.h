using namespace std;
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <stdio.h>


//function for jacobi rotation and orthogonal transformation
//of eig_vec to compute final eigenvectors
void rotate(double **A, double **eig_vec, int k, int l, int n)
{
    double s, c;
    if(A[k][l] != 0)
    {
        double t, tau;
        tau = (A[l][l] - A[k][k])/(2*A[k][l]);
        if(tau>0){
            t = 1.0/(tau + sqrt(1.0 + tau*tau));
        }
        else{
            t = -1.0/( -tau + sqrt(1.0 + tau*tau));
        }
        c = 1/sqrt(1+t*t);
        s = c*t;
    }
    else
    {
        c = 1;
        s = 0;
    }
    double a_kk, a_ll, a_ik, a_il, r_ik, r_il;
    a_kk = A[k][k];
    a_ll = A[l][l];
    //Changing matrix elements in accordance with similarity transform
    A[k][k] = c*c*a_kk - 2*c*s*A[k][l] + s*s*a_ll;
    A[l][l] = s*s*a_kk + 2*c*s*A[k][l] + c*c*a_ll;
    A[k][l] = 0;
    A[l][k] = 0;
    for(int i=0;i<n;i++)
    {
        if(i != k && i != l)
        {
            a_ik = A[i][k];
            a_il = A[i][l];
            A[i][k] = c*a_ik - s*a_il;
            A[k][i] = A[i][k];
            A[i][l] = c*a_il + s*a_ik;
            A[l][i] = A[i][l];
        }
        //computing the eigenstates from the orthogonal transformations
        r_ik = eig_vec[i][k];
        r_il = eig_vec[i][l];
        eig_vec[i][k] = c*r_ik - s*r_il;
        eig_vec[i][l] = c*r_il + s*r_ik;
    }
    return;

}
//function to compute max off-diagonal element
double max_off_diagonal(double ** A, int *k, int *l, int n)
{
    double max = 0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(fabs(A[i][j])>max){
                max=fabs(A[i][j]);
                *l=i;
                *k=j;
            }
        }
    }
    return max;
}
//function to compute eigenvalues and eigenfunction of
//A matrix using jacobi method.
double *jacobi(double **A, double **eig_vec, int n)
{
    // setting up the eigenvector matrix
    for(int i=0;i<n; i++){
        for(int j=0;j<n;j++){
            if(i==j){
                eig_vec[i][j] = 1.0;
            }
            else{
                eig_vec[i][j] = 0.0;
            }
        }
    }
    int k, l;
    double eps = 1.0e-8;
    int iter = 0;
    double max_iter = double(n) * double(n) * double(n);
    double max = max_off_diagonal(A,&k,&l,n);
    while(fabs(max)>eps && double(iter)<max_iter)
    {
        max = max_off_diagonal(A,&k,&l,n);
        rotate(A,eig_vec,k,l,n);
        iter++;
    }

    printf("Number of iterations: %d\n", iter);
    double *eig_vals = new double[n];
    for (int i=0;i<n;i++){
      eig_vals[i] = A[i][i];
    }
    return eig_vals;
}
