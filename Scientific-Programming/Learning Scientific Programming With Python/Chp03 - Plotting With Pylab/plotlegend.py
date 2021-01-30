# Labels and Legends
import pylab
from math import pi

if __name__ == '__main__':
	n = 1000
	xmin, xmax = -2. * pi, 2. * pi
	
	x = pylab.linspace(xmin, xmax, n)
	y1 = pylab.sin(x)**2
	y2 = pylab.cos(x)**2
	
	pylab.plot(x, y1, label='sin²(x)')
	pylab.legend(loc=1)
	pylab.plot(x, y2, label='cos²(x)')
	pylab.legend(loc=1)
	pylab.show()
