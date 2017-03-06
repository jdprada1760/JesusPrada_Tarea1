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
int N = 64, np = 4;
double beta = 1.0, dt = 0.005;

// Filenames etc
FILE* Ek;
FILE* chain;

/*  
 *  PROBLEM FUNCTIONS
 *  
 */
void ini_x(double* xx, double* vv);
void update_v(double* xx, double* vv, double ddt);
void update_x(double* xx, double* vv, double ddt);
void print_data(double* xx, double* vv);

int main(){

	// Filenames etc
	Ek = fopen("Ek.data","w");
	chain = fopen("Chain.data","w");
	
	// Final time
	int tf = 5.0*N*N;

	// Mem Alloc for position x and velocity v **** Paralelization ****
	double* x = malloc(N*sizeof(double));
	double* v = malloc(N*sizeof(double));
	ini_x(x,v);
	
	// Time and index for writing
	double t = 0;
	// int i = 0;
	do{
		update_v(x,v,dt/2);
		update_x(x,v,dt);
		update_v(x,v,dt/2);
		int mod = ((int)(t/dt))%((int)(tf/(1000*dt)));
		if( mod == 0 ){

			// Calculates energy of the first, second and third mode
			//printf("%d\n",i);
			print_data(x,v);	
			//i++;	
		}

		t += dt;
	}while(t <= tf);
	fclose(Ek);
	fclose(chain);
	return 0;
}



/*
 *  Defines the initial condition for the x vector and (zero) for the initial velocity vector
 *
 */
void ini_x(double* xx, double* vv){
	int i;
	for( i = 0; i < N; i++ ){
		xx[i] = sin(M_PI*i/(N-1));
		vv[i] = 0;
	}
}

/*
 *  Updates velocity given the position and the finite difference ddt
 *
 */
void update_v(double* xx, double* vv, double ddt){
	int i;
	// Actualizes vv
	for( i = 1; i < N-1; i++ ){
		// Acceleration is defined as the term multiplying ddt
		vv[i] = vv[i]+(ddt)*(xx[i+1] + xx[i-1] - 2*xx[i] + beta*(pow(xx[i+1]-xx[i],3) - pow(xx[i]-xx[i-1],3)));
	}
}

/*
 *  Updates position given the previous velocity and the finite difference ddt
 *
 */
void update_x(double* xx, double* vv, double ddt){
	int i;
	// Actualizes xx
	for( i = 1; i < N-1; i++ ){
		xx[i] = xx[i]+ddt*vv[i];
	}
	//return vec;
}

/*
 *  Prints energy of modes 1,2 and 3 as well as the configuration of the chain
 *
 */
void print_data(double* xx, double* vv){
	int i;
	double e1 = 0;
	double e2 = 0;
	double e3 = 0;
	double wk = 1;
	// Calculates energy of 3 modes
	for( i = 0; i < N; i++ ){
		e1 += wk*sqrt(2/(N-1))*xx[i]*sin(1*M_PI*i/(N-1))+ pow(vv[i],2);
		e2 += wk*sqrt(2/(N-1))*xx[i]*sin(2*M_PI*i/(N-1))+ pow(vv[i],2);
		e3 += wk*sqrt(2/(N-1))*xx[i]*sin(3*M_PI*i/(N-1))+ pow(vv[i],2);
		// Prints x and v
		fprintf(chain, "%f,%f\n", xx[i], vv[i]);
	}
	fprintf(Ek, "%f,%f,%f\n", e1, e2, e3);
}




