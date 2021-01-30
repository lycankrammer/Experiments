"""
	Pascal Triangle
"""
import argparse

def pascal_triangle(nmax):
	assert type(nmax) is int, 'argument \'nmax\' must be an integer'
	
	x = [1]
	space, maxsp = '  ', nmax
	for n in range(1, nmax+2):
		sp = space * maxsp
		maxsp -= 1
		
		print("{}{}".format(sp, x))
		x = [([0]+x)[i] + (x+[0])[i] for i in range(n+1)]
		

if __name__ == '__main__':
	parser = argparse.ArgumentParser()
	obrigatorio = parser.add_argument_group("argumentos obrigarótios")
	obrigatorio.add_argument("-n", "--nmax", type=int, required=True,
	                         help="max size of Pascal triangle")
	
	args = parser.parse_args()
	
	pascal_triangle(args.nmax)
