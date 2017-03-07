import numpy as np
import matplotlib.pyplot as plt
from matplotlib import animation

# Loads data #Energy modes and #Chain configutation
modes = np.loadtxt("Ek.data", delimiter = ',')[:100].T
chain = np.loadtxt("Chain.data", delimiter = ',', usecols = (0,))

# Reshape chain array to plot 
chain = chain.reshape((1001,64))


# Plots energy modes
fig = plt.figure()
ax = fig.add_subplot(111)
ax.plot(modes[0], c='r')
ax.plot(modes[1], c='g')
ax.plot(modes[2], c='b')
plt.show()

'''
# Plots evolution
plt.imshow(np.log(chain+0.00001))
plt.show()


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
                               frames=200, interval=20, blit=True)

plt.show()
'''
