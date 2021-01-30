""" A cardioid is the plane figure described in polar coordinates by
r = 2a(1 + cos(θ)) for 0 <= θ <= 2π.
"""
import pylab

if __name__ == '__main__':
	θ = pylab.linspace(0, 2 * pylab.pi, 1000)
	a = 1.
	r = 2 * a * (1. + pylab.cos(θ))
	
	pylab.polar(θ, r)
	pylab.show()
