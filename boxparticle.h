#ifndef BOXPARTICLE_H
#define BOXPARTICLE_H

#include <particle.h>
#include <boxcollider.h>

namespace FalconeEngine
{
    namespace ParticleSystem
    {
        class BoxParticle : public Particle
        {
        private:
            //Physics::BoxCollider collider;
        public:
            BoxParticle();
        };
    }

}
#endif // BOXPARTICLE_H
