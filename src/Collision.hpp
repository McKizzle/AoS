#include <vector>

#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "Object.hpp"
#include "Systems.hpp"
#include "Collidable.hpp"

namespace aos
{    
    class Collision: public Systems
    {
        public:
            Collidable *collider;
            bool collision = false;

            Collision(Collidable *collider);
            ~Collision();

            /// Inherited from Updateful.hpp. Overrides update to search for collisions. 
            virtual void update(Uint32 dt_ms, Uint32 time); ///< Inherited from Updateful
    };
}

#endif

