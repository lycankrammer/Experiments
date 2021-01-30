# Using LaTeX in pylab
# Plot the fuctions f(x) = x^n sin(x) for n = 1, 2, 3, 4
import pylab

if __name__ == '__main__':
	pylab.rc('text', usetex=True) # enable latex markup
	
	x = pylab.linspace(-10, 10, 1001)
	for n in range(1, 5):
		y = x**n * pylab.sin(x)
		# To make the graphs easier to compare, they have been scaled
		# to a maximum of 1 in the region considered.
		y /= max(y)
		pylab.plot(x, y, label=r'$x^{}\sin x$'.format(n))
		
	pylab.legend(loc='lower center')
	pylab.show()
