#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>
#include <cstdlib>

#define _USE_MATH_DEFINES

#include "Object.hpp"
#include "Systems.hpp"
#include "GravityWell.hpp"
#include "Collision.hpp"
#include "Planet.hpp"
#include "Player.hpp"
#include "Grid.hpp"
#include "Score.hpp"
#include "Projectile.hpp"

namespace aos
{
    class Object;
    
    /// Dumps the contents of a vector of doubles to a out stream.
    void dvect_dump(const std::ostream &os, const std::vector< double > &todump);
    
    /// Generate a circular object. 
    /// \param [in] radius
    /// \param [in] the number of segments used to render circle parameter. 
    /// \param [in] the x position. 
    /// \param [in] the y positoin. 
    ///
    /// \return the generated object. 
    Object * circle(double radius, unsigned int sectors, double x, double y); ///< Generates a circle. 

    /// Generate a random set of asteroids. 
    /// \param [in] the seed to use (doesn't work for now though)
    /// \param [in] the number of asteroids to generate. 
    /// \param [in] the maximum number of allowed vertices per asteroid. 
    /// \param [in] the minimum number of allowd vertices per asteroid. 
    /// \param [in] the minimum radius of an asteroid. 
    /// \param [in] the maximum radius of an asteroid. 
    /// \param [in] the maximum heading velocity. (if its negative spin counter clockwise.) 
    ///
    /// \return a vector of Objects the 'look' like asteroids. 
    std::vector< Object * > * seed_for_asteroids(unsigned int seed, unsigned int count, 
            double verts_max, double verts_min,
            double min_radius, double max_radius, double max_heading_vel);
    
    /// Returns a single asteroid. 
    Systems * single_asteroid();
    /// Returns a system with two planets, 100 Asteroids and a player. 
    Systems * two_planets(); 
    /// Pin the ship!
    Systems * pin_the_ship();
}

#endif
