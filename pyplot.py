import numpy as np
import matplotlib.pyplot as plt
import sys
from matplotlib import animation

# Solves display problems 
matplotlib.use('Agg')
# Loads data #Energy modes and #Chain configutation
modes = np.loadtxt(sys.argv[1], delimiter = ',').T
#chain = np.loadtxt("Chain.data", delimiter = ',', usecols = (0,))

# Reshape chain array to plot 
# chain = chain.reshape((len(modes.T),64))


# Plots energy modes
fig = plt.figure()
ax = fig.add_subplot(111)
style = 'o'
ms = 0.5
ax.plot(modes[0], c='r', linestyle='None', marker=style, markersize = ms)
ax.plot(modes[1], c='g', linestyle='None', marker=style, markersize = ms)
ax.plot(modes[2], c='b', linestyle='None', marker=style, markersize = ms)
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

