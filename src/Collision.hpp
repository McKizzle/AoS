#include "includes.hpp"
#include "Object.hpp"

#include <vector>

#ifndef COLLISION_HPP
#define COLLISION_HPP

namespace aos
{
    class Collision
    {
        public:
            std::vector< Object * > bins;

            Collision(Object * ref_obj);
            ~Collision(); 

            void test_collision(Object * obj);
    };
}

#endif

