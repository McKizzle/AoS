#include "includes.hpp"
#include <SDL2/SDL.h>

#ifndef ODE_HPP
#define ODE_HPP

namespace aos 
{

    std::vector< double > * euler(std::vector< double > * (*f)(std::vector< double >, Uint32),
                                    std::vector< double > & x, Uint32 dt, Uint32 t);
}

#endif
