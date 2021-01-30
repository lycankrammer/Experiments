# Plot f(x) = ln(1 / cos²(x)) and g(x) = ln(1 / sin²(x))
# across -20 <= x <= 20 on a 1000 point sample
import pylab
from math import sin, cos, log1p
import numpy as np

if __name__ == '__main__':
	n = 1000
	xmin, xmax = -20., 20.
	dx = (xmax - xmin) / (n-1)
	x = np.zeros(n)
	y1 = np.zeros(n)
	y2 = np.zeros(n)
	
	for i in range(n):
		xpoint = xmin + i * dx
		x[i] = xpoint
		y1[i] = log1p(1 / cos(xpoint) ** 2)
		y2[i] = log1p(1 / sin(xpoint) ** 2)
			
	pylab.plot(x, y1)
	pylab.plot(x, y2)
	pylab.show()
	
