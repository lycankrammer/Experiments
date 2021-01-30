""" The methods pylab.xlim and pylab.ylim sets the limits x- and y-limits
of the plot  respectively.  They  must be  called  after  any  pylab.plot
statements.
"""
import pylab

if __name__ == '__main__':
	t = pylab.linspace(0, 2, 1000)
	f = t * pylab.exp(t + pylab.sin(20*t))
	
	pylab.plot(t, f)
	pylab.xlim(1.5, 1.8)
	pylab.ylim(0, 30)
	pylab.show()
