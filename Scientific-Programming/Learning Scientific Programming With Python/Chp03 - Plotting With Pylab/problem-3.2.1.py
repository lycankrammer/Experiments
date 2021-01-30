# Problem 3.2.1
import pylab

if __name__ == '__main__':
	# First order rate constants (s^-1)
	k1, k2 = 300, 100
	# Initial concentration of reactant (mol dm^-3)
	A0 = 2.
	
	t = pylab.linspace(0, .1, 1000)
	# Molecules
	A = A0 * pylab.exp(-(k1+k2) * t)
	tmp = A0 * (1 - pylab.exp(-(k1+k2) * t))
	B = k1 / (k1+k2) * tmp
	C = k2 / (k1+k2) * tmp
	
	# Plot
	pylab.plot(t * 1000, A, markersize=12, color='b', markeredgecolor='b', label='[A]')
	pylab.plot(t * 1000, B, markersize=12, color='g', markeredgecolor='g', label='[B]')
	pylab.plot(t * 1000, C, markersize=12, color='r', markeredgecolor='r', label='[C]')
	pylab.legend(fontsize=16, loc='upper right')
	pylab.xlabel('Time /ms', fontsize=16)
	pylab.ylabel('Concentration /mol dm^-3', fontsize=16)
	pylab.title("First order concentration reaction [A], [B], [C]")
	pylab.show()
