""" The correlation between margarine consumption in the United States
and the divorce rate in Maine.
	The two time series here have different units and  meanings and so
should be plotted on separate y-axes, sharing a common x-axis (year).
"""
import pylab
import numpy as np

if __name__ == '__main__':
	years = range(2000, 2010)
	divorce_rate = np.array([5.0, 4.7, 4.6, 4.4, 4.3, 4.1, 4.2, 4.2, 4.2, 4.1])
	margarine_cons = np.array([8.2, 7., 6.5, 5.3, 5.2, 4., 4.6, 4.5, 4.2, 3.7])
	
	line1 = pylab.plot(years, divorce_rate, 'b-o', label='Divorce rate in Maine')
	pylab.ylabel('Divorces per 1000 people')
	pylab.legend()
	
	pylab.twinx() # start a new set of axis with the same x-axis
	line2 = pylab.plot(years, margarine_cons, 'r-o', label='Margarine consumption')
	pylab.ylabel('lb of Margarine (per capita)')
	
	# Jump through some hoops to get the both line's labels in the same legend
	lines = line1 + line2
	labels = []
	for line in lines:
		labels.append(line.get_label())
		
	pylab.legend(lines, labels)
	pylab.show()
