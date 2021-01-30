""" A spiral may be considered to be the figure described by the motion
of a point on an imaginary line as that line pivots around an origin at
constant angular velocity. If the point is fixed on the line,  then the
figure described is a circle.
	i) If the point on the rotating  line moves  from the  origin  with
	   constant speed, its position describes an Archimedean spiral. In
	   polar coordinates the equation of this spiral is r = a + bθ.
   ii) If the point moves along the rotating  line with a velocity that
       increases in  proportion to  its  distance from  the origin, the
       result is a logarithmic spiral, which may be written as r = a^θ.
"""
import pylab

if __name__ == '__main__':
	# Archimedean Spiral
	θ = pylab.linspace(0, 8 * pylab.pi, 1000)
	b = 2.
	r = b * θ
	
	pylab.polar(θ, r)
	pylab.show()

	# Logarithmic Spiral
	θ = pylab.linspace(0, 8 * pylab.pi, 1000)
	a = .8
	r = a**θ
	
	pylab.polar(θ, r)
	pylab.show()
