""" The Mersenne prime, Mi, is a prime number of the form Mi = 2^i - 1.
	The set of Mersenne primes less than n may  be  thought of as  the
	intersection of the  set of all primes  less than n, Pn,  with the
	set, An, of integers satisfying 2^i - 1 < n.
"""
from math import sqrt, log

def primes(n):
	""" Return a list of the prime numbers <= n. """
	assert type(n) == int, 'n must be an integer'
	
	sieve = [True] * (n//2)
	for i in range(3, int(sqrt(n))+1, 2):
		if sieve[i//2]:
			sieve[i*i//2::i] = [False] * ((n - i*i - 1) // (2*i) + 1)
	
	return [2] + [2*i+1 for i in range(1, n//2) if sieve[i]]
	   

if __name__ == '__main__':
	n = 1000000
	
	P = set(primes(n))
	# A list of integers  2^i - 1 <= n
	A = []
	for i in range(2, int(log(n+1, 2))+1):
		A.append(2**i - 1)
	
	# The set of Mersenne primes as the intersection of P and A
	M = P.intersection(A)
	
	print(sorted(list(M)))
