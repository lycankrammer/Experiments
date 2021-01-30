# Plot the annual risk of death in UK (2005)
import pylab
import numpy as np

if __name__ == '__main__':
	# Age ranges
	x = np.array([0, 1, 4, 5, 14, 15, 24, 25, 34, 35, 44, 45, 54, 55, 64, 65, 74,
	     75, 84, 85])
	# Anuual risk of death (1 to N)
	female = np.array([227, 5376, 5376, 10417, 10417, 4132, 4132, 2488, 2488,
	          1106, 1106, 421, 421, 178, 178, 65, 65, 21, 21, 7])
	male = np.array([177, 4386, 4386, 8333, 8333, 1908, 1908, 1215, 1215, 663, 663,
	        279, 279, 112, 112, 42, 42, 15, 15, 6])

	pylab.plot(x, 1./female, markersize=16, color='r', markeredgecolor='r', label='Female')
	pylab.plot(x, 1./male, markersize=16, color='b', markeredgecolor='b', label='Male')
	pylab.legend(fontsize=16, loc='upper left')
	pylab.xlabel('Age (years)', fontsize=16)
	pylab.ylabel('Risk of death (1 to N)', fontsize=16)
	pylab.title("UK Annual risk of death (2005)")
	pylab.show()
