##################This program graphics time of execution for FPUT problem with 2,4,8 procesors ##############################################
import matplotlib
# Solves display problems 
matplotlib.use('Agg')

import numpy as np
import matplotlib.pyplot as plt
import sys

# Load data
t2 = np.loadtxt(sys.argv[2], delimiter = ',')
t4 = np.loadtxt(sys.argv[4], delimiter = ',')
t8 = np.loadtxt(sys.argv[8], delimiter = ',')

# Array of times and respective procesors
tarr = np.array([t2,t4,t8])
nump = np.array([2,4,6]) 

# Plot 
fig = plt.figure()
ax = fig.add_subplot(111)
style = 'o'
ax.plot(nump,tarr, linestyle='None', marker=style)
ax.set_title("Parallelization eficiency")
ax.set_ylabel("Time(s)")
ax.set_xlabel("Number of procesors")
fig.savefig('TimeEvol.png')
