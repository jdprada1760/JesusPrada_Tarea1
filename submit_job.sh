#PBS -N test_scheduler
#PBS -l nodes=1:ppn=4
#PBS -M jd.prada1760@uniandes.edu.co
#PBS -m abe

module load rocks-openmpi_ib
cd $PBS_O_WORKDIR
./a.out Time2.data Ek2.data Chain2.data 2
