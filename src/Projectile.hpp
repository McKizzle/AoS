#include <vector> 

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Object.hpp"

namespace aos
{
    /// \class Projectile Projectile.hpp
    /// \brief Represents a projectile. 
    ///  
    /// A projectile is a special object that modifies scores based
    /// on what it collides with. 
    class Projectile: public Object
    {
        public:
            Object * owner; ///< The owner of the projectile.

            Projectile(Object * owner, std::vector< double > init_state, double velocity_x, double velocity_y);
            ~Projectile();
    };
}

#endif

