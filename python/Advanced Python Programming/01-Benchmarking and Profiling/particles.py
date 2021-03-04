import matplotlib.pyplot as plt
import matplotlib

class Particle:

    def __init__(self, x, y, angularvel):
        """ Particle positions and angular velocity. """
        self.x = x
        self.y = y
        self.angularvel = angularvel

class ParticleSimulator:

    def __init__(self, particles):
        """ A list of particles. """
        self.particles = particles

    def evolve(self, dt, *, timestep=1.0e-5):
        """
        Approximate circular motion by changing particle
        positions in function of infinitesimal time dt.
        """
        nsteps = int(dt / timestep)
        for i in range(nsteps):
            for p in self.particles:
                # Calculate direction of motion
                norm = (p.x**2 + p.y**2)**0.5
                try:
                    vx = -p.y / norm
                    vy = p.x / norm
                except ZeroDivisionError:
                    print("Division by zero found in iteration {}, particle {}".format(i, p))
                    pass

                # Calculate displacement
                dx = timestep * p.angularvel * vx
                dy = timestep * p.angularvel * vy
                p.x += dx
                p.y += dy

    def visualize(self):
        """ Animate a particle simulation. """
        X = [p.x for p in self.particles]
        Y = [p.y for p in self.particles]

        fig = plt.figure()
        ax = plt.subplot(111, aspect='equal')
        # ax.plot returns a tuple (or list) with one element. This
        # is the same as:  line = ax.plot(X, Y, 'ro')[0]
        line, = ax.plot(X, Y, 'ro')
        # Axis limits
        plt.xlim(-1, 1)
        plt.ylim(-1, 1)

        def init():
            line.set_data([], [])
            return line,

        def animate(i):
            self.evolve(0.01)
            X = [p.x for p in self.particles]
            Y = [p.y for p in self.particles]
            line.set_data(X, Y)
            return line,

        anim = matplotlib.animation.FuncAnimation(fig, animate, init_func=init, blit=True, interval=10)
        plt.show()
