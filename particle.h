#ifndef PARTICLE_H
#define PARTICLE_H

#include <Vector3.h>

namespace FalconeEngine
{
    namespace ParticleSystem
    {
        class Particle
        {
        private:
            Vector3 position;
            Vector3 velocity;
            Vector3 appliedForce;
        public:
            Particle();
        };
    }
}

#endif // PARTICLE_H
