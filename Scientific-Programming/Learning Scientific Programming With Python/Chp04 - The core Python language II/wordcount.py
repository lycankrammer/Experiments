"""
The novel Moby-Dick is out of copyright and can be downloaded as a text file
from the Project Gutenberg website at www.gutenberg.org/2/7/0/2701/. Write a
program to output 100 words mot frequently used in the book
"""
import string
import argparse
import numpy as np
from math import log10

def most_frequent_words(filename, nwords):
	assert type(filename) is str, 'invalid type for {}'.format(filename)
	
	words = {}
	with open(filename, newline='') as f:
		for line in f.readlines():
			line = ''.join(line.strip(string.punctuation))
			for w in line.split():
				w = w.strip(string.punctuation)
				try:
					words[w] = words.get(w, 0) + 1
				except KeyError:
					pass
	
	slist = sorted(words.items(), key=lambda x: x[1], reverse=True)
	
	try:
		return slist[:nwords]
	except IndexError:
		print("[ALERTA]: quantidade {} fora do intervalo de valores válidos.".format(nwords))
		return slist

def zipf_law(wlist):
	assert type(wlist) is list, 'invalid type for wlist'
	
	freqlist = np.array([freq for _, freq in wlist])
	
	n = len(freqlist)
	zipf = np.zeros(n)
	for i in range(n):
		zipf[i] = log10(freqlist[i]) - log10(i+1)
	
	return zipf
	
	
if __name__ == '__main__':
	parser = argparse.ArgumentParser()
	obrigatorio = parser.add_argument_group("argumentos obrigatórios")
	obrigatorio.add_argument("-f", "--textpath", help="", required=True)
	
	args = parser.parse_args()
	
	wordlist = most_frequent_words(args.textpath, 20)
	zipf = zipf_law(wordlist)
	
	[print("{}: {}".format(word, count)) for word, count in wordlist]
	print("========== Zipf's Law ==========")
	[print("log f(w) = {} = log C - alog r(w) = {}".format(log10(wordlist[i][1]), zipf[i])) for i, _ in enumerate(wordlist)]
