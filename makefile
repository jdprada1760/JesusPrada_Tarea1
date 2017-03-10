EXECS=a.out

all: Energies.png  TimeEvol.png

TimeEvol.png: Time1.data Time2.data Time4.data
	python timeplot.py Time1.data Time2.data Time4.data

Energies.png: Ek.data
	python pyplot.py Ek.data

Time1.data Time2.data Time4.data Ek.data: a.out submit_job.sh
	./a.out Time1.data Ek.data 1
	./a.out Time2.data Ek2.data 2
	./a.out Time4.data Ek4.data 4

a.out : FPUT_solve.c
	gcc -Wall FPUT_solve.c -fopenmp -lm

clean:
	rm -f a.out
	rm -f *.data
	rm -f test*
