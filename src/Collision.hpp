#include <vector>

#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "Object.hpp"
#include "System.hpp"

namespace aos
{    
    class Collision: public System
    {
        public:
            Collision();
            ~Collision();
    };
}

#endif

