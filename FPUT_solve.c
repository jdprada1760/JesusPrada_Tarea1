// This code solves Fermi-Pasta-Ulam-Tsingou differential equation for 
// a given inital condition using leapfrog. Parameters are defined below.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <mpi.h>

/*  
 *  PROBLEM CONSTANTS
 *  N     -> Number of spring nodes
 *  beta  -> Problem parameter
 *  dt    -> Time of integration
 *  np    -> Number of procs to use
 *  
 */
int N = 1024, np = 4;
double beta = 0.3, dt = 0.001;

/*  
 *  PROBLEM FUNCTIONS
 *  
 */
void ini_x(double* vec);
void update_v(double* xx, double ** vv, double ddt);
void update_x(double* vv, double ** xx, double ddt);

int main(){
	// Indexes and temp variables
	int i,j;
	
	// Number of iterations
	int nit = 100*N;

	// Mem Alloc for position x and velocity v **** Paralelization ****
	double* x = malloc(N*sizeof(double));
	double* v = malloc(N*sizeof(double));
	ini_x(x);
	
	for( i = 0; i < N; i++ ){
		
	}
	return 0;
}



/*
 *  Defines the initial condition for the x vector and (zero) for the initial velocity vector
 *
 */
void ini_x(double* xx, double* vv){
	int i;
	for( i = 0; i < N; i++ ){
		xx[i] = sin(2*M_PI*i/(N-1));
		vv[i] = 0;
	}
}

/*
 *  Updates velocity given the position and the finite difference ddt
 *
 */
void update_v(double* xx, double ** vv, double ddt){
	int i;
	// Actualizes vv
	for( i = 1; i < N-1; i++ ){
		// Acceleration is defined as the term multiplying ddt
		vv[i] = vv[i]+(ddt)*(x[i+1] + x[i-1] - 2*x[i] + beta*(pow(x[i+1]-x[i],3) - pow(x[i]-x[i-1],3)));
	}
}

/*
 *  Updates position given the previous velocity and the finite difference ddt
 *
 */
void update_x(double* xx, double ** vv, double ddt){
	int i;
	// Actualizes xx
	for( i = 1; i < N-1; i++ ){
		xx[i] = xx[i]+ddt*vv[i];
	}
	//return vec;
}
