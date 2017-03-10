EXECS=a.out

all: Energies.png  Time2.data Time4.data Time8.data 

Energies.png: Ek2.data
	python pyplot Ek2.data

Time2.data: a.out submit_job.sh
	qsub submit_job.sh
	

a.out : FPUT_solve.c
	gcc -Wall FPUT_solve.c -fopenmp -lm

clean:
	rm -f a.out
	rm -f *.data
	rm -f test*
