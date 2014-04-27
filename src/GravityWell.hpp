#include <vector>
#include <SDL2/SDL.h>
#include <cmath>
#include <cstdlib>

#define _USE_MATH_DEFINES

#define GW_GM  1 //4.0 * (M_PI * M_PI)


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
        // TODO: Mass and density should be an object property.
        public: 
            double mass    = 1e3;    ///< The mass of the object. Scale and units to be determined.
            double density = 1.0;    ///< Not too dense or the gravity feild will be too strong.
            double pe      = 0.005;    ///< A percentage dampener of the object radius to the minimum distance. 
            double epsilon = 1.0;    ///< Dampen by a distance of one.
            Object * celestial_body; ///< The object that represents the celestial body. 
            std::vector<Object *> satellites;
            
            /// Create a gravity well associated with a celestial body. 
            GravityWell(Object * celestial_body);
            ~GravityWell();

            unsigned int push_back(System * satellite); ///< Adds a satellite.
            virtual void pop_back(); ///< Removes a satellite

            /// Places an object in orbit about the planet. 
            /// 
            /// \param [in, out] the satellite that will be affected by the gravity.
            /// \param [in] the distance from the center of the celestial body. 
            /// \param [in] the position in the orbit to place the object. Expects a value in 
            ///     radians.
            //unsigned int push_back_orbit(System * satellite, double distance, double position); ///< Adds an orbiting satellite at the specified distance from the body. 

            /// Behaves just like push_back_orbit except for that the objects are placed in 
            /// random locations around the orbit.
            unsigned int push_back_orbit(System * satellite, double distance);
            
            /// Calculates the gravitational forces between a satellite and the gravitational well.
            /// 
            /// \param [in] The satellite of interest.
            /// 
            /// \returns an (x,y) vector of the acting forces. 
            std::vector< double > F_g(Object * satellite);

            /// Updates the forces acting on the bodies that are associated to the gravity well. 
            virtual void update(Uint32 dt_ms, Uint32 time);
    };
}

#endif
