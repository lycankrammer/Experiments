""" Generators allows us to declare a function that behaves like an
	iterable object. That is, a function that can be used in a  for
	loop and that will yield its values, in turn, on demand.
"""

def triangular_numbers(n):
	assert type(n) is int, 'argument \'n\' must be an integer'
	i, t = 1, 0
	
	while i <= n:
		yield t
		t += i
		i += 1

if __name__ == '__main__':
	print(list(triangular_numbers(15)))
		
