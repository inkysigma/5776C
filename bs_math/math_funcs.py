import matplotlib.pyplot as plt
import numpy as np

def gaussian(x, a, b, c):
	"""Gaussian function"""
	return a * np.e ** -((x - b)**2)/(2 * c ** 2)

# Data for plotting
t = np.arange(0.0, 2.0, 0.01)
s = gaussian(t, 2, 1.1, 0.4)

# Note that using plt.subplots below is equivalent to using
# fig = plt.figure and then ax = fig.add_subplot(111)
fig, ax = plt.subplots()
ax.plot(t, s)

ax.set(xlabel="mass (kg)", ylabel="probability (%)",
       title="the effect of mass of robot on probability of grabbing a cone".title())
ax.grid()

fig.savefig("test.png")
plt.show()