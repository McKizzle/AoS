#include "includes.hpp"
#include "Object.hpp"

#ifndef UTILS_HPP
#define UTILS_HPP

namespace aos
{
    void dvect_dump(const std::ostream &os, const std::vector< double > &todump);
    Object * grid(double width, double height, double step_size); ///< Generates an MxN grid object.
}

#endif
