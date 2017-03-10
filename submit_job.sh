#PBS -N test_scheduler
#PBS -l nodes=1:ppn=4
#PBS -M jd.prada1760@uniandes.edu.co
#PBS -m abe

module load rocks-openmpi_ib
cd $PBS_O_WORKDIR
./a.out Time2.data Ek2.data Chain.data 2
./a.out Time4.data Ek4.data Chain.data 4
./a.out Time8.data Ek8.data Chain.data 8
