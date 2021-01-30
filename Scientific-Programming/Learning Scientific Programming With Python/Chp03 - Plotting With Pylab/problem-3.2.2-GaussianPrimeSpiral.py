# Plot a Gaussian prime spiral
import pylab
import cmath
from math import sqrt
import numpy as np

def isprime(n):
	prime = True
	sq = sqrt(n)
	j = 2
	while j <= sq and prime:
		if n % j == 0:
			prime = False
		j += 1
	
	return prime

def direction_transform(direct):
	dc = (0, 0)
	if direct == (1, 0):
		dc = (0, 1)
	elif direct == (0, 1):
		dc = (-1, 0)
	elif direct == (-1, 0):
		dc = (0, -1)
	elif direct == (0, -1):
		dc = (1, 0)
			
	return dc
	
if __name__ == '__main__':
	n = 10000
		
	dc = (1, 0)         # direction
	c0 = complex(5, 23) # starting point
	
	ax = np.zeros(n)
	ay = np.zeros(n)
	for i in range(n):
		ax[i] = c0.real
		if ( c0.real == 0 and abs(c0.imag) == 4 * i + 3 ) or \
		   ( c0.imag == 0 or abs(c0.real) == 4 * i + 3 ) or \
		   isprime(c0.real**2 + c0.imag**2):
			dc = direction_transform(dc)
		r, im = dc
		c0 += complex(r, im) # transform
		ay[i] = c0.imag
				
	
	pylab.plot(ax, ay, markersize=12, color='r', markeredgecolor='r')
	pylab.xlabel('Real', fontsize=16)
	pylab.ylabel('Imaginary', fontsize=16)
	pylab.title("Gaussian Prime Spiral")
	pylab.show()
