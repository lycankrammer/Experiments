# Plot the normalized Gaussian function centered at x = 0
import pylab
import numpy as np
from math import exp, sqrt, pi

def compute_gaussian(*, n=1000, stdev=1.0):
	xmin, xmax = -10., 10.
	x = pylab.linspace(xmin, xmax, n)
	dx = (xmax - xmin) / (n-1)
	y = np.zeros(n)
	
	dvar = 2. * stdev**2
	for i in range(n):
		xpoint = xmin + i * dx
		x[i] = xpoint
		y[i] = 1./sqrt(pi * dvar) * exp(- xpoint**2 / dvar)
	
	return x, y
	
if __name__ == '__main__':
	x, y = compute_gaussian(stdev=1.5)
	
	pylab.plot(x, y)
	pylab.show()
