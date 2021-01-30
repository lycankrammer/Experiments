""" Example of histogram in pylab.
	Taking 5000 random values from the normal distribution with mean
	0 and standard deviation 2.
"""
import pylab
from random import normalvariate

if __name__ == '__main__':
	data = []
	for i in range(5000):
		data.append(normalvariate(0, 2))
	
	pylab.hist(data, bins=20, density=True)
	pylab.show()
