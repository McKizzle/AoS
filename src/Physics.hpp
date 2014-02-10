#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#include "Object.hpp"

namespace aos {
    /// \interface Integrator 
    /// \brief The Integrator interface allows a class to implement a timer that updates a
    ///         a set of objects at regular intervals.
    class Integrator
    {
        public:
            virtual void integrate(int dt_ms, Object * objects) = 0;
    };
    
    /// \class PhysicsGine
    /// \brief The PhysicsGine class handles all of the object position 
    ///         update calls. 
    class PhysicsGine: public Integrator
    {
        public:
            PhysicsGine();
            ~PhysicsGine();
            virtual void integrate(int dt_ms, Object * objects);
            virtual void overrided();
    };
}
#endif
