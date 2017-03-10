EXECS=a.out

all: Energies.png  TimeEvol.png

TimeEvol.png: Time2.data Time4.data Time8.data
	python timeplot.py Time2.data Time4.data Time8.data

Energies.png: Ek2.data
	python pyplot.py Ek2.data

Time2.data Time4.data Time8.data Ek2.data: a.out submit_job.sh
	qsub submit_job.sh

a.out : FPUT_solve.c
	gcc -Wall FPUT_solve.c -fopenmp -lm

clean:
	rm -f a.out
	rm -f *.data
	rm -f test*
