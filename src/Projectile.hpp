#include <vector> 

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Object.hpp"
#include "Weapon.hpp"
//#include "AsteroidsOnSteroids.hpp"

namespace aos
{
    class Weapon;
    /// \class Projectile Projectile.hpp
    /// \brief Represents a projectile. 
    ///  
    /// A projectile is a special object that modifies scores based
    /// on what it collides with. 
    class Projectile: public Object
    {
        public:
            Weapon * owner; ///< The owner of the projectile. (usually a weapon.)
            
            double ttl = 4.0; /// The time to live for the projectile. 

            Projectile();
            virtual ~Projectile();
 
            virtual void set_collision(Collidable * collider); 
    };
}

#endif

