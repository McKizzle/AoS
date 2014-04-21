#include <vector>
#include <SDL2/SDL.h>
#include <cmath>
#include <cstdlib>

#define _USE_MATH_DEFINES

#define GW_GM  4.0 * (M_PI * M_PI)


#ifndef GRAVITYWELL_HPP
#define GRAVITYWELL_HPP

#include "System.hpp"
#include "Object.hpp"



namespace aos
{
    /// \class CelestialBody CelestialBody.hpp 
    /// \brief Represents a body that has gravity. 
    ///  
    /// The CelestialBody class takes in an object and associates gravitational forces
    /// to it. It is issentially a simple 1body system where the you have the ability to 
    /// associate 'satellite' objects to it which will be affected by its gravity. 
    class GravityWell: public System
    {
        public: 
            //static const double GM = 4 * (M_PI * M_PI);

            double mass = 1e3; ///< The mass of the object. Scale and units to be determined.
            Object * celestial_body; ///< The object that represents the celestial body. 
            std::vector<Object *> satellites;
            
            /// Create a gravity well associated with a celestial body. 
            GravityWell(Object * celestial_body);
            ~GravityWell();

            unsigned int push_back(System * satellite); ///< Adds a satellite. 
            virtual void pop_back(); ///< Removes a satellite
            
            /// Updates the forces acting on the bodies that are associated to the gravity well. 
            virtual void update(Uint32 dt_ms, Uint32 time);
    };
}

#endif
