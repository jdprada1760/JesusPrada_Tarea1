##################This program graphics time of execution for FPUT problem with 2,4,8 procesors ##############################################
import matplotlib
# Solves display problems 
matplotlib.use('Agg')

import numpy as np
import matplotlib.pyplot as plt
import sys

# Load data
t1 = np.loadtxt(sys.argv[1], delimiter = ',')
t2 = np.loadtxt(sys.argv[2], delimiter = ',')
t4 = np.loadtxt(sys.argv[3], delimiter = ',')

# Array of times and respective procesors
tarr = np.array([t1,t2,t4])
nump = np.array([1,2,4]) 

# Plot 
fig = plt.figure()
ax = fig.add_subplot(111)
style = 'o'
ax.plot(nump,tarr, linestyle='None', marker=style)
ax.set_xlim(0,9)
ax.set_ylim(min(tarr)-3,max(tarr)+3)
ax.set_title("Parallelization eficiency")
ax.set_ylabel("Time(s)")
ax.set_xlabel("Number of procesors")
fig.savefig('TimeEvol.png')
