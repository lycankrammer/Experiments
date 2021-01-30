# Example 3.1 - Plot sin^2(x)
from math import pi, sin
import numpy as np
import pylab

if __name__ == '__main__':
	xmin, xmax = -2. * pi, 2. * pi
	n = 1000 # n samples
	x = np.zeros(n)
	y = np.zeros(n)
	dx = (xmax - xmin) / (n-1)
	
	for i in range(n):
		xpoint = xmin + i * dx
		x[i] = xpoint
		y[i] = sin(xpoint) ** 2
		
	pylab.plot(x, y)
	pylab.show()
