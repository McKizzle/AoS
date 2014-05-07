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
            virtual void render(Uint32 dt_ms, Uint32 time); ///< Override Renderful.
            virtual void send_event(const Uint8* keyboardStates, Uint32 dt, Uint32 time);
    };
}

#endif

