#include "includes.hpp"
#include "Updateable.hpp"

#include <SDL2/SDL.h>
//#include <functional>

#ifndef ODE_HPP
#define ODE_HPP

namespace aos 
{ 
    std::vector< double > * euler(
        std::vector< double > * (Updateable::*)(std::vector< double > *, Uint32, Uint32),
        std::vector< double > * x, Uint32 dt, Uint32 t
    );

    class Integrator {
        public:
            Integrator();
            //~Integrator();
            std::vector< double > * (*integrator)(
                std::vector< double > * (Updateable::*)(std::vector< double > *, Uint32, Uint32),
                std::vector< double > * x, Uint32 dt, Uint32 t) = euler;  ///< Stores a pointer to the default ODE integrator function (defaults to euler)   
             
            std::vector< double > * integrate(
                std::vector< double > * (Updateable::*)(std::vector< double > *, Uint32, Uint32),
                std::vector< double > * x, Uint32 dt, Uint32 t
            );
    };
}


#endif
