#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>
#include <cstdlib>

#define _USE_MATH_DEFINES

#include "Object.hpp"

namespace aos
{
    class Object;
    
    /// Dumps the contents of a vector of doubles to a out stream.
    void dvect_dump(const std::ostream &os, const std::vector< double > &todump);

    /// Generates an object that renders a circle. 
    Object * circle(double radius, unsigned int sectors, double x, double y); ///< Generates a circle. 
    /// Generate a random set of asteroids. 
    std::vector< Object * > * seed_for_asteroids(unsigned int seed, unsigned int count, 
            double verts_max, double verts_min,
            double max_radius, double max_heading_vel);
}

#endif
