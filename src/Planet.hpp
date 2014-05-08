#include <gmtl/gmtl.h>
#include <gmtl/VecOps.h>
#include <gmtl/MatrixOps.h>

#ifndef PLANET_HPP
#define PLANET_HPP

#include "Object.hpp"
#include "Collidable.hpp"

namespace aos
{
    class Planet: public Object
    {
        public: 
            Planet(double radius, unsigned int sectors, double x, double y);
            ~Planet();

            /// Only perform circle point collision detection.  
            bool check_collision(std::vector< double > point);


            void set_collision(Collidable * collider);
    };
}

#endif
