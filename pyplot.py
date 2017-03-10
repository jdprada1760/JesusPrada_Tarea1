############################## This program graphics energy modes 1,2,3 for FPUT problem ############################################################
import matplotlib
# Solves display problems 
matplotlib.use('Agg')

import numpy as np
import matplotlib.pyplot as plt
import sys
#from matplotlib import animation


# Loads data #Energy modes and
modes = np.loadtxt(sys.argv[1], delimiter = ',').T

#chain = np.loadtxt("Chain.data", delimiter = ',', usecols = (0,))
# Reshape chain array to plot 
# chain = chain.reshape((len(modes.T),64))


# Plots energy modes
fig = plt.figure()
times = np.range(0,1000)*(5.0*(64**2.2)/1000.0)
ax = fig.add_subplot(111)
style = 'o'
ms = 0.5
ax.plot(times,modes[0], c='r', linestyle='None', marker=style, markersize = ms)
ax.plot(times,modes[1], c='g', linestyle='None', marker=style, markersize = ms)
ax.plot(times,modes[2], c='b', linestyle='None', marker=style, markersize = ms)
ax.set_title("Energy modes 1,2,3")
# Arbitrary units
ax.set_ylabel("Energy")
ax.set_xlabel("Time")
#plt.show()
fig.savefig('Energies.png')

'''
# Plots evolution
plt.imshow(np.log(chain+0.00001))
plt.show()

'''
'''
# First set up the figure, the axis, and the plot element we want to animate
fig = plt.figure()
ax = plt.axes(xlim=(0, 64), ylim=(-2, 2))
line, = ax.plot([], [], lw=2)

# initialization function: plot the background of each frame
def init():
    line.set_data([], [])
    return line,

# animation function.  This is called sequentially
def animate(i):
    x = np.linspace(0, 64, 64)
    y = chain[i%1000]
    line.set_data(x, y)
    return line,

# call the animator.  blit=True means only re-draw the parts that have changed.
anim = animation.FuncAnimation(fig, animate, init_func=init,
                               frames=10000, interval=20, blit=False)

plt.show()
'''

