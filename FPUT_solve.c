// This code solves Fermi-Pasta-Ulam-Tsingou differential equation for 
// a given inital condition using leapfrog. Parameters are defined below.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
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
double beta = 1.0;
double dt = 0.005;

// Filenames etc
FILE* Ek;
FILE* chain;
FILE* ttime;

/*  
 *  PROBLEM FUNCTIONS
 *  
 */
void ini_x(double* xx, double* vv);
void update_v(double* xx, double* vv, double ddt);
void update_x(double* xx, double* vv, double ddt);
void print_data(double* xx, double* vv);
double getE(double* xx, double* vv, int n);

int main(){
	
	// Time
	ttime = fopen("Time.data","w"); 
	clock_t ini = clock();

	// Filenames etc
	Ek = fopen("Ek.data","w");
	chain = fopen("Chain.data","w");

	// Final time
	double tf = N*N;

	// Mem Alloc for position x and velocity v **** Paralelization ****
	double* x = malloc(N*sizeof(double));
	double* v = malloc(N*sizeof(double));
	ini_x(x,v);
	
	// Time and index for writing
	double t = 0;
	int i = 0;
	do{	
		int mod = ((int)(t/dt))%((int)(tf/(1000*dt)));
		if( mod == 0 ){

			// Calculates energy of the first, second and third mode
			printf("%d\n",i);
			print_data(x,v);	
			i++;	
		}
		update_v(x,v,0.5*dt);
		update_x(x,v,dt);
		update_v(x,v,0.5*dt);
		
		t += dt;
	}while(t <= tf);
	
	// Closes files and deallocate memory
	fclose(Ek);
	fclose(chain);
	free(x);
	free(v);
	
	// Gets time and writes it on file (time) and then closes the file
	clock_t fin = clock();
	double time_elapsed = ((double)(fin - ini))/CLOCKS_PER_SEC;
	fprintf(ttime, "%f\n", time_elapsed);
	fclose(ttime);

	return 0;
}



/*
 *  Defines the initial condition for the x vector and (zero) for the initial velocity vector
 *
 */
void ini_x(double* xx, double* vv){
	int i;
	for( i = 0; i < N; i++ ){
		xx[i] = sin(2.0*M_PI*i/(N-1));
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
		//vv[i%N] += (ddt)*(xx[(i+1)%N] + xx[(i-1)%N] - 2.0*xx[i%N] + beta*(pow(xx[(i+1)%N]-xx[i%N],2.0) - pow(xx[i%N]-xx[(i-1)%N],2.0)));
		vv[i] += (ddt)*(xx[(i+1)] + xx[(i-1)] - 2.0*xx[i] + beta*(pow(xx[(i+1)]-xx[i],2.0) - pow(xx[i]-xx[(i-1)],2.0)));
	}
}

/*
 *  Updates position given the previous velocity and the finite difference ddt
 *
 */
void update_x(double* xx, double* vv, double ddt){
	int i;
	// Actualizes xx
	for( i = 0; i < N; i++ ){
		xx[i%N] = xx[i%N]+ddt*vv[i%N];
	}
	//return vec;
}

/*
 *  Prints energy of modes 1,2 and 3 as well as the configuration of the chain
 *
 */
void print_data(double* xx, double* vv){
	int i;
	double e1 = getE(xx, vv, 1);
	double e2 = getE(xx, vv, 3);
	double e3 = getE(xx, vv, 2);
	// Calculates energy of 3 modes
	for( i = 0; i < N; i++ ){
		fprintf(chain, "%f,%f\n", xx[i], vv[i]);
	}
	fprintf(Ek, "%f,%f,%f\n", e1, e2, e3);
}

/*
 *  Gets energy of mode n given xx and vv
 *
 */
double getE(double* xx, double* vv, int n){
	int i;
	// Defines An 
	double An = 0;
	// Defines dot(An) 
	double Adn = 0;
	// Defines wn
	double wn = 4*pow(sin(n*M_PI/(2*N+2)),2);
	for( i = 0; i < N; i++ ){
		
		An  += sqrt(2.0/(N+1))*xx[i]*sin(n*M_PI*i/(N+1));
		Adn += sqrt(2.0/(N+1))*vv[i]*sin(n*M_PI*i/(N+1));

	}
	return 0.5*(pow(An,2)+pow(wn*An,2));

}

