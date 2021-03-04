import random
from particles import Particle, ParticleSimulator

def benchmark():
    particles = [Particle(random.uniform(-1.0, 1.0),
                          random.uniform(-1.0, 1.0),
                          random.uniform(-1.0, 1.0))
                 for i in range(1000)]
    sim = ParticleSimulator(particles)
    sim.evolve(0.1)

if __name__ == '__main__':
    benchmark()
