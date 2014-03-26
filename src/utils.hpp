#include "includes.hpp"
#include "Object.hpp"

#include <cmath>
#include <cstdlib>

#define _USE_MATH_DEFINES

#ifndef UTILS_HPP
#define UTILS_HPP

namespace aos
{
    void dvect_dump(const std::ostream &os, const std::vector< double > &todump);
    Object * circle(double radius, unsigned int sectors, double x, double y); ///< Generates a circle. 
    Object * grid(double width, double height, double step_size); ///< Generates an MxN grid object.
    std::vector< Object * > * seed_for_asteroids(unsigned int seed, unsigned int count, 
            double verts_max, double verts_min,
            double max_radius, double max_heading_vel);
}

#endif
