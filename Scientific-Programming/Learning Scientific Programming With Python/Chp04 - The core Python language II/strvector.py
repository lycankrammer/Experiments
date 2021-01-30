""" This example defines a function  that returns  a  string
	representation of a two-dimensional or three-dimensional
	vector, which  must  be represented  as a list or  tuple
	containing two or three items.
	And a function that takes the cross product of  a  three
	dimensional vector.
"""

def str_vector(v):
	assert type(v) is list or type(v) is tuple, 'argument to str_vector must be a list or tuple'
	assert len(v) in (2, 3), 'vector must be 2D or 3D in str_vector'
	
	unitvectors = ['i', 'j', 'k']
	s = []
	for i, component in enumerate(v):
		s.append("{}{}".format(component, unitvectors[i]))
	
	s = [c for c in s if c[0] != '0' or c[0] == '0' and c[1] == '.']
	return '+'.join(s).replace('+-', '-')

def cross_product3D(a, b):
	assert len(a) == len(b) == 3, 'vectors a, b must be three-dimensional'
	
	return [a[1] * b[2] - a[2] * b[1],
	        a[2] * b[0] - a[0] * b[2],
	        a[0] * b[1] - a[1] * b[0]]


if __name__ == '__main__':
	vectors = [(1, 2), (1, -2, -3), (0, 12, 32), (0.001, 0.002, 0.03), 
	           (-1, 8.5), (1, 2, 3, 4)]
	
	for idx, v in enumerate(vectors):
		print("Vector v{}: {}".format(idx+1, str_vector(v)))
	
	print(cross_product3D(vectors[1], vectors[2]))
	print(cross_product3D(vectors[5], vectors[5]))
	
